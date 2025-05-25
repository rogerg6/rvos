#include "os.h"

extern ptr_t TEXT_START;
extern ptr_t TEXT_END;
extern ptr_t DATA_START;
extern ptr_t DATA_END;
extern ptr_t RODATA_START;
extern ptr_t RODATA_END;
extern ptr_t BSS_START;
extern ptr_t BSS_END;
extern ptr_t HEAP_START;
extern ptr_t HEAP_SIZE;

#define PAGE_SIZE 4096
#define PAGE_ORDER 12

#define PAGE_TAKEN  (uint8_t)(1<<0)
#define PAGE_LAST   (uint8_t)(1<<1)

struct Page {
    uint8_t flags;
};


struct Page *pages = NULL;
int npages = 0;
ptr_t alloc_start = 0;
ptr_t alloc_end = 0;

static inline void _clear(struct Page *page) {
    page->flags = 0;
}

static inline void _set_flag(struct Page *page, uint8_t flag) {
    page->flags |= flag;
}

static inline int _is_free(struct Page *page) {
    return !(page->flags & PAGE_TAKEN);
}

static inline int _is_last(struct Page *page) {
    return (page->flags & PAGE_LAST);
}

/**
 * @brief 以PAGE_SIZE大小对齐
 */
static inline ptr_t _align_page(ptr_t addr) {
    ptr_t order = (1 << PAGE_ORDER) - 1;
    return (addr + order) & (~order);
}

void page_init(void) {
    ptr_t heap_start_aligned = _align_page(HEAP_START);
    uint32_t real_heap_size = HEAP_SIZE - (heap_start_aligned - HEAP_START);
    int i;

    pages = (struct Page*)heap_start_aligned;
    alloc_start = _align_page(real_heap_size / PAGE_SIZE + heap_start_aligned);
    npages = (HEAP_SIZE - (alloc_start - HEAP_START)) / PAGE_SIZE;
    alloc_end = alloc_start + npages * PAGE_SIZE;

    printf("HEAP_START = 0x%p\n"
        "heap_start_aligned = 0x%p\n"
        "alloc_start = 0x%p\n"
        "HEAP_SIZE = %d\n"
        "npages = %d\n", 
        HEAP_START, heap_start_aligned, alloc_start, HEAP_SIZE, npages);

    // init pages
    for (i = 0; i < npages; ++i)
        pages[i].flags = 0;

	printf("TEXT:   %p -> %p\n", TEXT_START, TEXT_END);
	printf("RODATA: %p -> %p\n", RODATA_START, RODATA_END);
	printf("DATA:   %p -> %p\n", DATA_START, DATA_END);
	printf("BSS:    %p -> %p\n", BSS_START, BSS_END);
	printf("HEAP:   %p -> %p\n", alloc_start, alloc_end);
}

/**
 * @brief 分配页
 * @param n_pages 需要分配的页数
 * @retval 分配的起始页指针
 */
void* page_alloc(int n_pages) {
    int i;
    struct Page *page_i = pages, *page_j;

    /* 1. find free pages */
    for (i = 0; i < npages; ++i, page_i++) {
        if (_is_free(page_i)) {
            page_j = page_i;
            char found = 1;
            while (page_j - page_i + 1 < n_pages) {
                if (!_is_free(++page_j)) {
                    page_i = page_j;
                    found = 0;
                    break;
                }
            }
            
            /* 2. alloc & return start address */
            if (found) {
                for (i = 0; i < n_pages - 1; i++)
                    _set_flag(page_i + i, PAGE_TAKEN);
                _set_flag(page_i + i, PAGE_TAKEN | PAGE_LAST);
                return (void*)(alloc_start + (page_i - pages) * PAGE_SIZE);
            } 
        }
    }
    return NULL;

}

/**
 * @param p 待释放的内存区域起始地址
 */
void page_free(void *p) {
    if (!p || (ptr_t)p > alloc_end)
        return;

    struct Page *page = pages + ((ptr_t)p - alloc_start) / PAGE_SIZE;
    while (!_is_free(page)) {
        if (_is_last(page)) {
            _clear(page);
            break;
        } else {
            _clear(page);
            page++;
        }
    }
}

void page_test(void) {
    void *p1 = page_alloc(2);
    printf("p1 = %p\n", (ptr_t)p1);

    void *p2 = page_alloc(4);
    printf("p2 = %p\n", (ptr_t)p2);

    void *p3 = page_alloc(7);
    printf("p3 = %p\n", (ptr_t)p3);

    page_free(p2);

    void *p4 = page_alloc(5);
    printf("p4 = %p\n", (ptr_t)p4);
}