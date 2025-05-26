#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

// printf：将格式化字符串输出到标准输出（控制台）。
// sprintf：将格式化字符串写入字符数组（不限制长度，需确保缓冲区足够大）。
// snprintf：将格式化字符串写入字符数组，最多写入n字节（包含终止符\0），防止缓冲区溢出。
// vsprintf：与sprintf类似，但使用已初始化的可变参数列表va_list，用于函数复用参数列表。
// vsnprintf：与snprintf类似，但使用已初始化的可变参数列表va_list，安全限制写入长度。

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
    va_list ap;
    int len;
    char buf[1024]; // 临时缓冲区（根据需要调整大小）

    va_start(ap, fmt);
    len = vsprintf(buf, fmt, ap); // 先格式化到临时缓冲区
    va_end(ap);

    putstr(buf); // 使用 am.h 中的 putstr 输出字符串
    return len; // 返回输出字符数
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    char *p = out;
    char buf[32]; // 临时缓冲区
    
    while (*fmt) {
        if (*fmt != '%') {
            *p++ = *fmt++; // 复制普通字符
            continue;
        }

        fmt++; // 跳过%
        switch (*fmt) {
            case 'd': // 十进制整数
                itoa(buf, 10, va_arg(ap, int));
                strcpy(p, buf);
                p += strlen(buf);
                break;

            case 'x': // 十六进制整数
                itoa(buf, 16, va_arg(ap, unsigned int));
                strcpy(p, buf);
                p += strlen(buf);
                break;

            case 's': // 字符串
                strcpy(p, va_arg(ap, char*));
                p += strlen(p);
                break;

            case 'c': // 字符
                *p++ = (char)va_arg(ap, int);
                break;

            case '%': // 转义%
                *p++ = '%';
                break;

            default: // 未知格式，保留%和字符
                *p++ = '%';
                *p++ = *fmt;
                break;
        }
        fmt++;
    }

    *p = '\0'; // 终止符
    return p - out; // 返回写入长度
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
    va_list ap;
    char *p = out;
    char buf[32];
    size_t remaining = n; // 剩余可用空间

    va_start(ap, fmt);

    while (*fmt && remaining > 0) { // 确保不超过 n 字节
        if (*fmt != '%') {
            if (remaining > 1) { // 保留空间给终止符
                *p++ = *fmt++;
                remaining--;
            }
            continue;
        }

        fmt++; // 跳过%
        switch (*fmt) {
            case 'd': case 'x': // 数字转换
                itoa(buf, *fmt == 'd' ? 10 : 16, 
                     *fmt == 'd' ? va_arg(ap, int) : va_arg(ap, unsigned int));
                size_t len = strlen(buf);
                if (remaining > len + 1) { // 剩余空间足够
                    strcpy(p, buf);
                    p += len;
                    remaining -= len;
                } else { // 空间不足，填充剩余空间
                    if (remaining > 1) *p = '\0'; // 确保终止符
                    goto end;
                }
                break;

            case 's': // 字符串复制
                char *s = va_arg(ap, char*);
                size_t slen = strlen(s);
                size_t copy_len = (slen < remaining - 1) ? slen : remaining - 1;
                strncpy(p, s, copy_len);
                p += copy_len;
                remaining -= copy_len;
                break;

            case 'c': // 字符
                if (remaining > 1) {
                    *p++ = (char)va_arg(ap, int);
                    remaining--;
                }
                break;

            case '%': // 转义%
                if (remaining > 1) {
                    *p++ = '%';
                    remaining--;
                }
                break;

            default: // 未知格式
                if (remaining > 1) {
                    *p++ = '%';
                    *p++ = *fmt;
                    remaining -= 2;
                }
                break;
        }
        fmt++;
    }

    end:
    if (remaining > 0) *p = '\0'; // 确保以'\0'结尾
    va_end(ap);
    return p - out; // 返回实际写入长度（不含终止符）
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    char *p = out;
    char buf[32];         // 临时缓冲区，用于数字转换
    size_t remaining = n; // 剩余可用空间

    if (n == 0) {
        return 0; // 若 n 为 0，直接返回（不写入任何内容）
    }

    while (*fmt && remaining > 1) { // 保留至少 1 字节用于终止符
        if (*fmt != '%') {
            *p++ = *fmt++;
            remaining--;
            continue;
        }

        fmt++; // 跳过 %
        switch (*fmt) {
            case 'd': // 十进制整数
                itoa(buf, 10, va_arg(ap, int));
                break;

            case 'x': // 十六进制整数
                itoa(buf, 16, va_arg(ap, unsigned int));
                break;

            case 's': { // 字符串
                char *s = va_arg(ap, char*);
                size_t len = strlen(s);
                if (len < remaining) {
                    strcpy(p, s);
                    p += len;
                    remaining -= len;
                } else {
                    strncpy(p, s, remaining - 1);
                    p += remaining - 1;
                    remaining = 1; // 仅剩终止符空间
                }
                fmt++;
                continue; // 跳过后续处理
            }

            case 'c': // 字符
                *p++ = (char)va_arg(ap, int);
                remaining--;
                fmt++;
                continue; // 跳过后续处理

            case '%': // 转义 %
                *p++ = '%';
                remaining--;
                fmt++;
                continue; // 跳过后续处理

            default: // 未知格式，保留 % 和原始字符
                *p++ = '%';
                *p++ = *fmt;
                remaining -= 2;
                fmt++;
                continue; // 跳过后续处理
        }

        // 处理数字转换结果（d/x）
        size_t len = strlen(buf);
        if (len < remaining) {
            strcpy(p, buf);
            p += len;
            remaining -= len;
        } else {
            strncpy(p, buf, remaining - 1);
            p += remaining - 1;
            remaining = 1; // 仅剩终止符空间
        }
        fmt++;
    }

    *p = '\0'; // 确保字符串以 '\0' 结尾
    return p - out; // 返回实际写入的字符数（不含终止符）
}

#endif
