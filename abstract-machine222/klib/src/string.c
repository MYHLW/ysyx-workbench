#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// ====================== 字符串操作函数 ======================

/**
 * @brief 计算字符串长度（不含终止符）
 * @param s 输入字符串
 * @return 字符串长度
 */
size_t strlen(const char *s) {
    const char *p = s;
    while (*p != '\0') p++; // 遍历直到'\0'
    return p - s; // 返回指针偏移量（字符数）
}

/**
 * @brief 复制字符串（含终止符）
 * @param dst 目标缓冲区
 * @param src 源字符串
 * @return 目标缓冲区指针（dst）
 */
char *strcpy(char *dst, const char *src) {
    char *ret = dst; // 保存初始地址
    while ((*dst++ = *src++) != '\0'); // 复制字符直到'\0'
    return ret;
}

/**
 * @brief 按长度复制字符串
 * @param dst 目标缓冲区
 * @param src 源字符串
 * @param n 最大复制字节数
 * @return 目标缓冲区指针（dst）
 * @note 若src长度不足n，用'\0'填充剩余空间
 */
char *strncpy(char *dst, const char *src, size_t n) {
    char *ret = dst;
    size_t i;
    for (i = 0; i < n && *src != '\0'; i++) { // 复制有效字符
        *dst++ = *src++;
    }
    for (; i < n; i++) { // 填充剩余空间为'\0'
        *dst++ = '\0';
    }
    return ret;
}

/**
 * @brief 拼接字符串
 * @param dst 目标字符串（需足够空间）
 * @param src 源字符串
 * @return 目标字符串指针（dst）
 */
char *strcat(char *dst, const char *src) {
    char *ret = dst;
    // 定位到dst末尾的'\0'
    while (*dst != '\0') dst++;
    // 复制src到dst末尾
    while (*src != '\0') *dst++ = *src++;
    *dst = '\0'; // 添加终止符
    return ret;
}

/**
 * @brief 字典序比较字符串
 * @param s1 字符串1
 * @param s2 字符串2
 * @return 差值：0（相等），负数（s1<s2），正数（s1>s2）
 */
int strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) { // 逐字符比较
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2; // 避免符号扩展问题
}

/**
 * @brief 按长度比较字符串
 * @param s1 字符串1
 * @param s2 字符串2
 * @param n 最大比较字节数
 * @return 差值：0（前n字节相等），负数/正数（首个差异字节）
 */
int strncmp(const char *s1, const char *s2, size_t n) {
    size_t i;
    for (i = 0; i < n && *s1 != '\0' && *s2 != '\0'; i++) {
        if (*s1 != *s2) return (unsigned char)*s1 - (unsigned char)*s2; // 提前返回差异
    }
    if (i == n) return 0; // 比较完n字节无差异
    return (unsigned char)*s1 - (unsigned char)*s2; // 处理'\0'差异
}

// ====================== 内存操作函数 ======================

/**
 * @brief 填充内存块
 * @param s 内存块指针
 * @param c 填充值（仅低8位有效）
 * @param n 填充字节数
 * @return 原始指针（s）
 */
void *memset(void *s, int c, size_t n) {
    unsigned char *p = s; // 转换为字节指针
    while (n-- > 0) *p++ = (unsigned char)c; // 逐字节填充
    return s;
}

/**
 * @brief 安全内存移动（处理重叠区域）
 * @param dst 目标地址
 * @param src 源地址
 * @param n 移动字节数
 * @return 目标地址指针（dst）
 */
void *memmove(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    if (d < s) { // 正向复制（dst在src前或无重叠）
        while (n-- > 0) *d++ = *s++;
    } else { // 反向复制（dst在src后，防止覆盖）
        d += n; // 指向目标末尾
        s += n; // 指向源末尾
        while (n-- > 0) *--d = *--s; // 从后往前复制
    }
    return dst;
}

/**
 * @brief 内存复制（不处理重叠）
 * @param dst 目标地址
 * @param src 源地址
 * @param n 复制字节数
 * @return 目标地址指针（dst）
 */
void *memcpy(void *dst, const void *src, size_t n) {
    return memmove(dst, src, n); // 直接复用memmove（非重叠时等价）
}

/**
 * @brief 内存块比较
 * @param s1 内存块1
 * @param s2 内存块2
 * @param n 比较字节数
 * @return 差值：0（相等），负数（s1<s2），正数（s1>s2）
 */
int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    while (n-- > 0) {
        if (*p1 != *p2) return *p1 - *p2; // 返回首个差异字节
        p1++;
        p2++;
    }
    return 0; // 完全相等
}

#endif