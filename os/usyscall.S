#include "syscall.h"

.global gethid


# 系统调用传参规范
# a7 存放系统调用号
# a0 - a5 存放系统调用参数
# a0 存放系统调用返回值
gethid:
    li a7, SYS_gethid

    # ecall会产生一个同步的异常，切换到M-mode, 获取
    # 系统信息，最后调用mret再次返回U-mode
    ecall
    ret