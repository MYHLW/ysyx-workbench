#include <am.h>

// 定义键盘地址，与main_new.cpp中保持一致
#define KBD_ADDR 0xa0000060

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  // 读取键盘状态
  uint32_t key = *(volatile uint32_t *)KBD_ADDR;
  
  // 检查是否有按键
  if (key != 0) {
    // 最高位表示按下状态
    kbd->keydown = (key & 0x8000) ? 1 : 0;
    // 低16位为键码
    kbd->keycode = key & 0x7fff;
  } else {
    kbd->keydown = 0;
    kbd->keycode = AM_KEY_NONE;
  }
}
