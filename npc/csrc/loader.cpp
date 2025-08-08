// loader.cpp
#include "loader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>

// 全局记录实际加载到 memory 的字节数，供 difftest 使用
// (在 loader.cpp 中定义，其他文件用 extern 引用)
size_t program_size = 0;

// 加载二进制镜像（.bin等）
static void load_image(const char* filename) {
    FILE* fp = std::fopen(filename, "rb");
    if (!fp) {
        std::perror("fopen failed");
        std::exit(EXIT_FAILURE);
    }
    size_t sz = std::fread(memory, 1, MEM_SIZE, fp);
    std::fclose(fp);
    program_size = sz;
    std::printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n",
                filename, sz, (unsigned)MEM_BASE);
}

// 加载HEX格式程序（.hex）
// 假设每行格式：<wordAddrHex>: <instr1> <instr2> ...
// wordAddr表示以word(4字节)为单位的地址（你原有实现如此）
static void load_hex(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::perror("open hex file failed");
        std::exit(EXIT_FAILURE);
    }
    std::string line;
    // 我们会追踪写入的最高字节下标，从而精确设置 program_size
    size_t max_written = 0;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos == std::string::npos) continue;

        // 解析地址（word地址 -> 字节地址）
        std::string addrStr = line.substr(0, pos);
        uint32_t wordAddr = 0;
        try {
            wordAddr = std::stoul(addrStr, nullptr, 16);
        } catch (...) {
            continue;
        }
        uint32_t baseByte = wordAddr * 4;

        // 解析指令数据（小端存储）
        std::string data = line.substr(pos + 1);
        std::istringstream iss(data);
        std::string tok;
        uint32_t idx = 0;
        while (iss >> tok) {
            uint32_t instr = 0;
            try {
                instr = std::stoul(tok, nullptr, 16);
            } catch (...) {
                instr = 0;
            }
            // 写入内存，注意越界检查
            size_t write_addr = (size_t)baseByte + (size_t)idx * 4;
            if (write_addr + 4 <= MEM_SIZE) {
                for (int b = 0; b < 4; b++) {
                    memory[write_addr + b] = (instr >> (8 * b)) & 0xFF;
                }
                if (write_addr + 4 > max_written) max_written = write_addr + 4;
            } else {
                std::fprintf(stderr, "load_hex: write out of bounds at 0x%zx (MEM_SIZE=%u)\n",
                             write_addr, (unsigned)MEM_SIZE);
                std::exit(EXIT_FAILURE);
            }
            idx++;
        }
    }
    if (max_written == 0) {
        // 如果文件为空或未写入，设成0
        program_size = 0;
    } else {
        program_size = max_written;
    }
    std::printf("Loaded hex program '%s' into memory at 0x%08X (size=%zu)\n",
                filename, (unsigned)MEM_BASE, program_size);
}

// 根据文件后缀选择加载方式（对外暴露的接口）
// load_program 在其他文件被调用（main_new.cpp）
void load_program(const char* filename) {
    std::string fn(filename);
    auto pos = fn.rfind('.');
    if (pos != std::string::npos && fn.substr(pos) == ".hex") {
        // 先清零内存
        std::memset(memory, 0, MEM_SIZE);
        load_hex(filename);
    } else {
        // binary image
        std::memset(memory, 0, MEM_SIZE);
        load_image(filename);
    }

    // 如果 program_size 超出 MEM_SIZE，修正（理论上不会发生）
    if (program_size > MEM_SIZE) program_size = MEM_SIZE;
}
