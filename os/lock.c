/****
 * 当前是单核os，所以加锁可以用关闭中断来
 * 防止进程被调度。
 * 
 * 多核系统，需要使用原子指令来实现，如amoswap
 */
#include "os.h"

int spin_lock(void) {
    w_mstatus(r_mstatus() & ~MSTATUS_MIE);
    return 0;
}

int spin_unlock(void) {
    w_mstatus(r_mstatus() | MSTATUS_MIE);
    return 0;
}