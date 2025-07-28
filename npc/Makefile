# 默认接收外部传入的 IMG，如果未指定就用下面这行
IMG ?= /home/wang/ysyx-workbench/npc/program/$(IMAGE).bin

all:
	@echo "Write this Makefile by your self."

run:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe ./csrc/*.cpp  -LDFLAGS "-ldl -lreadline" --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	@echo "=> Running NPC with image: $(IMG)"
	./obj_dir/Vysyx_25020059_top $(IMG)
	gtkwave ./Vysyx_25020059.vcd


clean:
	rm -rf ./obj_dir
	rm *.vcd
include ../Makefile
#include ./vsrc/Makefile