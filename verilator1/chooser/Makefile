# @echo "Write this Makefile by your self."
# VSRC = $(wildcard ./vsrc/*.v)
# CSRC = $(wildcard ./csrc/*.cpp)
FILEV = $(wildcard ./top.v)
FILEC = $(wildcard ./test_top.cpp)
all:
	@echo "Write this Makefile by your self."
 
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -Wno-fatal $(FILEV) $(FILEC) --top-module top --cc --trace --exe
	make -C obj_dir -f Vtop.mk Vtop
	./obj_dir/Vtop
	# gtkwave wave.vcd
 
 .PHONY:clean
clean:
	rm -rf obj_dir wave.vcd	


