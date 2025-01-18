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
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vaddr_read.h"
#include <memory/vaddr.h>


enum {
  TK_NOTYPE = 256,
  TK_EQ,           // ==
  TK_NE,           //!=
  TK_NUMBER,       // 数字
  TK_PLUS,         // +
  TK_MINUS,        // -
  TK_MULTIPLY,     // *
  TK_DIVIDE,       // /
  TK_MODULO,       // %
  TK_LPAREN,       // (
  TK_RPAREN,       // )
  TK_AND,          // &&
  TK_OR,           // ||
  TK_NOT,          //!
  TK_UNARY_MINUS,   // 一元 -
  TK_HEX_NUMBER,    // 十六进制数
  TK_LT,TK_LE,TK_GT,TK_GE,
  TK_DEREF = 276,
  TK_REG
};


static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  {"0[xX][0-9a-fA-F]+", TK_HEX_NUMBER}, // 十六进制数字
  {" +", TK_NOTYPE},    // spaces
  {"\\+", TK_PLUS},         // plus
  {"==", TK_EQ},        // equal
  {"!=", TK_NE},        // not equal
  {"-", TK_MINUS},         // minus
  {"\\*", TK_MULTIPLY},    // multiply
  {"\\*", TK_DEREF},      // pointer dereference
  {"/", TK_DIVIDE},        // divide
  {"%", TK_MODULO},        // modulo
  {"\\(", TK_LPAREN},      // left parenthesis
  {"\\)", TK_RPAREN},      // right parenthesis
  {"[0-9]+", TK_NUMBER},   // DECIMAL NUM
  {"&&", TK_AND},         // logical AND
  {"\\|\\|", TK_OR},      // logical OR
//  {"!", TK_NOT},         // logical NOT
//  {"<<", TK_LSHIFT},      // bitwise left shift
//  {">>", TK_RSHIFT},      // bitwise right shift
//  {"&", TK_BITAND},       // bitwise AND
//  {"\\|", TK_BITOR},      // bitwise OR
//  {"\\^", TK_BITXOR},     // bitwise XOR
//  {"~", TK_BITNOT},       // bitwise NOT
  {"<", TK_LT},           // less than
  {"<=", TK_LE},          // less than or equal
  {">", TK_GT},           // greater than
  {">=", TK_GE},          // greater than or equal
//  {"^-", TK_UNARY_MINUS}   // unary minus
  {"\\$[a-zA-Z0-9]+", TK_REG},
};


#define NR_REGEX ARRLEN(rules)


static regex_t re[NR_REGEX] = {};


void init_regex() {
  int i;
  char error_msg[128];
  int ret;


  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret!= 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}


typedef struct token {
  int type;
  char *str;
} Token;


static Token tokens[65536] __attribute__((used)) = {};  //TOO SMALL?
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {   
  
  int position = 0;
  int i;
  regmatch_t pmatch;
  nr_token = 0;
  
  while (e[position]!= '\0') {
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;
   
        switch (rules[i].token_type) {
           case TK_NOTYPE:
                break;
           case TK_NUMBER:
           case TK_HEX_NUMBER:
             tokens[nr_token].type = rules[i].token_type;
             tokens[nr_token].str = (char *)malloc(substr_len + 1);
             if (tokens[nr_token].str == NULL) {
                printf("Memory allocation failed\n");
                return false;
             }
             strncpy(tokens[nr_token].str, substr_start, substr_len);
             tokens[nr_token].str[substr_len] = '\0';
             nr_token++;
             break;
          case TK_LT:
          case TK_LE:
          case TK_GT:
          case TK_GE:
          case TK_DEREF:
          case TK_REG:
           
          case TK_PLUS:
          case TK_MINUS:
          case TK_MULTIPLY:
          case TK_DIVIDE:
          case TK_MODULO:
          case TK_EQ:
          case TK_NE:
          case TK_LPAREN:
          case TK_RPAREN:
          case TK_AND:
          case TK_OR:
        //  case TK_NOT:
        //  case TK_UNARY_MINUS:
             tokens[nr_token].type = rules[i].token_type;
             tokens[nr_token].str = (char *)malloc(strlen(rules[i].regex) + 1);
             if (tokens[nr_token].str == NULL) {
                printf("Memory allocation failed\n");
                return false;
             }
             strncpy(tokens[nr_token].str, rules[i].regex, strlen(rules[i].regex));
             tokens[nr_token].str[strlen(rules[i].regex)] = '\0';
             nr_token++;
             break;
          default:
             printf("Unknown token type\n");
             return false;
        }
        break;
      }
    }
    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  return true;
}


// 辅助函数：将十六进制字符串转换为整数
long long hex_to_decimal(char *hex_str) {
  return strtoll(hex_str, NULL, 16);
}


// 检查表达式是否被一对匹配的括号包围
bool check_parentheses(int p, int q) {
  if (tokens[p].type == TK_LPAREN && tokens[q].type == TK_RPAREN) {
    int count = 0;
    for (int i = p; i <= q; i++) {
      if (tokens[i].type == TK_LPAREN) count++;
      if (tokens[i].type == TK_RPAREN) count--;
      if (count == 0 && i < q) return false;
    }
    return count == 0;
  }
  return false;
}


// 找到主运算符
int find_main_op(int p, int q) {
  int paren_count = 0;
  int main_op = -1;
  int op_priority = 7; 
  int current_priority = 7;
  // 从左到右扫描token
  for (int i = p; i <= q; i++) {
    if (tokens[i].type == TK_LPAREN) paren_count++;
    if (tokens[i].type == TK_RPAREN) paren_count--;
    
  /*  // 只有在括号平衡的情况下才能考虑运算符
    if (paren_count == 0) {
        int current_priority = 3;  // 默认较高优先级

        // 根据运算符类型设定优先级
        if (tokens[i].type == TK_PLUS || tokens[i].type == TK_MINUS) {
          current_priority = 1;  // 加减优先级较低
        } else if (tokens[i].type == TK_MULTIPLY || tokens[i].type == TK_DIVIDE || tokens[i].type == TK_MODULO) {
          current_priority = 2;  // 乘除优先级较高
        }      */
               // 设置优先级
        if (tokens[i].type == TK_PLUS || tokens[i].type == TK_MINUS)
          current_priority = 4;// 加减
        else if (tokens[i].type == TK_MULTIPLY || tokens[i].type == TK_DIVIDE || tokens[i].type == TK_MODULO)
          current_priority = 5; // 乘除
        else if (tokens[i].type == TK_LT || tokens[i].type == TK_LE || tokens[i].type == TK_GT || tokens[i].type == TK_GE || tokens[i].type == TK_EQ || tokens[i].type == TK_NE)
          current_priority = 3;  // 比较运算符
        else if (tokens[i].type == TK_AND)
          current_priority = 2;  // 逻辑与
        else if (tokens[i].type == TK_OR)
          current_priority = 1;  // 逻辑或
        else if (tokens[i].type == TK_DEREF)
          current_priority = 6;  //pointer
           // 选择当前运算符作为主运算符的条件:1. 当前运算符的优先级比之前选中的运算符低2. 如果当前优先级与已选择的相同，选择最后出现的运算符
      if (current_priority <= op_priority) {
          op_priority = current_priority;
          main_op = i;
          printf("main_op(i) = %d",main_op);  //
      }
    }
  return main_op;
}



// 表达式求值的递归函数
long long eval(int p, int q) {
  if (p > q) {
    // Bad expression
    return 0;
  } else if (p == q) {
    // Single token. For now this token should be a number.
    if (tokens[p].type == TK_NUMBER) {
      return atoll(tokens[p].str);
    } else if (tokens[p].type == TK_HEX_NUMBER) {
      return hex_to_decimal(tokens[p].str);
    } else {
      printf("Invalid token in eval!\n");
      exit(1);
    }
  } else if (check_parentheses(p, q) == true) {
    // The expression is surrounded by a matched pair of parentheses.
    // If that is the case, just throw away the parentheses.
    return eval(p + 1, q - 1);
  } else {
    int op = find_main_op(p, q);
    uint32_t val1 = eval(p, op - 1);
    uint32_t val2 = eval(op + 1, q);


    switch (tokens[op].type) {
      case TK_PLUS: return val1 + val2;
      case TK_MINUS: return val1 - val2;
      case TK_MULTIPLY: return val1 * val2;
      case TK_DIVIDE:
        if (val2 == 0) {
          printf("Division by zero\n");
          exit(1);
        }
        return val1 / val2;
      case TK_MODULO:
        if (val2 == 0) {
          printf("Division by zero\n");
          exit(1);
        }
        return val1 % val2;
      case  TK_EQ: if(val1 == val2) return 1;else return 0;
      case  TK_NE: if(val1 != val2) return 1;else return 0;
      case  TK_DEREF: return vaddr_read(val2,4);  //!!!
      case  TK_LT: if(val1 < val2) return 1;else return 0;  
      case  TK_GT: if(val1 > val2) return 1;else return 0; 
      case  TK_GE: if(val1 >= val2) return 1;else return 0;
      case  TK_LE: if(val1 <= val2) return 1;else return 0; 
      default:
        printf("Invalid operator in eval\n");
        exit(1);
    }
  }
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  for (int i = 0; i <NR_REGEX; i++) {
	if (tokens[i].type == TK_MULTIPLY && (i == 0 || tokens[i - 1].type == '('||tokens[i - 1].type==TK_EQ||tokens[i - 1].type==TK_NE)) {
        	tokens[i].type = TK_DEREF;
    		printf(" i = %d\n",i);
    		printf(" The type is: %d\n",tokens[i].type);
  }
}

  *success = true;
  return eval(0, nr_token - 1);
}


// 增加释放动态分配内存的函数
void free_tokens() {
  for (int i = 0; i < nr_token; i++) {
    free(tokens[i].str);
  }
}
