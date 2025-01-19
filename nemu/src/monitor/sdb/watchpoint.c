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

#include "sdb.h"
#include <stdio.h>
#include <assert.h>


#define NR_WP 32

extern uint32_t expr(char *e, bool *success); //

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expr[128]; // 表达式
  uint32_t value;   // 当前值
} WP;

static WP wp_pool[NR_WP] = {};  //监视点结构的池
static WP *head = NULL, *free_ = NULL;  //还有两个链表head和free_, 其中head用于组织使用中的监视点结构, free_用于组织空闲的监视点结构,

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp() {
  if (free_ == NULL) {
    assert(0);
    }
  WP *wp = free_;// 获取空闲的监视点 
  // 将free_链表中的第一个元素移出
  free_ = free_->next;
  // 将该监视点结构添加到使用中的链表head中
  wp->next = head;
  head = wp;
  
  return wp;
}

void free_wp(WP *wp) {
  if (wp == NULL) {
    return;  
  }
  // 从使用中的链表中移除wp
  WP **pp = &head;
  while (*pp != NULL && *pp != wp) {
    pp = &(*pp)->next;
  }

  if (*pp != NULL) {
    *pp = wp->next;  // 将wp从链表中移除
  }
 // 将wp归还到free_链表
  wp->next = free_;
  free_ = wp;
}


void display_wp() {
  if (head == NULL) {
    printf("No watchpoints.\n");
    return;
  }

  printf("Num\tType\t\tExpression\t\tValue\n");
  for (WP *wp = head; wp != NULL; wp = wp->next) {
    printf("%d\twatchpoint\t%s\t\t0x%x\n", wp->NO, wp->expr, wp->value);
  }
}

WP* create_watchpoint(char *expr_str) {
  WP *wp = new_wp();  // 从监视点池申请一个新的监视点
  strncpy(wp->expr, expr_str, sizeof(wp->expr) - 1);  // 保存表达式
  wp->expr[sizeof(wp->expr) - 1] = '\0';  // 确保字符串以NULL结尾
  wp->value = expr(wp->expr, NULL);  // 计算表达式的初始值并存储
  return wp;
}

void delete_watchpoint(int wp_num) {
  WP **pp = &head;
  while (*pp != NULL) {
    if ((*pp)->NO == wp_num) {
      WP *to_free = *pp;
      *pp = to_free->next;  // 从链表中移除该监视点
      free_wp(to_free);  // 将监视点归还到空闲池
      printf("Watchpoint %d deleted.\n", wp_num);
      return;
    }
    pp = &(*pp)->next;
  }
  printf("Watchpoint %d not found.\n", wp_num);
}   





