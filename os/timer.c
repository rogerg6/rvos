#include "os.h"

/* interval ~= 1s */
#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint32_t tick = 0;

static void timer_load(int interval) {
    /* each CPU has a separate source of timer interrupts. */
    int id = (int)r_mhartid();
    *(uint64_t *)CLINT_MTIMECMP(id) = *(uint64_t *)CLINT_MTIME + interval;
}

void timer_init(void) {
    timer_load(TIMER_INTERVAL);

    // enable machine-mode timer interrupt
    w_mie(r_mie() | MIE_MTIE);

    // enable machine-mode global interrupts
    w_mstatus(r_mstatus() | MSTATUS_MIE);
}

void timer_handler(void) {
    tick++;
    printf("tick: %d\n", tick);
    timer_load(TIMER_INTERVAL);

    schedule();
}