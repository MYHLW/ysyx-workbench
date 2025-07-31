#include <am.h>
#include <nemu.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint64_t low = inl(RTC_ADDR); //读取 uptime 的 低 32 位
  uint64_t high = inl(RTC_ADDR + 4); //读取 uptime 的 高 32 位(4字节偏移)  注意：这里的 low 和 high 是从硬件寄存器中读取的
  uptime->us = (high << 32) | low; // 将高位左移 32 位后与低位合并成一个 64 位
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
