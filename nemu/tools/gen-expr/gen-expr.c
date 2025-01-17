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

// Define the maximum buffer size
#define BUF_SIZE 65536
static char buf[BUF_SIZE] = {};  // Buffer to hold the expression
static char code_buf[BUF_SIZE + 128] = {}; // A little larger than `buf`
// Code template for the C program to evaluate the expression
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

// Safely concatenate strings to avoid buffer overflow
void safe_strcat(char *dest, const char *src) {
    if (strlen(dest) + strlen(src) < BUF_SIZE - 1) {
        strcat(dest, src);
    }
}

// Function to generate random expressions
void gen_rand_expr() {
    buf[0] = '\0';  // Clear the buffer

    switch (rand() % 3) {
        case 0: {
            // Case 1: Generate a number
            sprintf(buf, "%d", rand() % 100);  // Random number between 0 and 99
            break;
        }
        case 1: {
            // Case 2: Generate a sub-expression with parentheses
            safe_strcat(buf, "(");
            gen_rand_expr();
            safe_strcat(buf, ")");
            break;
        }
        default: {
            // Case 3: Generate an expression with a random operator
            gen_rand_expr();
            char op = "+-*/"[rand() % 4];  // Choose a random operator
            if (op == '/') {
                // Ensure no division by zero
                int denominator = rand() % 100;
                if (denominator == 0) {
                    denominator = 1;  // Prevent division by zero
                }
                sprintf(buf + strlen(buf), " / %d", denominator);
            } else {
                char expr[64];
                int space_chance = rand() % 2;  // Randomly decide whether to insert a space
                if (space_chance) {
                    sprintf(expr, " %c ", op);   // Add space around operator
                } else {
                    sprintf(expr, "%c", op);     // No space around operator
                }
                safe_strcat(buf, expr);
                gen_rand_expr();
            }
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int seed = time(0);
    srand(seed);  // Initialize random number generator with current time
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);  // Read the number of iterations from command line argument
    }

    for (int i = 0; i < loop; i++) {
        gen_rand_expr();  // Generate a random expression

        // Prepare the C code with the generated expression
        sprintf(code_buf, code_format, buf);

        // Write the C code to a temporary file
        FILE *fp = fopen("/tmp/.code.c", "w");
        assert(fp != NULL);
        fputs(code_buf, fp);
        fclose(fp);

        // Compile the C code using gcc
        int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
        if (ret != 0) continue;  // If compilation fails, skip this iteration

        // Run the compiled C program and get the result
        fp = popen("/tmp/.expr", "r");
        assert(fp != NULL);

        unsigned result;
        ret = fscanf(fp, "%u", &result);  // Read the result from the program's output
        pclose(fp);

        // Print the result along with the generated expression
        printf("%u %s\n", result, buf);
    }
    return 0;
}

