/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <stdio.h>
#include <stdlib.h>

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}
static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args); //C 语言要求在使用函数指针之前，必须先声明该函数的原型。
static int cmd_x(char *args); 
static int cmd_p(char *args); 
static int cmd_w(char *args); 
static int cmd_d(char *args);
 

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Let the program execute N instructions in a single step and then pause,When N is not given, the default is 1", cmd_si },
  { "info", "Print register status/Print monitoring point information", cmd_info },
  { "x", "Find the value of the expression EXPR, use the result as the starting memory address, and output N consecutive 4-byte values in hexadecimal format", cmd_x },
  { "p", "Evaluate the expression EXPR", cmd_p },
  { "w", "When the value of expression EXPR changes, the program execution is paused.", cmd_w },
  { "d", "Delete the monitoring point with sequence number N", cmd_d },

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  //char *arg = strtok(NULL, " ");
  char *arg = strtok(args, " ");
  int i; //size_t??

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_si(char *args) {
       int n = 1; // 默认单步执行 1 条指令
       if (args != NULL) {
        	sscanf(args, "%d", &n); // 解析参数 N
       if (n <= 0) {
                printf("Error: Invalid argument for si. Must be a positive integer.\n");
      return 0;
    }
  }
  cpu_exec(n); // 执行 N 条指令
  return 0;
}

static int cmd_info(char *args){
	if (args == NULL){
		printf("Error: Missing argument. Use 'info r' or 'info w'.\n");
		return 0;
	}
	if (strcmp(args,"r") == 0){
		isa_reg_display();
	}else if (strcmp(args,"w") == 0){
	//	 print_wp_info(); // 打印监视点信息，假设有该函数!!!
	}else{
		 printf("Error: Unknown argument '%s'. Use 'info r' or 'info w'.\n", args);
        }
	return 0;
}



  static int cmd_x(char *args) {
  /*if (args == NULL) {
    printf("Error: Missing arguments. Use 'x N EXPR'.\n");
    return 0;
  }

  int n;
  char *expr = NULL;
  sscanf(args, "%d %ms", &n, &expr); // 解析参数 N 和 EXPR
  if (expr == NULL || n <= 0) {
    printf("Error: Invalid arguments. Use 'x N EXPR'.\n");
    free(expr);
    return 0;
  }

  bool success;
 // word_t addr = expr(expr, &success); // 假设有 expr实现表达式求值
  free(expr);  
  if (!success) {
    printf("Error: Failed to evaluate expression.\n");
    return 0;
  }

  for (int i = 0; i < n; i++) {
    printf("0x%08lx: 0x%08x\n", addr + i * 4, vaddr_read(addr + i * 4, 4)); // 假设 vaddr_read 实现内存读取!!parre_read??
  }    */    
  return 0;
}


static int cmd_p(char *args) {      //表达式求值p EXPR
  /* if (args == NULL) {
    printf("Error: Missing expression.\n");
    return 0;
  }

  bool success;
 // word_t result = expr(args, &success); // expr.c=>expr()实现表达式求值
  if (!success) {
    printf("Error: Failed to evaluate expression.\n");
  } else {
    printf("Result = %ld\n", result);
  }   */
  return 0;  
}

static int cmd_w(char *args) {
/*  if (args == NULL) {
    printf("Error: Missing expression for watchpoint.\n");
    return 0;
  }
  set_wp(args); // 假设 set_wp 实现了设置监视点   */
  return 0;  
}

static int cmd_d(char *args) {
/*  if (args == NULL) {
    printf("Error: Missing watchpoint number.\n");
    return 0;
  }    

  int wp_num = atoi(args);//focus on atoi!!
 if (!delete_wp(wp_num)) { // 假设 delete_wp 实现了删除监视点!!!
    printf("Error: Watchpoint %d does not exist.\n", wp_num);
  }   */
  return 0;    
}    







void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
