all:
	@echo "Write this Makefile by your self."
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe $(wildcard ./csrc/*.cpp) -LDFLAGS -ldl --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
	./obj_dir/Vysyx_25020059_top ./addi_test.bin
	#gtkwave ./obj_dir/Vysyx_25020059.vcd
#PHONY:clean sim

clean:
	rm -rf .obj_dir
include ../Makefile
#include ./vsrc/Makefile