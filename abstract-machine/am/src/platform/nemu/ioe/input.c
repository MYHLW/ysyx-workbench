#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  // 1) 从 MMIO 地址直接读 4 字节寄存器
  volatile uint32_t *mmio = (volatile uint32_t *)KBD_ADDR;
  uint32_t key = *mmio;

  // 2) 如果返回 AM_KEY_NONE（0），说明队列空，无事件
  if (key == AM_KEY_NONE) {
    kbd->keydown = false;
    kbd->keycode = AM_KEY_NONE;
    return;
  }

  // 3) 有事件：最高位表示按下/释放，低 15 位是真正的扫描码
  kbd->keydown = (key & KEYDOWN_MASK) != 0;
  kbd->keycode = key & ~KEYDOWN_MASK;
}
