#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "watchpoint.h"
#include "sdb.h"

int test(){
	FILE *fp = fopen("~/ysyx-workbench/nemu/tools/gen-expr/input.txt","r");
	if (fp == NULL){
		assert(0);
		}
	char expr_str[1024];
	uint32_t expected_result;	
	// 读取文件中的测试数据
	while (fscanf(fp, "%u ", &expected_result) == 1) {  // 先读取无符号整数结果
    	// 读取整行表达式，跳过结果
    		if (fgets(expr_str, sizeof(expr_str), fp)) {
       	 // 去除末尾换行符
        		expr_str[strcspn(expr_str, "\n")] = '\0';

        		// 使用 expr() 函数计算表达式结果
        		bool success;
        		uint32_t result = expr(expr_str, &success);
        
        		// 打印对比结果
        		if (success && result == expected_result) {
            			printf("PASS: %s = %u\n", expr_str, result);
        		} else {
            			printf("FAIL: %s = %u, expected %u\n", expr_str, result, expected_result);
          }	
      }
  }
  return 0;
}
