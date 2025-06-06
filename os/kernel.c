
#include "os.h"

#define TEST 0

#if TEST
extern void page_test(void);
#endif

void start_kernel(void) {
    uart_init();
    uart_puts("Hello RVOS ! ");
    printf("Author: %c%s%d\n", 'r', "ogerg", 6);

    page_init();
#if TEST
    page_test();
#endif

    sched_init();
    schedule();

    uart_puts("Never go here !\n");
    while (1) { }
}