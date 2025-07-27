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

// ----- 全局变量定义 -----
VerilatedContext* ctx       = nullptr;
VerilatedVcdC*    tfp       = nullptr;
bool              sim_done  = false;
int               trap_code = -1;
uint64_t          sim_cycle = 0;
Vysyx_25020059_top dut;
uint8_t*          memory    = nullptr;

#define MEM_FAULT_CODE   0xdeadbeef  // 定义内存故障码
#define MEM_ACCESS_FAULT 1           // 定义内存访问错误trap码

#define MEM_BASE    0x80000000U
#define MEM_SIZE    (8 * 1024 * 1024)  // 8MB

// 加载二进制镜像
void load_image(const char* filename) {
    FILE* fp = std::fopen(filename, "rb");
    if (!fp) {
        std::perror("fopen");
        std::exit(EXIT_FAILURE);
    }
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

    dut.clk = 1;
    dut.eval();
    dut.inst = pmem_read(dut.curr_pc);
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    sim_cycle++;
}

// 复位 n 周期
void reset(int n) {
    dut.rst = 1;
    while (n-- > 0) single_cycle();
    dut.rst = 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "Usage: %s <program.hex|program.bin>\n", argv[0]);
        return -1;
    }

    memory = (uint8_t*)std::malloc(MEM_SIZE);
    if (!memory) { std::perror("malloc"); return -1; }
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

    // 结束后输出 Trap 状态
    std::printf("\n");
    if (trap_code == 0) {
        std::printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        std::printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n", trap_code);
    }

    tfp->close();
    delete tfp;
    delete ctx;
    std::free(memory);
    return 0;
}
