#include "os.h"

extern void switch_to(struct context *ctx);

#define MAX_TASKS  10
#define STACK_SIZE 1024

uint8_t __attribute__((aligned(16))) task_stack[MAX_TASKS][STACK_SIZE];     // 所有task的栈
struct context ctx_task[MAX_TASKS];     // 所有task的上下文
int current = -1;        // 当前task索引
int nr_tasks = 0;       // task个数

void sched_init(void) {
    w_mscratch(0);
}

void schedule(void) {
    if (nr_tasks < 0) {
        panic("Task num must > 0\n");
        return;
    }

    current = (current + 1) % nr_tasks;
    struct context *next = &ctx_task[current];
    switch_to(next);
}

void task_yield(void) {
    schedule();
}

int task_create(void(*task)(void)) {
    if (nr_tasks < MAX_TASKS) {
        ctx_task[nr_tasks].pc = (reg_t)task;
        ctx_task[nr_tasks].sp = (reg_t)&task_stack[nr_tasks][STACK_SIZE];
        nr_tasks++;
        return 0;
    } else {
        return -1;
    }
}

void task_delay(volatile int count) {
    count *= 50000;
    while (count--);
}
