#include "os.h"

/* interval ~= 1s */
#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ
#define MAX_TIMER_NUM 10

static uint32_t tick = 0;
static struct timer timer_list[MAX_TIMER_NUM];

static void timer_load(int interval) {
    /* each CPU has a separate source of timer interrupts. */
    int id = (int)r_mhartid();
    *(uint64_t *)CLINT_MTIMECMP(id) = *(uint64_t *)CLINT_MTIME + interval;
}

void timer_init(void) {
    for (int i = 0; i < MAX_TIMER_NUM; i++) {
        timer_list[i].func = NULL;
        timer_list[i].arg = NULL;
        timer_list[i].timeout_ticks = 0;
    }

    timer_load(TIMER_INTERVAL);

    // enable machine-mode timer interrupt
    w_mie(r_mie() | MIE_MTIE);
}


struct timer* timer_create(
        void (*func)(void *arg),
        void *arg,
        uint32_t timeout_ticks) {
    struct timer *t = NULL;

    spin_lock();

    for (int i = 0; i < MAX_TIMER_NUM; i++) {
        if (timer_list[i].func == NULL) {
            t = &timer_list[i];
            t->func = func;
            t->arg = arg;
            t->timeout_ticks = tick + timeout_ticks;
            break;
        }
    }

    spin_unlock();

    return t;
}

void timer_delete(struct timer *t) {
    spin_lock();

    for (int i = 0; i < MAX_TIMER_NUM; i++) {
        if (t == &timer_list[i]) {
            timer_list[i].func = NULL;
            timer_list[i].arg = NULL;
            timer_list[i].timeout_ticks = 0;
            break;
        }
    }

    spin_unlock();
}

void timer_check(void) {
    struct timer *t;

    for (int i = 0; i < MAX_TIMER_NUM; i++) {
        t = &timer_list[i];
        if (t->func && (tick >= t->timeout_ticks)) {
            t->func(t->arg);
            t->func = NULL;
            t->arg = NULL;
            t->timeout_ticks = 0;
        }
    }

}

void timer_handler(void) {
    tick++;
    printf("tick: %d\n", tick);

    // run soft timer func
    timer_check();

    timer_load(TIMER_INTERVAL);
    schedule();
}