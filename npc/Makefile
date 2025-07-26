# 默认接收外部传入的 IMG
IMG ?= /home/wang/ysyx-workbench/am/$(IMAGE).bin

# 设置 Capstone 的绝对路径
CAPSTONE_DIR := /home/wang/ysyx-workbench/npc/tools/capstone/repo
LIBCAPSTONE := $(CAPSTONE_DIR)/libcapstone.so.5

# 源文件列表
C_SRCS := $(wildcard csrc/*.cpp) \
          csrc/utils/disasm.c \
          csrc/utils/itrace.cpp

# 检查库文件存在
$(LIBCAPSTONE):
	@echo "Error: Capstone library not found at $(LIBCAPSTONE)"
	@echo "Please ensure Capstone is built and available at this location"
	@exit 1

all:
	@echo "Write this Makefile by your self."

sim2: $(LIBCAPSTONE)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@rm -rf obj_dir *.vcd  # 清理旧构建
	
	# 使用绝对路径链接库文件
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe $(C_SRCS) \
		-CFLAGS "-I$(CAPSTONE_DIR)/include -Icsrc/utils" \
		-LDFLAGS "-ldl -lreadline $(LIBCAPSTONE)" \
		--top ysyx_25020059_top
	
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	
	@echo "=> Running NPC with image: $(IMG)"
	LD_LIBRARY_PATH=$(CAPSTONE_DIR) ./obj_dir/Vysyx_25020059_top $(IMG)
	gtkwave ./Vysyx_25020059.vcd

clean:
	rm -rf obj_dir
	rm -f *.vcd

include ../Makefile