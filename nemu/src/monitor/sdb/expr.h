#ifndef __EXPR_H__
#define __EXPR_H__

#include <stdint.h>
#include <stdbool.h>

// 定义操作符的类型
enum {
  TK_NOTYPE = 256,
  TK_EQ,           // ==
  TK_NE,           // !=
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
  TK_NOT,          //! (未启用)
  TK_UNARY_MINUS,  // 一元 -
  TK_HEX_NUMBER,   // 十六进制数
  TK_LT,           // <
  TK_LE,           // <=
  TK_GT,           // >
  TK_GE,           // >=
  TK_DEREF = 276,  // 指针解引用
  TK_REG           // 寄存器名
};

// 定义规则结构体
struct rule {
  const char *regex;  // 正则表达式
  int token_type;     // 对应的 token 类型
};

// 定义 token 结构体
typedef struct token {
  int type;           // token 类型
  char *str;          // token 字符串
} Token;

// 函数声明
extern void init_regex(void);
extern bool make_token(char *e);
extern long long hex_to_decimal(char *hex_str);
extern bool check_parentheses(int p, int q);
extern int find_main_op(int p, int q);
extern long long eval(int p, int q);
extern word_t expr(char *e, bool *success);
extern void free_tokens(void);

#endif // __EXPR_H__

