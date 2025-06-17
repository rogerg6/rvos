#include "os.h"
#include "syscall.h"


int sys_gethid(unsigned int *hid) {
    printf("--> %s, arg0=%p\n", __FUNCTION__, hid);

    if (!hid)
        return -1;
    else {
        *hid = r_mhartid();
        return 0;
    }
}


void do_syscall(struct context *ctx) {
    uint32_t syscall_num = ctx->a7;

    switch (syscall_num) {
    case SYS_gethid:
        ctx->a0 = sys_gethid((unsigned int *)ctx->a0);
        break;
    default:
        printf("Unknown syscall num = %d\n", syscall_num);
    }
}