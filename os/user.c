#include "os.h"
#include "user_api.h"

#define DELAY 1000
extern void trap_test(void);

struct userdata {
    int counter;
    char *str;
};

static struct userdata person = {0, "rogerg6"};

void user_task0(void) {
    uart_puts("Task0 is created\n");
    task_yield();
    while (1) {
#ifdef USE_LOCK
        spin_lock();

        uart_puts("Task 0: Begin ... \n");
        for (int i = 0; i < 5; ++i) {
            uart_puts("Task0: Running...\n");
            task_delay(DELAY);
        }
        uart_puts("Task 0: End ... \n");

        spin_unlock();
#else
        uart_puts("Task0: Running...\n");
#if TEST
        trap_test();
#endif
        task_delay(DELAY);
#endif
    }
}

void user_task1(void) {
    uart_puts("Task1 is created\n");
    while (1) {
        uart_puts("Task1: Running...\n");
        task_delay(DELAY);
    }
}

void timer_func(void *arg) {
    if (arg == NULL)
        return;

    struct userdata *d = (struct userdata*)arg;
    ++d->counter;
    printf("=====> TIMEOUT: %s %d\n", d->str, d->counter);
}

void user_task2(void) {
    uart_puts("Task2 is created\n");

    struct timer *t1 = timer_create(timer_func, &person, 3);
    if (t1 == NULL)
        printf("Failed to create timer1.\n");

    struct timer *t2 = timer_create(timer_func, &person, 5);
    if (t2 == NULL)
        printf("Failed to create timer2.\n");

    struct timer *t3 = timer_create(timer_func, &person, 7);
    if (t3 == NULL)
        printf("Failed to create timer3.\n");

    while (1) {
        uart_puts("Task2: Running...\n");
        task_delay(DELAY);
    }
}

void user_task3(void) {
    unsigned int hid;
    uart_puts("Task2 is created\n");

    /* user-mode下无法读取mhartid寄存器，所以需要
     * 系统调用来获取
     */
#ifdef CONFIG_SYSCALL
    if (gethid(&hid) < 0)
        printf("ERR: gethid failed.\n");
    else
        printf("Current hart ID = %d\n", hid);
#else
    hid = r_mhartid();
    printf("Current hart ID = %d\n", hid);
#endif

    while (1) {
        uart_puts("Task3: Running...\n");
        task_delay(DELAY);
    }
}

void create_tasks(void) {
    // task_create(user_task0);
    task_create(user_task1);
    // task_create(user_task2);
    task_create(user_task3);
}