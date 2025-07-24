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
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$(clean)
	verilator -Wno-lint --trace -cc $(wildcard ./vsrc/*.v) --exe ./csrc/main_new.cpp -LDFLAGS -ldl --top ysyx_25020059_top
	make -C obj_dir -j -f Vysyx_25020059_top.mk Vysyx_25020059_top
#./obj_dir/Vysyx_25020059_top ./program/dummy-riscv32e-npc.bin
	./obj_dir/Vysyx_25020059_top ./program/*.bin
	gtkwave ./Vysyx_25020059.vcd


clean:
	rm -rf .obj_dir
	rm *.vcd
include ../Makefile
#include ./vsrc/Makefile