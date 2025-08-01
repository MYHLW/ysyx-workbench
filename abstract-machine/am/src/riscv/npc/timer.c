#include <am.h>

// 定义RTC地址，与main_new.cpp中保持一致
#define RTC_ADDR 0xa0000048

static uint64_t boot_time = 0;

void __am_timer_init() {
  // 初始化启动时间
  boot_time = *(volatile uint64_t *)RTC_ADDR;
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  // 读取当前时间并计算uptime
  uint64_t current_time = *(volatile uint64_t *)RTC_ADDR;
  uptime->us = current_time - boot_time;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  // 简单实现，返回固定时间
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 1;
  rtc->month  = 1;
  rtc->year   = 2023;
}
