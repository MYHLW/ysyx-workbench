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


static void gen_rand_expr(int depth);
static void gen(char c);
static void gen_num(int non_zero);
static char gen_rand_op(void);
static int choose(int n);

static char buf[655369] = {};
static int index_buf = 0;
static char code_buf[655369 + 128] = {};
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

// 生成随机表达式，确保分母非零和括号匹配
static void gen_rand_expr(int depth) {
    if (index_buf >= sizeof(buf) - 10) {
        return;
    }
    if (depth > 10) { // 超过深度时生成数字避免无效括号
        gen_num(0);
        return;
    }

    switch (choose(4)) {
        case 0: gen_num(0); break;
        case 1: 
            gen('('); 
            gen_rand_expr(depth + 1); 
            gen(')'); 
            break;
        case 2: 
            gen_rand_expr(depth + 1);
            char op = gen_rand_op();
            if (op == '/') {
                gen_num(1); // 分母为非零
            } else {
                gen_rand_expr(depth + 1);
            }
            break;
        case 3: 
            gen_num(0);
            char op2 = gen_rand_op();
            if (op2 == '/') {
                gen_num(1);
            } else {
                gen_num(0);
            }
            break;
    }
}

int choose(int n) {
    return rand() % n;
}

static void gen(char c) {
    if (index_buf < sizeof(buf) - 1) {
        buf[index_buf++] = c;
    }
}

// 生成数字，non_zero控制是否非零
static void gen_num(int non_zero) {
    unsigned num;
    if (non_zero) {
        num = (rand() % 99) + 1; // 1-99
    } else {
        num = rand() % 100; // 0-99
    }
    char num_str[10];
    sprintf(num_str, "%u", num);
    for (int i = 0; num_str[i] != '\0'; i++) {
        gen(num_str[i]);
    }
}

// 生成运算符并返回
static char gen_rand_op(void) {
    char op[] = {'+', '-', '*', '/'};
    int pos = rand() % 4;
    gen(op[pos]);
    return op[pos];
}

int main(int argc, char *argv[]) {
    int seed = time(0);
    srand(seed);
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);
    }
    for (int i = 0; i < loop; i++) {
        index_buf = 0;
        memset(buf, 0, sizeof(buf));
        gen_rand_expr(0);

        // 确保表达式非空
        if (index_buf == 0) {
            gen_num(0);
        }

        // 生成代码
        if (index_buf < sizeof(buf) - 1) {
            sprintf(code_buf, code_format, buf);
        } else {
            printf("Expression too long, skipping...\n");
            continue;
        }

        FILE *fp = fopen("/tmp/.code.c", "w");
        if (fp == NULL) {
            perror("Failed to open file");
            continue;
        }
        fputs(code_buf, fp);
        fclose(fp);

        int ret = system("gcc /tmp/.code.c -o /tmp/.expr 2>/dev/null");
        if (ret != 0) {
            printf("Compilation failed, skipping...\n");
            continue;
        }

        fp = popen("/tmp/.expr", "r");
        if (!fp) {
            perror("Failed to run expr");
            continue;
        }

        unsigned result;
        if (fscanf(fp, "%u", &result) != 1) {
            pclose(fp);
            printf("Read result failed\n");
            continue;
        }
        pclose(fp);
        printf("%u %s\n", result, buf);
    }
    return 0;
}


