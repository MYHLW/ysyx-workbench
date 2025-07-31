#include <am.h>
#include <nemu.h>
#include <riscv/riscv.h>

void __am_timer_init() {
}
//这个函数的功能是获取系统启动到当前的累计运行时间（以微秒为单位），并将结果存储在传入的AM_TIMER_UPTIME_T结构体指针中。
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t low_time = inl(RTC_ADDR);                     //设备寄存器为64位 将64位功能拆分成两个32位设备寄存器
  uint32_t high_time = inl(RTC_ADDR+4);
  uptime->us = (uint64_t)low_time + (((uint64_t) high_time) << 32);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
