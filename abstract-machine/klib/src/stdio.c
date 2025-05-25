#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>



#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);  // 初始化可变参数列表

    char *ptr = out;    // 指向输出缓冲区的指针
    const char *str;    // 临时存储字符串参数
    int num;            // 临时存储整数参数
    char num_buf[32];   // 存储整数转换后的字符串

    while (*fmt) {
        if (*fmt != '%') {
            *ptr++ = *fmt++;  // 普通字符直接复制
            continue;
        }

        fmt++;  // 跳过 '%'
        switch (*fmt) {
            case 's':  // 处理 %s
                str = va_arg(ap, char*);
                while (*str) {
                    *ptr++ = *str++;
                }
                fmt++;
                break;

            case 'd':  // 处理 %d
                num = va_arg(ap, int);
                // 将整数转换为字符串（反向存储）
                char *p = num_buf + sizeof(num_buf) - 1;
                *p = '\0';
                int is_negative = 0;

                if (num < 0) {
                    is_negative = 1;
                    num = -num;
                }

                do {
                    *--p = '0' + (num % 10);
                    num /= 10;
                } while (num > 0);

                if (is_negative) {
                    *--p = '-';
                }

                // 将转换后的数字复制到输出缓冲区
                while (*p) {
                    *ptr++ = *p++;
                }
                fmt++;
                break;

            default:  // 不支持的格式，直接复制 '%' 和后面的字符
                *ptr++ = '%';
                *ptr++ = *fmt++;
                break;
        }
    }

    *ptr = '\0';  // 确保字符串以 '\0' 结尾
    va_end(ap);   // 清理可变参数列表

    return ptr - out;  // 返回写入的字符数（不包括 '\0'）
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif

