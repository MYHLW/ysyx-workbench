#include <am.h>
#include <nemu.h>

void __am_timer_init() {
}
//这个函数的功能是获取系统启动到当前的累计运行时间（以微秒为单位），并将结果存储在传入的AM_TIMER_UPTIME_T结构体指针中。
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint64_t low = inl(RTC_ADDR);
  uint64_t high = inl(RTC_ADDR + 4);
  uptime->us = (high << 32) | low; // 读取RTC寄存器的低位和高位，合并为一个64位的时间戳
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
