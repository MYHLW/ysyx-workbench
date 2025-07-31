#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t key = inl(KBD_ADDR);
  if (key == AM_KEY_NONE) {
    kbd->keydown = false;
    kbd->keycode = AM_KEY_NONE;
    return;
  }
  kbd->keydown = key & KEYDOWN_MASK ? true : false;// 用位掩码判断按键是否按下
  kbd->keycode = key & ~KEYDOWN_MASK;//用按位与运算把 key 的第 16 位清零，仅保留低 15 位的键值部分。
}
