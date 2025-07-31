#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  printf("1\n");
  uint32_t key = inl(KBD_ADDR);
  kbd->keydown = key & KEYDOWN_MASK ? true : false;// 用位掩码判断按键是否按下
  kbd->keycode = key & ~KEYDOWN_MASK;//用按位与运算把 key 的第 16 位清零，仅保留低 15 位的键值部分。
}
