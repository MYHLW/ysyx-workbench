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
#include "local-include/reg.h"
#include <stdio.h>
#include <string.h> // 添加此头文件以支持 strcmp

typedef uint32_t word_t; // 定义 word_t 类型
extern CPU_state cpu;
// 通过头文件声明的外部变量访问全局 cpu

/*CPU_state cpu = {
  .gpr = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31
  }
};   */

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};


//I fix the module
void isa_reg_display() {
 printf("Register Information:\n");
  for (int i = 0; i < 32; i++) {
    printf("%-5s  0x%08x\n", regs[i], cpu.gpr[i]);
  }
}
/*Register Information:
$0     0x00000000
ra     0x00000001
sp     0x00000002
...
*/

//I fix the module
word_t isa_reg_str2val(const char *s, bool *success) {
    printf("%s", s);
   size_t len = strlen(s);
   char reg[] = "";
   for (size_t i = 0; i < len-1; i++) {
        reg[i] = s[i+1];
        }
    printf("%s", reg);
       //remove $
   for (int i = 0; i < 32; i++) {
    if (strcmp(reg, regs[i]) == 0) {
      *success = true;
      printf("The REG is %s",regs[i]);
      return cpu.gpr[i];
    }
  }
  *success = false;
  return 0; // 如果未找到，返回 0
}  
