#include <am.h>
#include <nemu.h>

void __am_timer_init() {
}
//这个函数的功能是获取系统启动到当前的累计运行时间（以微秒为单位），并将结果存储在传入的AM_TIMER_UPTIME_T结构体指针中。
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  // 读取RTC寄存器的低32位和高32位
  uint32_t low = inl(RTC_ADDR);       // 低32位时间值
  uint32_t high = inl(RTC_ADDR + 4);  // 高32位时间值

  // 拼接成64位微秒数，存储到uptime结构体中
  uptime->us = ((uint64_t)high << 32) | low;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
