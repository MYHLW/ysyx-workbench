    .section .text
    .globl _start
_start:
    addi x1, x0, 10      # x1 = 0 + 10 = 10
    addi x2, x1, 5       # x2 = 10 + 5 = 15
    addi x3, x2, -3      # x3 = 15 - 3 = 12
    addi x4, x3, 0       # x4 = x3
    addi x5, x4, 1       # x5 = x4 + 1 = 13
