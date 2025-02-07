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

#include <common.h>
#include <stdlib.h>   // 用于文件操作
#include <string.h>   // 用于字符串处理
#include "../src/monitor/sdb/expr.h"  // 修正了路径

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

// 新增函数声明
uint32_t expr(char *e, bool *success);
int expression_test();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* 新增：通过命令行参数选择模式 */
  int test_mode = 0;
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "test") == 0) {
      test_mode = 1;
      break;
    }
  }

  if (test_mode) {
    // 表达式测试模式
    return expression_test();
  } else {
    // 原模拟器执行流程
    engine_start();
    return is_exit_status_bad();
  }
}

// 新增表达式测试函数实现
int expression_test() {
  const char *test_file = "/home/wang/ysyx-workbench/nemu/tools/gen-expr/input";
  FILE *fp = fopen(test_file, "r");
  if (fp == NULL) {
    Log("Failed to open test file %s", test_file);
    return 1;
  }

  char expr_str[1024];
  uint32_t expected_result;
  int pass_count = 0, total_count = 0;

  while (fscanf(fp, "%u", &expected_result) == 1) {
    if (fgets(expr_str, sizeof(expr_str), fp)) {
      // 清理输入：移除换行符和前导空格
      expr_str[strcspn(expr_str, "\n")] = '\0';
      char *expr1 = expr_str;
      while (*expr1 == ' ') expr1++; // 跳过前导空格

      // 执行表达式计算
      bool success;
      uint32_t result = expr(expr1, &success);

      // 输出带颜色的对比结果
      if (success && result == expected_result) {
        printf(ANSI_FMT("[PASS]", ANSI_FG_GREEN) " %s = %u\n", expr1, result);
        pass_count++;
      } else {
        printf(ANSI_FMT("[FAIL]", ANSI_FG_RED) " %s = %u (expected %u)\n", 
               expr1, result, expected_result);
      }
      total_count++;
    }
  }

  fclose(fp);
  
  // 打印统计信息
  printf("\nTest Summary:\n");
  printf("Total cases: %d\n", total_count);
  printf(ANSI_FMT("Passed: %d (%.1f%%)", 
         (pass_count == total_count) ? ANSI_FG_GREEN : ANSI_FG_RED),
         pass_count, (float)pass_count/total_count*100);
  
  return (pass_count == total_count) ? 0 : 1;
}

