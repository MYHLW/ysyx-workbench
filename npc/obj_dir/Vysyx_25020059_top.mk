# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Makefile for building Verilated archive or executable
#
# Execute this makefile from the object directory:
#    make -f Vysyx_25020059_top.mk

default: Vysyx_25020059_top

### Constants...
# Perl executable (from $PERL, defaults to 'perl' if not set)
PERL = perl
# Python3 executable (from $PYTHON3, defaults to 'python3' if not set)
PYTHON3 = python3
# Path to Verilator kit (from $VERILATOR_ROOT)
VERILATOR_ROOT = /usr/local/share/verilator
# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)
SYSTEMC_INCLUDE ?= 
# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)
SYSTEMC_LIBDIR ?= 

### Switches...
# C++ code coverage  0/1 (from --prof-c)
VM_PROFC = 0
# SystemC output mode?  0/1 (from --sc)
VM_SC = 0
# Legacy or SystemC output mode?  0/1 (from --sc)
VM_SP_OR_SC = $(VM_SC)
# Deprecated
VM_PCLI = 1
# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)
VM_SC_TARGET_ARCH = linux

### Vars...
# Design prefix (from --prefix)
VM_PREFIX = Vysyx_25020059_top
# Module prefix (from --prefix)
VM_MODPREFIX = Vysyx_25020059_top
# User CFLAGS (from -CFLAGS on Verilator command line)
VM_USER_CFLAGS = \
	-Wall -g -I/home/wang/ysyx-workbench/npc/csrc/include -I/home/wang/ysyx-workbench/npc/csrc/include/sdb -I/home/wang/ysyx-workbench/npc/csrc/include/cpu  -I/home/wang/ysyx-workbench/npc/../nemu/include -I /home/wang/ysyx-workbench/npc/tools/capstone/repo/include \

# User LDLIBS (from -LDFLAGS on Verilator command line)
VM_USER_LDLIBS = \
	-lreadline -L/home/wang/ysyx-workbench/npc/../nemu/build -lriscv32-nemu-interpreter-so -Wl,-rpath=/home/wang/ysyx-workbench/npc/../nemu/build \

# User .cpp files (from .cpp's on Verilator command line)
VM_USER_CLASSES = \
	cpu_exec \
	dut \
	ft_stack \
	ftrace \
	RingBuffer \
	bstrlib \
	iritrace \
	registers \
	utils \
	trace \
	memory \
	breakpoint \
	expr \
	sdb \
	watchpoint \
	disasm \
	log \
	top \

# User .cpp directories (from .cpp's on Verilator command line)
VM_USER_DIR = \
	.. \
	../csrc/src/cpu \
	../csrc/src/cpu/difftest \
	../csrc/src/cpu/ftrace \
	../csrc/src/cpu/iritrace \
	../csrc/src/debug \
	../csrc/src/device \
	../csrc/src/memory \
	../csrc/src/sdb \
	../csrc/src/utils \


### Default rules...
# Include list of all generated classes
include Vysyx_25020059_top_classes.mk
# Include global rules
include $(VERILATOR_ROOT)/include/verilated.mk

### Executable rules... (from --exe)
VPATH += $(VM_USER_DIR)

cpu_exec.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/cpu_exec.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
dut.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/difftest/dut.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
ft_stack.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/ftrace/ft_stack.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
ftrace.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/ftrace/ftrace.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
RingBuffer.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/iritrace/RingBuffer.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
bstrlib.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/iritrace/bstrlib.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
iritrace.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/iritrace/iritrace.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
registers.o: /home/wang/ysyx-workbench/npc/csrc/src/cpu/registers.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
utils.o: /home/wang/ysyx-workbench/npc/csrc/src/debug/utils.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
trace.o: /home/wang/ysyx-workbench/npc/csrc/src/device/trace.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
memory.o: /home/wang/ysyx-workbench/npc/csrc/src/memory/memory.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
breakpoint.o: /home/wang/ysyx-workbench/npc/csrc/src/sdb/breakpoint.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
expr.o: /home/wang/ysyx-workbench/npc/csrc/src/sdb/expr.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
sdb.o: /home/wang/ysyx-workbench/npc/csrc/src/sdb/sdb.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
watchpoint.o: /home/wang/ysyx-workbench/npc/csrc/src/sdb/watchpoint.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
disasm.o: /home/wang/ysyx-workbench/npc/csrc/src/utils/disasm.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
log.o: /home/wang/ysyx-workbench/npc/csrc/src/utils/log.c 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
top.o: /home/wang/ysyx-workbench/npc/top.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<

### Link rules... (from --exe)
Vysyx_25020059_top: $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a $(VM_HIER_LIBS)
	$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBS) $(SC_LIBS) -o $@


# Verilated -*- Makefile -*-
