#include <am.h>
#include <klib.h>

#define VGACTL_ADDR 0xa0000100
#define FB_ADDR     0xa1000000

#define SCREEN_W 400
#define SCREEN_H 300

static uint32_t screen_width() {
  return SCREEN_W;
}

static uint32_t screen_height() {
  return SCREEN_H;
}

static uint32_t screen_size() {
  return screen_width() * screen_height() * sizeof(uint32_t);
}

void __am_gpu_init() {
  // 初始化VGA控制器
  int i;
  uint32_t *fb = (uint32_t *)(FB_ADDR);
  for (i = 0; i < screen_width() * screen_height(); i++) {
    fb[i] = 0;
  }
  // 设置屏幕大小
  outl(VGACTL_ADDR, (screen_height() << 16) | screen_width());
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true,
    .has_accel = false,
    .width = screen_width(),
    .height = screen_height(),
    .vmemsz = screen_size()
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  uint32_t *pixels = ctl->pixels;
  int cp_bytes = sizeof(uint32_t) * (w < screen_width() - x ? w : screen_width() - x);
  uint32_t *fb = (uint32_t *)(FB_ADDR + (y * screen_width() + x) * sizeof(uint32_t));
  for (int j = 0; j < h && y + j < screen_height(); j++) {
    memcpy(fb, pixels, cp_bytes);
    pixels += w;
    fb += screen_width();
  }

  if (ctl->sync) {
    // VGA同步操作
    outl(VGACTL_ADDR + 4, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}