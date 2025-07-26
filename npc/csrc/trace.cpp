// csrc/trace.cpp  中的 npc_trap

#include <cstdio>
#include <cstdint>

// 引入外部变量，来源于 main_new.cpp
extern bool  sim_done;
extern int   trap_code;

// 环形缓冲区及状态（同前面定义）
static constexpr size_t IBUF_SIZE = 10;
struct ITraceEntry { uint32_t pc, inst; char disasm[48]; };
static ITraceEntry ibuf[IBUF_SIZE];
static size_t       head     = 0;
static bool         buf_full = false;
static bool         dumped   = false;

// pmem_read 和 ringbuf_push 同前面定义
extern "C" uint32_t pmem_read(uint32_t);
static void ringbuf_push(uint32_t pc, uint32_t inst, const char *disasm);

extern "C" void npc_trap(int code) {
  // 1) 首次 trap 时 dump 最近十条指令
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

  // 2) 保留原有逻辑：只在第一次 trap 时设置 sim_done/trap_code
  if (!sim_done) {
    sim_done  = true;
    trap_code = code;
  }
}
