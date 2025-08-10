#include "loader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

uint32_t img_size = 0;
// 加载二进制镜像（.bin等）
static void load_image(const char* filename) {
    FILE* fp = std::fopen(filename, "rb");
    if (!fp) { 
        std::perror("fopen failed"); 
        std::exit(EXIT_FAILURE); 
    }
    size_t sz = std::fread(memory, 1, MEM_SIZE, fp);
    std::fclose(fp);
    std::printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n",
                filename, sz, MEM_BASE);
    img_size = sz;  // 更新全局变量img_size
}

// 加载HEX格式程序（.hex）
static void load_hex(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::perror("open hex file failed");
        std::exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos == std::string::npos) continue;

        // 解析地址（word地址 -> 字节地址）
        std::string addrStr = line.substr(0, pos);
        uint32_t wordAddr = std::stoul(addrStr, nullptr, 16);
        uint32_t baseByte = wordAddr * 4;

        // 解析指令数据（小端存储）
        std::string data = line.substr(pos + 1);
        std::istringstream iss(data);
        std::string tok;
        uint32_t idx = 0;
        while (iss >> tok) {
            uint32_t instr = std::stoul(tok, nullptr, 16);
            for (int b = 0; b < 4; b++) {
                memory[baseByte + idx * 4 + b] = (instr >> (8 * b)) & 0xFF;
            }
            idx++;
        }
    }
    std::printf("Loaded hex program '%s' into memory at 0x%08X\n", filename, MEM_BASE);
}

// 根据文件后缀选择加载方式（对外暴露的接口）
void load_program(const char* filename) {
    std::string fn(filename);
    auto pos = fn.rfind('.');
    if (pos != std::string::npos && fn.substr(pos) == ".hex") {
        load_hex(filename);
    } else {
        load_image(filename);
    }
}