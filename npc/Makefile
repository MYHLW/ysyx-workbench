# 默认接收外部传入的 IMG，如果未指定就用下面这行
IMG ?= /home/wang/ysyx-workbench/npc/program/$(IMAGE).bin

# 添加capstone库路径
CAPSTONE_PATH = $(shell pwd)/tools/capstone
CAPSTONE_INC = $(CAPSTONE_PATH)/include
CAPSTONE_LIB = $(CAPSTONE_PATH)/lib/libcapstone.a

# 编译标志
CFLAGS = -I$(CAPSTONE_INC)
LDFLAGS = -ldl -lreadline $(CAPSTONE_LIB)

all:
	@echo "Write this Makefile by your self."

# 编译capstone
$(CAPSTONE_LIB):
	$(MAKE) -C tools/capstone

run: $(CAPSTONE_LIB)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint -cc $(wildcard ./vsrc/*.v) \
		--exe ./csrc/*.cpp ./csrc/trace/*.cpp \
		$(CFLAGS) -LDFLAGS "$(LDFLAGS)" \
		--top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	@echo "=> Running NPC with image: $(IMG)"
	./obj_dir/Vysyx_25020059_top $(IMG)

run-debug: $(CAPSTONE_LIB)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) \
		--exe ./csrc/*.cpp ./csrc/trace/*.cpp \
		$(CFLAGS) -LDFLAGS "$(LDFLAGS)" \
		--top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	@echo "=> Running NPC with image: $(IMG)"
	./obj_dir/Vysyx_25020059_top $(IMG)
	gtkwave ./Vysyx_25020059.vcd

clean:
	rm -rf ./obj_dir
	rm -f *.vcd

# 清理capstone
clean-all: clean
	$(MAKE) -C tools/capstone clean

include ../Makefile