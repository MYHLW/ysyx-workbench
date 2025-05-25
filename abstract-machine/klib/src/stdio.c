#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

static void itoa(char *buf, int base, int value) {
    char *p = buf;
    char *start = buf;
    unsigned int num;
    int is_negative = 0;

    // 处理负数（仅十进制）
    if (base == 10 && value < 0) {
        is_negative = 1;
        num = -value;
        *p++ = '-';
    } else {
        num = (unsigned int)value;
    }

    // 转换数字
    do {
        int rem = num % base;
        *p++ = (rem < 10) ? rem + '0' : rem - 10 + 'a';
    } while (num /= base);

    // 反转字符串
    if (is_negative) start++; // 跳过负号
    char *end = p - 1;
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
    *p = '\0'; // 终止符
}



#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    char *p = out;
    char buf[32]; // 临时缓冲区，用于数字转换

    va_start(ap, fmt); // 初始化可变参数列表

    while (*fmt) {
        if (*fmt != '%') {
            *p++ = *fmt++; // 直接复制普通字符
            continue;
        }

        fmt++; // 跳过%
        switch (*fmt) {
            case 'd': // 十进制整数
                itoa(buf, 10, va_arg(ap, int));
                strcpy(p, buf);
                p += strlen(buf);
                break;

            case 'x': // 十六进制整数（小写）
                itoa(buf, 16, va_arg(ap, unsigned int));
                strcpy(p, buf);
                p += strlen(buf);
                break;

            case 's': // 字符串
                strcpy(p, va_arg(ap, char*));
                p += strlen((char*)p); // 直接使用目标指针计算长度（避免重复计算）
                break;

            case 'c': // 字符
                *p++ = (char)va_arg(ap, int); // 恢复为char类型
                break;

            case '%': // 转义%
                *p++ = '%';
                break;

            default: // 未知格式，保留%和原始字符
                *p++ = '%';
                *p++ = *fmt;
                break;
        }
        fmt++; // 移动到下一个格式字符
    }

    *p = '\0'; // 添加字符串终止符
    va_end(ap); // 清理可变参数列表

    return p - out; // 返回写入的字符数（不含终止符）
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif

