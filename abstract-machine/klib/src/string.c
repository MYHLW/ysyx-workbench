#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  const char *p = s;
    // 遍历字符串直到遇到 '\0'
    while (*p != '\0') {
        p++;
    }
    // 返回字符数（不包含终止符）
    return p - s;
}

char *strcpy(char *dst, const char *src) {
    char *ret = dst; // 保存目标指针初始位置
    // 循环复制字符直到源字符串终止符
    while ((*dst++ = *src++) != '\0') {
        ; // 空循环体，仅通过赋值移动指针
    }
    return ret; // 返回目标字符串起始地址
}

char *strncpy(char *dst, const char *src, size_t n) {
    char *ret = dst;
    size_t i;
    // 复制最多 n 个字符
    for (i = 0; i < n && *src != '\0'; i++) {
        *dst++ = *src++;
    }
    // 如果复制长度不足 n，用 '\0' 填充剩余空间
    for (; i < n; i++) {
        *dst++ = '\0';
    }
    return ret;
}

char *strcat(char *dst, const char *src) {
    char *ret = dst;
    // 移动指针到目标字符串末尾（'\0' 位置）
    while (*dst != '\0') {
        dst++;
    }
    // 复制源字符串到目标末尾
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0'; // 添加终止符
    return ret;
}

int strcmp(const char *s1, const char *s2) {
    // 逐个字符比较，直到出现差异或终止符
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    // 返回差值：
    // - 0：相等
    // - 负数：s1 < s2（ASCII 值更小）
    // - 正数：s1 > s2
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    size_t i;
    // 比较最多 n 个字符
    for (i = 0; i < n && *s1 != '\0' && *s2 != '\0'; i++) {
        if (*s1 != *s2) {
            return (unsigned char)*s1 - (unsigned char)*s2; // 提前返回差异值
        }
        s1++;
        s2++;
    }
    // 处理长度相等或剩余字符为 '\0' 的情况
    if (i == n) { // 已比较完 n 个字符，无差异
        return 0;
    } else { // 其中一个字符串先到达 '\0'
        return (unsigned char)*s1 - (unsigned char)*s2;
    }
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s; // 转换为字节指针
    // 逐个字节填充值 c
    while (n-- > 0) {
        *p++ = (unsigned char)c; // 仅保留低8位
    }
    return s; // 返回原始指针
}

void *memmove(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    
    // 处理重叠区域：根据 dst 和 src 的相对位置选择复制方向
    if (d < s) {
        // 正向复制（不重叠或 dst 在 src 之前）
        while (n-- > 0) {
            *d++ = *s++;
        }
    } else {
        // 反向复制（重叠且 dst 在 src 之后）
        d += n;  // 指向目标末尾
        s += n;  // 指向源末尾
        while (n-- > 0) {
            *--d = *--s;  // 从后向前复制
        }
    }
    
    return dst;
}

void *memcpy(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    
    // 逐字节复制（可优化为按字长复制）
    while (n-- > 0) {
        *d++ = *s++;
    }
    
    return dst;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    
    // 逐字节比较
    while (n-- > 0) {
        if (*p1 != *p2) {
            return *p1 - *p2;  // 返回首个不同字节的差值
        }
        p1++;
        p2++;
    }
    
    return 0;  // 内存块完全相同
}

#endif
