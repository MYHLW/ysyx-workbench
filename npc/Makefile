# 默认接收外部传入的 IMG，如果未指定就用下面这行
IMG ?= /home/wang/ysyx-workbench/am/$(IMAGE).bin

# Capstone 配置
CAPSTONE_DIR = ./tools/capstone/repo
LIBCAPSTONE = $(CAPSTONE_DIR)/libcapstone.so.5

all:
	@echo "Write this Makefile by your self."

sim2: $(LIBCAPSTONE)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe ./csrc/*.cpp ./csrc/utils/*.c \
		-CFLAGS "-I$(CAPSTONE_DIR)/include -Icsrc/utils" -LDFLAGS "-ldl -lreadline -L$(CAPSTONE_DIR) -l:libcapstone.so.5" \
		--top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	@echo "=> Running NPC with image: $(IMG)"
	LD_LIBRARY_PATH=$(CAPSTONE_DIR) ./obj_dir/Vysyx_25020059_top $(IMG)
	gtkwave ./Vysyx_25020059.vcd

$(LIBCAPSTONE):
	@echo "Capstone library already exists at $(CAPSTONE_DIR)"
	@echo "Skipping build as it's pre-built"

clean:
	rm -rf obj_dir
	rm -f *.vcd
	rm -f csrc/utils/disasm.o

include ../Makefile