// difftest.cpp
// 动态加载 NEMU 的 difftest so，并提供 init / step_and_check / fini

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <dlfcn.h>

extern "C" {
  // 这些变量在 main_new.cpp 中定义（或其他地方），在此声明为外部引用
  extern unsigned char memory[];      // loader.cpp 提供的全局内存数组
  extern const uint32_t MEM_BASE;
  extern const uint32_t MEM_SIZE;
  extern size_t program_size;        // loader 应该设置为加载的字节数（见说明）
}

// 与 ref.c 中的 CPU_state 二进制兼容的最小结构（仅 gpr + pc）
struct DifftestCPUState {
  uint32_t gpr[32];
  uint32_t pc;
};

// difftest 函数指针类型（与 ref.c 中导出的一致）
using difftest_init_t   = void (*)(int);
using difftest_memcpy_t = void (*)(uint32_t, void*, size_t, bool);
using difftest_regcpy_t = void (*)(void*, bool);
using difftest_exec_t   = void (*)(uint64_t);

static void *nemu_so = nullptr;
static difftest_init_t   difftest_init_fp   = nullptr;
static difftest_memcpy_t difftest_memcpy_fp = nullptr;
static difftest_regcpy_t difftest_regcpy_fp = nullptr;
static difftest_exec_t   difftest_exec_fp   = nullptr;

static const bool DIFFTEST_TO_DUT = true;   // ref <- buf (把 buf 的数据写入 ref)
static const bool DIFFTEST_TO_REF = false;  // ref -> buf

// 你实现的比较函数（C 链接），我们调用它来对比寄存器
extern "C" {
  // note: 将 ref_state 传入，pc 作为第二个参数
  extern bool isa_difftest_checkregs(void *ref_r, uint32_t pc);
}

// 加载 nemu so
bool load_nemu_so(const char *so_path) {
  nemu_so = dlopen(so_path, RTLD_NOW | RTLD_LOCAL);
  if (!nemu_so) {
    std::fprintf(stderr, "[DIFTEST] dlopen(%s) failed: %s\n", so_path, dlerror());
    return false;
  }

  dlerror(); // clear
  difftest_init_fp   = (difftest_init_t)dlsym(nemu_so, "difftest_init");
  difftest_memcpy_fp = (difftest_memcpy_t)dlsym(nemu_so, "difftest_memcpy");
  difftest_regcpy_fp = (difftest_regcpy_t)dlsym(nemu_so, "difftest_regcpy");
  difftest_exec_fp   = (difftest_exec_t)dlsym(nemu_so, "difftest_exec");

  const char *err = dlerror();
  if (err) {
    std::fprintf(stderr, "[DIFTEST] dlsym error: %s\n", err);
    dlclose(nemu_so);
    nemu_so = nullptr;
    return false;
  }

  std::fprintf(stdout, "[DIFTEST] loaded NEMU so: %s\n", so_path);
  return true;
}

// 初始化 difftest：把内存和初始寄存器写入 REF
// init_pc：DUT 当前的起始 PC（通常在 reset 后读取 dut.curr_pc 传入）
bool init_difftest_for_npc(const char *so_path, uint32_t init_pc) {
  if (!load_nemu_so(so_path)) return false;

  if (!difftest_init_fp || !difftest_memcpy_fp || !difftest_regcpy_fp || !difftest_exec_fp) {
    std::fprintf(stderr, "[DIFTEST] missing difftest symbols\n");
    return false;
  }

  // 调用 ref 初始化
  difftest_init_fp(0);

  // 计算要初始化给 ref 的内存大小：优先用 loader 提供的 program_size（实际加载大小）
  size_t sz = (program_size > 0) ? program_size : (size_t)MEM_SIZE;

  // 把 DUT 的内存拷贝给 REF（ref <- memory）
  difftest_memcpy_fp(MEM_BASE, memory, sz, DIFFTEST_TO_DUT);

  // 同步初始寄存器（这里尽量只同步 pc；如果你能把 DUT 的 gpr[] 读出来并填入 DifftestCPUState.gpr，请在这里填充）
  DifftestCPUState init_state;
  std::memset(&init_state, 0, sizeof(init_state));
  init_state.pc = init_pc;

  difftest_regcpy_fp(&init_state, DIFFTEST_TO_DUT);

  std::fprintf(stdout, "[DIFTEST] initialized: mem %zu bytes copied, init_pc=0x%08x\n", sz, init_pc);
  return true;
}

// 单步：REF 执行 1 条指令并从 REF 读取寄存器，然后调用 isa_difftest_checkregs() 做比较。
// dut_pc：DUT 当前的 PC（用于作为对比时的上下文，如果 REF 返回的 pc 为0则用此值）
bool difftest_step_and_check(uint32_t dut_pc) {
  if (!difftest_exec_fp || !difftest_regcpy_fp) {
    // difftest 未启用
    return true;
  }

  // 让 REF 执行 1 条指令
  difftest_exec_fp(1);

  // 从 REF 读回寄存器
  DifftestCPUState ref_state;
  std::memset(&ref_state, 0, sizeof(ref_state));
  // direction = DIFFTEST_TO_DUT 表示把 REF 的寄存器写入 ref_state（REF -> buf）
  difftest_regcpy_fp(&ref_state, DIFFTEST_TO_DUT);

  uint32_t ref_pc = ref_state.pc ? ref_state.pc : dut_pc;

  // 调用你实现的对比函数（传 void*）
  bool ok = isa_difftest_checkregs(&ref_state, ref_pc);
  if (!ok) {
    std::fprintf(stderr, "[DIFTEST] mismatch detected: dut_pc=0x%08x ref_pc=0x%08x\n", dut_pc, ref_pc);
  }
  return ok;
}

void fini_difftest() {
  if (nemu_so) {
    dlclose(nemu_so);
    nemu_so = nullptr;
  }
}
