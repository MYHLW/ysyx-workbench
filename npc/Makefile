# 测试用 .bin 文件所在目录
TEST_DIR := /home/wang/ysyx-workbench/nemu/am-kernels/tests/cpu-tests

# 允许通过 NAME 参数指定要加载的二进制文件
# 用法：make sim NAME=<binary_name>
NAME ?= dummy.bin
PROGRAM ?= $(TEST_DIR)/$(NAME)

all:
	@echo "Write this Makefile by your self."
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe $(wildcard ./csrc/main.cpp) -LDFLAGS -ldl --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	./obj_dir/Vysyx_25020059_top
#gtkwave ./obj_dir/Vysyx_25020059.vcd
#PHONY:clean sim

sim2:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe ./csrc/main_new.cpp -LDFLAGS -ldl --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	./obj_dir/Vysyx_25020059_top $(PROGRAM)


clean:
	rm -rf .obj_dir
include ../Makefile
#include ./vsrc/Makefile