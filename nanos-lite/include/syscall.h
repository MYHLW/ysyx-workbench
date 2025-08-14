#ifndef __SYSCALL_H__
#define __SYSCALL_H__

struct Context;
void do_syscall(struct Context *c);

#define SYS_yield 0

#endif