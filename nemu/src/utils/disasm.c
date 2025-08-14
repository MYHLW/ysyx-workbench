// disasm.c
#include <dlfcn.h>
#include <capstone/capstone.h>
#include <common.h>

static size_t (*cs_disasm_dl)(csh handle, const uint8_t *code,
    size_t code_size, uint64_t address, size_t count, cs_insn **insn) = NULL;
static void (*cs_free_dl)(cs_insn *insn, size_t count) = NULL;

static csh handle = 0;
static bool disasm_enabled = false;

void init_disasm() {
  void *dl_handle = NULL;

  // 先尝试系统库，避免相对路径问题
  dl_handle = dlopen("libcapstone.so.5", RTLD_LAZY);
  if (!dl_handle) {
    // 再试工程内相对路径（注意工作目录差异）
    dl_handle = dlopen("tools/capstone/repo/libcapstone.so.5", RTLD_LAZY);
  }
  if (!dl_handle) {
    fprintf(stderr, "WARN: capstone not found; disasm disabled: %s\n", dlerror());
    disasm_enabled = false;
    return;
  }

  cs_err (*cs_open_dl)(cs_arch arch, cs_mode mode, csh *handle) = dlsym(dl_handle, "cs_open");
  cs_disasm_dl = dlsym(dl_handle, "cs_disasm");
  cs_free_dl   = dlsym(dl_handle, "cs_free");

  if (!cs_open_dl || !cs_disasm_dl || !cs_free_dl) {
    fprintf(stderr, "WARN: capstone symbols missing; disasm disabled\n");
    disasm_enabled = false;
    return;
  }

  cs_arch arch = MUXDEF(CONFIG_ISA_x86,      CS_ARCH_X86,
                   MUXDEF(CONFIG_ISA_mips32, CS_ARCH_MIPS,
                   MUXDEF(CONFIG_ISA_riscv,  CS_ARCH_RISCV,
                   MUXDEF(CONFIG_ISA_loongarch32r,  CS_ARCH_LOONGARCH, -1))));
  cs_mode mode = MUXDEF(CONFIG_ISA_x86,      CS_MODE_32,
                   MUXDEF(CONFIG_ISA_mips32, CS_MODE_MIPS32,
                   MUXDEF(CONFIG_ISA_riscv,  MUXDEF(CONFIG_ISA64, CS_MODE_RISCV64, CS_MODE_RISCV32) | CS_MODE_RISCVC,
                   MUXDEF(CONFIG_ISA_loongarch32r,  CS_MODE_LOONGARCH32, -1))));
  int ret = cs_open_dl(arch, mode, &handle);
  if (ret != CS_ERR_OK) {
    fprintf(stderr, "WARN: cs_open failed (%d); disasm disabled\n", ret);
    disasm_enabled = false;
    return;
  }

#ifdef CONFIG_ISA_x86
  cs_err (*cs_option_dl)(csh handle, cs_opt_type type, size_t value) = dlsym(dl_handle, "cs_option");
  if (cs_option_dl) {
    cs_option_dl(handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);
  }
#endif

  disasm_enabled = true;
}

void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte) {
  if (!disasm_enabled || !cs_disasm_dl || !cs_free_dl || handle == 0) {
    // 降级：没装 capstone 或未初始化，避免崩溃
    if (size > 0) {
      // 也可选择打印十六进制
      snprintf(str, size, "%s", ""); 
    }
    return;
  }
  cs_insn *insn = NULL;
  size_t count = cs_disasm_dl(handle, code, nbyte, pc, 1, &insn);
  if (count != 1 || insn == NULL) {
    snprintf(str, size, "%s", ""); 
    if (insn) cs_free_dl(insn, count);
    return;
  }
  int ret = snprintf(str, size, "%s", insn->mnemonic);
  if (insn->op_str[0] != '\0') {
    snprintf(str + ret, size - ret, "\t%s", insn->op_str);
  }
  cs_free_dl(insn, count);
}
