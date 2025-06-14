#include "os.h"


void plic_init(void) {
    // read current hart ID
    int hart_id = r_tp();

    // set interrupt source priority
    *(uint32_t *)PLIC_PRIORITY(UART0_IRQ) = 1;

    // enable uart0
    *(uint32_t *)PLIC_MENABLE(hart_id, UART0_IRQ) = (1 << (UART0_IRQ % 32));

    /* each hart has a interrupt threshold, 
     * if interrupt source priority less than or equal threshold, interrupt will be ignored
     * otherwise it will be passed to hart
     */
    *(uint32_t *)PLIC_MTHRESHOLD(hart_id) = 0;

    // enable machine-mode external interrupt
    w_mie(r_mie() | MIE_MEIE);

    // enable machine-mode global interrupts
    w_mstatus(r_mstatus() | MSTATUS_MIE);   
}

/* 
 * get highest priority pending interrput and return it's irq number
 * or zero if there is no interrputs occur.
 * 
 * a successful claim will automatically clear the corresponding pending bit on
 * the interrupt source.
 * 
*/
int plic_claim(void) {
    int hart_id = r_tp();
    int irq = *(uint32_t *)PLIC_MCLAIM(hart_id);
    return irq;
}

/**
 * Writting the irq number to the complete register would
 * signal the PLIC we served this IRQ
*/
void plic_complete(int irq) {
    int hart_id = r_tp();
    *(uint32_t *)PLIC_MCOMPLETE(hart_id) = irq;
}
