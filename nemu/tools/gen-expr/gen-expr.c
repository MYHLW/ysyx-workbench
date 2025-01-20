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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// 函数声明
static void gen_rand_expr(void);
static void gen(char c);
static void gen_num(void);
static void gen_rand_op(void);
static int choose(int n);
static int gen_non_zero_num();

static char buf[655369] = {};    // 表达式存储数组
static int index_buf = 0;       // 当前索引
static char code_buf[655369 + 128] = {};  // 用于存储生成的代码
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

// 用于生成随机表达式
static void gen_rand_expr(void) {
    // 防止索引超出 buf 长度
    if (index_buf >= sizeof(buf) - 10) {
        printf("Buffer overflow prevented!\n");
        return; // 如果超过最大长度，停止生成
    }
    
    switch (choose(3)) {
        case 0: gen_num(); break;
        case 1: gen('('); gen_rand_expr(); gen(')'); break;
        default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
    }
}

// 随机选择一个值
int choose(int n) {
    return rand() % n;
}

// 向 buf 中添加一个字符
static void gen(char c) {
    if (index_buf < sizeof(buf) - 1) {  // 确保不会超出 buf 的大小
        buf[index_buf++] = c;
    } else {
        printf("Buffer overflow prevented!\n");
    }
}

// 生成一个随机数字
static void gen_num(void) {
    unsigned num = rand() % 100;  // 使用无符号类型
    int len = 0, tmp = num;
    while (tmp) {
        tmp /= 10;
        len++;
    }

    int x;
    if (len <= 1) x = 1;
    else x = (len - 1) * 10;

    while (num) {
        char c = num / x + '0';
        if (index_buf < sizeof(buf) - 1) {  // 确保不会超出 buf 的大小
            buf[index_buf++] = c;
        } else {
            printf("Buffer overflow prevented!\n");
            return;
        }
        num %= x;
        x /= 10;
    }
}

// 生成一个随机运算符
static void gen_rand_op(void) {
    char op[4] = {'+', '-', '*', '/'};
    int pos = rand() % 4;
    if (index_buf < sizeof(buf) - 1) {  // 确保不会超出 buf 的大小
        buf[index_buf++] = op[pos];
    } else {
        printf("Buffer overflow prevented!\n");
    }
}

static int gen_non_zero_num() {
    int num;
    do {
        num = rand() % 100;
    } while (num == 0);
    return num;
}

int main(int argc, char *argv[]) {
    int seed = time(0);
    srand(seed);
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);
    }
    int i;
    for (i = 0; i < loop; i++) {
        index_buf = 0;  // 重置索引
        memset(buf, 0, sizeof(buf));  // 清空 buf
        gen_rand_expr();  // 生成表达式
	for (int j = 0; j < index_buf; j++) {
            if (buf[j] == '/') {
                int num = gen_non_zero_num();
                sprintf(buf + j + 1, "%d", num);
                j += strlen(buf +j +1) - 1;
            } 
        }
        // 防止生成的表达式超过 buf 限制
        if (index_buf < sizeof(buf) - 1) {
            sprintf(code_buf, code_format, buf);
        } else {
            printf("Expression too long, skipping...\n");
            continue;
        }

        FILE *fp = fopen("/tmp/.code.c", "w");
        assert(fp != NULL);
        fputs(code_buf, fp);
        fclose(fp);

        int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
        if (ret != 0) continue;

        fp = popen("/tmp/.expr", "r");
        assert(fp != NULL);

        unsigned result;  // 使用无符号整数
        ret = fscanf(fp, "%u", &result);  // 读取无符号整数
        pclose(fp);

        printf("%u %s\n", result, buf);  // 打印无符号整数
    }

    return 0;
}


