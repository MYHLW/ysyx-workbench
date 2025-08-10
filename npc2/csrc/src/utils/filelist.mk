LIBCAPSTONE = $(NPC_HOME)/tools/capstone/repo/libcapstone.so.5
CFLAGS += -I $(NPC_HOME)/tools/capstone/repo/include
src/utils/disasm.c: $(LIBCAPSTONE)
$(LIBCAPSTONE):
	$(MAKE) -C $(NPC_HOME)/tools/capstone

