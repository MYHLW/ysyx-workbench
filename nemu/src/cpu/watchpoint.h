#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include <stdint.h>

// 最大监视点数量
#define NR_WP 32
// 表达式最大长度
#define MAX_EXPR_LEN 128

// 监视点结构体定义
typedef struct watchpoint {
  int NO;                    // 监视点编号
  struct watchpoint *next;   // 指向下一个监视点

  // 监视点表达式和当前值
  char expr[MAX_EXPR_LEN];   // 存储监视点的表达式
  uint32_t value;            // 存储监视点的当前值
} WP;

// 监视点池管理相关函数声明
void init_wp_pool(void);             // 初始化监视点池
WP* new_wp(void);                    // 从池中获取一个新的监视点
void free_wp(WP *wp);                // 将监视点归还到池中
void display_wp(void);               // 显示当前所有监视点

// 创建和删除监视点的函数声明
WP* create_watchpoint(char *expr_str);  // 创建新的监视点
void delete_watchpoint(int wp_num);     // 删除指定编号的监视点


void scan_watchpoint();

#endif // __WATCHPOINT_H__

