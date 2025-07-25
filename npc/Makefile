# 默认接收外部传入的 IMG，如果未指定就用下面这行
IMG ?= /home/wang/ysyx-workbench/am/$(IMAGE).bin

all:
	@echo "Write this Makefile by your self."
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe ./csrc/main.cpp -LDFLAGS -ldl --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	./obj_dir/Vysyx_25020059_top
#gtkwave ./Vysyx_25020059.vcd
#PHONY:clean sim
sim2:
	$(call git_commit, "sim RTL")
	@$(clean)
# 编译时加入 sdb.cpp（在 csrc 目录下）
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) \
	  --exe ./csrc/main_new.cpp ./csrc/sdb.cpp \
	  -LDFLAGS "-ldl -lreadline" --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	@echo "=> Running NPC with image: $(IMG)"
	./obj_dir/Vysyx_25020059_top $(IMG)
	gtkwave ./Vysyx_25020059.vcd


clean:
	rm -rf .obj_dir
	rm *.vcd
include ../Makefile
#include ./vsrc/Makefile