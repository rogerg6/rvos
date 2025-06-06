#include "os.h"

extern void switch_to(struct context *ctx);

#define STACK_SIZE 1024

uint8_t __attribute__((aligned(16))) task_stack[STACK_SIZE];
struct context ctx_task;

void task_delay(volatile int count) {
    count *= 50000;
    while (count--);
}

void user_task0(void) {
    uart_puts("Task0 is created\n");
    while (1) {
        uart_puts("Task0: Running...\n");
        task_delay(1000);
    }
}

static void w_mscratch(reg_t x) {
    asm volatile ("csrw mscratch, %0" : : "r"(x));
}

void sched_init(void) {
    w_mscratch(0);

    ctx_task.ra = (reg_t)user_task0;
    ctx_task.sp = (reg_t)&task_stack[STACK_SIZE];
}


void schedule(void) {
    struct context *next = &ctx_task;
    switch_to(next);
}