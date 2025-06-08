#include "os.h"

extern void trap_vec(void);

void trap_init(void) {
    w_mtvec((reg_t)trap_vec);
}

reg_t trap_handler(reg_t epc, reg_t cause) {
    reg_t return_pc = epc;
    reg_t cause_code =  cause & MCAUSE_MASK_ECODE;

    if (cause & MCAUSE_MASK_INTERRUPT) {
        // interrupt
        switch (cause_code) {
        default:
            printf("Unknown interrput = %ld\n", cause_code);
            break;
        }
    } else {
        // exception
        printf("Exception, cause = %ld\n", cause_code);
        // panic("Oops! what can I do?\n");
        return_pc += 4;
    }

    return return_pc;
}

void trap_test(void) {
    *(int *)0x0 = 0xff;     // ERROR: access invalid address

    uart_puts("Yeah! I am return back from trap.\n");
}