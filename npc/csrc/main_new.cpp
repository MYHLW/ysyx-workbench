// csrc/main_new.cpp
#include "cli.h"
#include "Vysyx_25020059_top.h"
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

#define MEM_FAULT_CODE   0xdeadbeef  // 定义内存故障码
#define MEM_ACCESS_FAULT 1           // 定义内存访问错误trap码

#define MEM_BASE    0x00000000U
#define MEM_SIZE (128 * 1024 * 1024)  // 128 MB


// ----- 全局变量定义 -----
VerilatedContext* ctx       = nullptr;
VerilatedVcdC*    tfp       = nullptr;
bool              sim_done  = false;
int               trap_code = -1;
uint64_t          sim_cycle = 0;
Vysyx_25020059_top dut;
// 全局静态分配8 MB
static uint8_t memory[MEM_SIZE];

// 在加载镜像时直接写入
void load_image(const char* filename) {
    FILE* fp = std::fopen(filename, "rb");
    if (!fp) { std::perror("fopen"); std::exit(EXIT_FAILURE); }
    size_t sz = std::fread(memory, 1, MEM_SIZE, fp);
    std::fclose(fp);
    std::printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n",
                filename, sz, MEM_BASE);
}


// 加载 HEX 格式程序 (地址为 word 地址)
void load_hex(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::perror("open hex file");
        std::exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos == std::string::npos) continue;
        // 解析地址（word 地址）
        std::string addrStr = line.substr(0, pos);
        uint32_t wordAddr = std::stoul(addrStr, nullptr, 16);
        uint32_t baseByte = wordAddr * 4;
        // 解析每个指令词
        std::string data = line.substr(pos + 1);
        std::istringstream iss(data);
        std::string tok;
        uint32_t idx = 0;
        while (iss >> tok) {
            uint32_t instr = std::stoul(tok, nullptr, 16);
            // 小端存储
            for (int b = 0; b < 4; b++) {
                memory[baseByte + idx * 4 + b] = (instr >> (8 * b)) & 0xFF;
            }
            idx++;
        }
    }
    std::printf("Loaded hex program '%s' into memory at 0x%08X\n", filename, MEM_BASE);
}

// 根据文件后缀选择加载方式
void load_program(const char* filename) {
    std::string fn(filename);
    auto pos = fn.rfind('.');
    if (pos != std::string::npos && fn.substr(pos) == ".hex") {
        load_hex(filename);
    } else {
        load_image(filename);
    }
}

// 单周期执行
void single_cycle() {    
    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);
   // dut.inst = pmem_read(dut.curr_pc);   
    dut.clk = 1;
    dut.eval();        
    tfp->dump(ctx->time());
    ctx->timeInc(1);
    
    
    sim_cycle++;
}

// 复位用：不做 pmem_read
void reset_cycle() {
    dut.clk = 1;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);
}



void reset(int n) {
    while(n>0){
    dut.clk = 0;  // 时钟低电平
    dut.rst = 1;  // 设置复位信号
    dut.eval();   // 评估模型
    tfp->dump(ctx->time());  // 转储当前时间点
    ctx->timeInc(1);  // 增加时间
    dut.clk = 1;  // 时钟高电平
    dut.rst = 1;  // 取消复位信号
    dut.eval();  // 再次评估模型
    tfp->dump(ctx->time());  // 转储当前时间点
    ctx->timeInc(1);  // 增加时间
    dut.rst = 0;  // 取消复位信号
    n--;
    }
}

void summary(){
    printf("%ld cycles executed.\n", sim_cycle);
    // 结束后输出 Trap 状态
    std::printf("\n");
    if (trap_code == 0) {
        std::printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        std::printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n", trap_code);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "Usage: %s <program.hex|program.bin>\n", argv[0]);
        return -1;
    }

    // memory = (uint8_t*)std::malloc(MEM_SIZE);
    // if (!memory) { std::perror("malloc"); return -1; }
    std::memset(memory, 0, MEM_SIZE);

    // 根据后缀自动选择加载方式
    load_program(argv[1]);

    // 波形跟踪
    Verilated::traceEverOn(true);
    ctx = new VerilatedContext;
    tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    // 复位
    reset(2);

    // 启动命令行调试
    sdb_mainloop();
    
    void summary();

    tfp->close();
    delete tfp;
    delete ctx;
    return 0;
}


// ===================DPI 端口===========================
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
    }
    printf("NPC_TRAP: code=%d", code);
}

extern "C" uint32_t pmem_read(uint32_t vaddr,int i) {  
    if (vaddr < MEM_BASE || vaddr >= MEM_BASE + MEM_SIZE) {
        printf("pmem_read: address out of bounds: 0x%08X\n", vaddr);
        npc_trap(MEM_ACCESS_FAULT);  // 触发内存访问错误trap
        return MEM_FAULT_CODE;
    }
    printf("code:%d pmem_read: vaddr=0x%08X\n",i, vaddr);  //!!1
    uint32_t off = vaddr - MEM_BASE;
    
    // 安全的内存访问（避免未对齐访问问题）
    uint32_t value;
    memcpy(&value, memory + off, sizeof(value));
    return value;
}

extern "C" void pmem_write(uint32_t addr, uint32_t data, uint8_t wmask) {
   // printf("pmem_write: addr=0x%08X, data=0x%08X, wmask=0x%02X\n", addr, data, wmask);
    uint32_t off = addr - MEM_BASE;
    uint8_t *p = memory + off;
    for (int i = 0; i < 4; i++) {
        if (wmask & (1 << i)) {
            p[i] = (data >> (i * 8)) & 0xff;
        }
    }
}


//=======================================================