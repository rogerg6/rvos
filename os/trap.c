#include "os.h"

extern void trap_vec(void);

void trap_init(void) {
    w_mtvec((reg_t)trap_vec);
}

void external_interrupt_handler(void) {
    int irq = plic_claim();

    if (irq == UART0_IRQ) {
        uart_isr();
    } else {
        printf("Unexpected irq = %d\n", irq);
    }

    if (irq)
        plic_complete(irq);
}

reg_t trap_handler(reg_t epc, reg_t cause) {
    reg_t return_pc = epc;
    reg_t cause_code =  cause & MCAUSE_MASK_ECODE;

    if (cause & MCAUSE_MASK_INTERRUPT) {
        // interrupt
        switch (cause_code) {
        case 3:
			uart_puts("software interrupt!\n");
			break;
        case 7:
			uart_puts("timer interrupt!\n");
            timer_handler();
			break;
        case 11:
			uart_puts("external interruption!\n");
            external_interrupt_handler();
			break;
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