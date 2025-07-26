// csrc/trace.cpp
#include <cstdint>
#include <cstdio>
#include <cstring>

// 从 main_new.cpp 引入这两个全局变量
extern bool  sim_done;
extern int   trap_code;

// 从 main_new.cpp 引入的内存读接口
extern "C" uint32_t pmem_read(uint32_t vaddr);

// 环形缓冲区容量：只保留最近 10 条
static constexpr size_t IBUF_SIZE = 10;

// 一条 trace 记录
struct ITraceEntry {
  uint32_t pc;
  uint32_t inst;
  char     disasm[48];
};

// 环形缓冲区及状态
static ITraceEntry ibuf[IBUF_SIZE];
static size_t       head     = 0;
static bool         buf_full = false;
static bool         dumped   = false;

// 将一条记录写入环形缓冲区
static void ringbuf_push(uint32_t pc, uint32_t inst, const char *disasm) {
  ibuf[head].pc   = pc;
  ibuf[head].inst = inst;
  std::strncpy(ibuf[head].disasm, disasm, sizeof(ibuf[0].disasm)-1);
  ibuf[head].disasm[sizeof(ibuf[0].disasm)-1] = '\0';
  head = (head + 1) % IBUF_SIZE;
  if (head == 0) buf_full = true;
}

// DPI-C 接口：每条指令取到时由 Verilog 调用
extern "C" void npc_itrace(uint32_t pc) {
  uint32_t inst = pmem_read(pc);
  char disasm[48];
  std::snprintf(disasm, sizeof(disasm), "0x%08x", inst);
  ringbuf_push(pc, inst, disasm);
}

// DPI-C 接口：trap（ebreak、越界等）时由 Verilog 调用
extern "C" void npc_trap(int code) {
  // 1) 首次 trap 时 dump 最近 10 条指令
  if (!dumped) {
    dumped = true;
    FILE *f = std::fopen("itrace_ringbuf.log", "w");
    if (f) {
      size_t count = buf_full ? IBUF_SIZE : head;
      std::fprintf(f,
        "=== Last %zu instructions (oldest first; most recent marked) ===\n",
        count);
      size_t start = buf_full ? head : 0;
      for (size_t i = 0; i < count; i++) {
        const auto &e = ibuf[(start + i) % IBUF_SIZE];
        bool is_last = (i + 1 == count);
        std::fprintf(f, "%08x: %08x  %-16s%s\n",
                     e.pc, e.inst, e.disasm,
                     is_last ? "  <-- fault here" : "");
      }
      std::fclose(f);
    }
  }
  // 2) 保留原有 sim_done / trap_code 逻辑
  if (!sim_done) {
    sim_done  = true;
    trap_code = code;
  }
}
