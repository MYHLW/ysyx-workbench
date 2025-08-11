#include "../../include/memory.h"
#include <stdio.h>
#include <cassert>
#include "cli.h"
// //memory
//static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};



// paddr_t 如果没有定义，可以 typedef 一下
typedef uint32_t paddr_t;
extern uint8_t memory[];

uint8_t* guest_to_host(paddr_t paddr) {
    // 检查物理地址是否在模拟内存范围内
    assert(paddr >= MEM_BASE && paddr < MEM_BASE + MEM_SIZE);
    return memory + (paddr - MEM_BASE);
}
// paddr_t host_to_guest(uint8_t *haddr) { return haddr - pmem + CONFIG_MBASE; }

// word_t pmem_read(paddr_t addr, int len) {
//     uint8_t *host_addr = guest_to_host(addr);
//     switch (len) {
//         case 1: return *(uint8_t  *)host_addr;
//         case 2: return *(uint16_t *)host_addr;
//         case 4: return *(uint32_t *)host_addr;
//         default: Assert(0, "date_len not in 1/2/4");
//     }
// }

// void pmem_write(paddr_t addr, int len, word_t data) {
//     uint8_t *host_addr = guest_to_host(addr);
//     switch (len) {
//         case 1:*(uint8_t *)host_addr = data; break;
//         case 2:*(uint16_t *)host_addr = data; break;
//         case 4:*(uint32_t *)host_addr = data; break;
//         default: Assert(0, "data_len not in 1/2/4");
//     }
// }

// static void out_of_bound(paddr_t addr) {
//     //????
// }

// void init_mem() {
//     memset(pmem, 0, CONFIG_MSIZE);
// }

// bool in_pmem(paddr_t addr) {
//     return addr - CONFIG_MBASE < CONFIG_MSIZE;
// }


// word_t paddr_read(paddr_t addr, int len) {
//     if(in_pmem(addr)) return pmem_read(addr, len);
//     out_of_bound(addr);
//     return 0; 
// }

// void paddr_write(paddr_t addr, int len, word_t data) {
//     if(in_pmem(addr)) {
//         pmem_write(addr, len, data);
//         return ;
//     }
//     out_of_bound(addr);
// }


//加载img
long load_img(char *img_file) {
    FILE *fp;         // 文件指针
    long img_size = -1;  // 存储文件大小，默认-1表示失败

    // 以二进制只读模式打开文件
    // 二进制模式避免文本文件在不同系统下的换行符转换问题
    fp = fopen(img_file, "rb");
    if (fp == NULL) {
        // 文件打开失败（可能原因：文件不存在、权限不足等）
        return -1;
    }

    // 将文件指针移动到文件末尾（SEEK_END表示从文件末尾开始计算偏移）
    // 偏移量为0，表示直接定位到末尾
    if (fseek(fp, 0, SEEK_END) == 0) {
        // 获取当前文件指针位置（即文件大小，单位：字节）
        img_size = ftell(fp);
    }

    // 关闭文件（无论成功与否都要关闭，避免资源泄漏）
    fclose(fp);

    return img_size;
}