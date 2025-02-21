#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "watchpoint.h"
#include "sdb.h"


extern uint32_t expr(char *e, bool *success); //


int test(){
        int count = 1;
        int number = 0;
	//FILE *fp = fopen("/home/wang/ysyx-workbench/nemu/tools/gen-expr/input.txt","r");
	FILE *fp = fopen("/home/wang/ysyx-workbench/nemu/tools/gen-expr/input","r");
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
            			count++;
        		} else {
            			printf("THE NUBER OF %d FAIL: %s = %u, expected %u\n", number,expr_str, result, expected_result);
          }	
      }number++;
  }printf("THE PASS NUMBER:%d\n",count);
  return 0;
}
