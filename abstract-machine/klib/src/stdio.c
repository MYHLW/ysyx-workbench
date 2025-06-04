#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

// 辅助函数：整数转字符串（支持十进制、十六进制）
static void itoa(char *buf, int base, int value) {
    char *p = buf;
    char *start = buf;
    unsigned int num;
    int is_negative = 0;

    // 处理负数（仅十进制）
    if (base == 10 && value < 0) {
        is_negative = 1;
        num = -value;
        *p++ = '-'; // 记录负号
    } else {
        num = (unsigned int)value;
    }

    // 转换数字为字符
    do {
        int rem = num % base;
        *p++ = (rem < 10) ? rem + '0' : rem - 10 + 'a'; // 十六进制用小写a-f
    } while (num /= base);

    // 反转字符串以得到正确顺序
    if (is_negative) start++; // 跳过负号
    char *end = p - 1;
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
    *p = '\0'; // 添加字符串终止符
}

// vsprintf：使用va_list格式化到字符串（核心函数）
int vsprintf(char *out, const char *fmt, va_list ap) {
    char *p = out;
    char buf[32]; // 临时缓冲区，用于数字转换

    while (*fmt) {
        if (*fmt != '%') { // 普通字符直接复制
            *p++ = *fmt++;
            continue;
        }

        fmt++; // 跳过%
        switch (*fmt) {
            case 'd': { // 十进制整数
                int val = va_arg(ap, int);
                itoa(buf, 10, val);
                strcpy(p, buf);
                p += strlen(buf);
                break;
            }
            case 'x': { // 十六进制整数（小写）
                unsigned int val = va_arg(ap, unsigned int);
                itoa(buf, 16, val);
                strcpy(p, buf);
                p += strlen(buf);
                break;
            }
            case 's': { // 字符串
                char *str = va_arg(ap, char*);
                strcpy(p, str);
                p += strlen(str);
                break;
            }
            case 'c': { // 字符（int提升为char）
                *p++ = (char)va_arg(ap, int);
                break;
            }
            case '%': { // 转义%
                *p++ = '%';
                break;
            }
            default: { // 未知格式，保留%和原始字符
                *p++ = '%';
                *p++ = *fmt;
                fmt++; // 手动跳过当前字符（避免外层循环重复递增）
                break;
            }
        }
        fmt++; // 处理完当前格式符后，移动到下一个字符
    }

    *p = '\0'; // 确保字符串终止
    return p - out; // 返回写入的字符数（不含终止符）
}

// sprintf：可变参数版本，封装vsprintf
int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    int ret;
    va_start(ap, fmt);
    ret = vsprintf(out, fmt, ap);
    va_end(ap);
    return ret;
}

// printf：输出到标准输出，依赖am.h中的putstr
int printf(const char *fmt, ...) {
    va_list ap;
    // 移除 char buf[1024]; // 未使用，导致编译错误
    int ret;

    char buf[1024]; // 显式保留并使用（若确实需要）
    va_start(ap, fmt);
    ret = vsprintf(buf, fmt, ap); // 使用buf进行格式化
    va_end(ap);

    putstr(buf); // 通过am.h中的函数输出字符串
    return ret;
}

// snprintf：带长度限制的安全格式化
int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list ap;
    char *p = out;
    char buf[32];
    size_t remaining = n; // 剩余可用空间（包含终止符）

    if (n == 0) return 0; // n为0时不写入

    va_start(ap, fmt);

    while (*fmt && remaining > 1) { // 至少保留1字节给'\0'
        if (*fmt != '%') { // 普通字符
            *p++ = *fmt++;
            remaining--;
            continue;
        }

        fmt++; // 跳过%
        switch (*fmt) {
            case 'd': case 'x': { // 数字类型
                int base = (*fmt == 'd') ? 10 : 16;
                unsigned int val = (*fmt == 'd') ? va_arg(ap, int) : va_arg(ap, unsigned int);
                itoa(buf, base, val);
                size_t len = strlen(buf);
                size_t copy_len = (len < remaining - 1) ? len : remaining - 1; // 保留终止符空间
                strncpy(p, buf, copy_len);
                p += copy_len;
                remaining -= copy_len;
                break;
            }
            case 's': { // 字符串
                char *str = va_arg(ap, char*);
                size_t len = strlen(str);
                size_t copy_len = (len < remaining - 1) ? len : remaining - 1;
                strncpy(p, str, copy_len);
                p += copy_len;
                remaining -= copy_len;
                break;
            }
            case 'c': { // 字符
                *p++ = (char)va_arg(ap, int);
                remaining--;
                break;
            }
            case '%': { // 转义%
                *p++ = '%';
                remaining--;
                break;
            }
            default: { // 未知格式
                *p++ = '%';
                *p++ = *fmt;
                remaining -= 2; // 占用2字节
                fmt++; // 手动跳过当前字符
                break;
            }
        }
        fmt++; // 移动到下一个格式符
    }

    *p = '\0'; // 强制添加终止符
    return p - out; // 返回实际写入的字符数（不含终止符）
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    char *p = out;
    char buf[32]; // 临时缓冲区，用于数字转换
    size_t remaining = n;

    if (n == 0) return 0;

    while (*fmt && remaining > 1) {
        if (*fmt != '%') {
            *p++ = *fmt++;
            remaining--;
            continue;
        }

        fmt++;
        switch (*fmt) {
            case 'd': case 'x': { // 数字类型
                int base = (*fmt == 'd') ? 10 : 16;
                unsigned int val = (*fmt == 'd') ? va_arg(ap, int) : va_arg(ap, unsigned int);
                itoa(buf, base, val); // 使用buf存储转换后的字符串
                size_t len = strlen(buf);
                size_t copy_len = (len < remaining - 1) ? len : remaining - 1;
                strncpy(p, buf, copy_len);
                p += copy_len;
                remaining -= copy_len;
                break;
            }
            case 's': { // 字符串
                char *str = va_arg(ap, char*);
                size_t len = strlen(str);
                size_t copy_len = (len < remaining - 1) ? len : remaining - 1;
                strncpy(p, str, copy_len);
                p += copy_len;
                remaining -= copy_len;
                break;
            }
            case 'c': { // 字符
                *p++ = (char)va_arg(ap, int);
                remaining--;
                break;
            }
            case '%': { // 转义%
                *p++ = '%';
                remaining--;
                break;
            }
            default: { // 未知格式
                *p++ = '%';
                *p++ = *fmt;
                remaining -= 2;
                fmt++;
                break;
            }
        }
        fmt++;
    }

    *p = '\0';
    return p - out;
}

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
// 条件编译保留原panic逻辑（若未定义原生实现）
// 此处已实现完整功能，panic可移除或作为fallback
#endif