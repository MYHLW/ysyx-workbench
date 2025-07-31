#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  // 1. 直接把那个 NEMU 侧写好的 4 字节 MMIO 区域当成普通变量读
  uint32_t key = *(volatile uint32_t *)KBD_ADDR;

  // 2. 无事件就退出
  if (key == AM_KEY_NONE) {
    kbd->keydown = false;
    kbd->keycode = AM_KEY_NONE;
    return;
  }
  // 3. 按位剥离
  kbd->keydown = !!(key & KEYDOWN_MASK);
  kbd->keycode = key & ~KEYDOWN_MASK;
}

