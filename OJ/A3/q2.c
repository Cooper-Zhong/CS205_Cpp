#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct mmpool mmpool_t;
typedef struct mmpool_data mmpool_data_t;
typedef struct mmpool_large mmpool_large_t;

#define MMPOOL_MAX_FAILED 4
struct mmpool_data
{
    uint8_t *last;
    uint8_t *end;
    mmpool_t *next;
    size_t failed;
};

struct mmpool_large
{
    mmpool_large_t *next;
    void *alloc;
};

#define MMPOOL_MAX_ALLOC (0x1000 - sizeof(mmpool_t))
#define MMPOOL_SIZE (0x1000 - sizeof(mmpool_t))
struct mmpool
{
    mmpool_data_t data;
    mmpool_t *current; // 非subpool的current指向最近的 failed<=MAX_FAILED 的pool
    mmpool_large_t *large;
};

mmpool_t *mmpool_create();
void *mmpool_alloc(mmpool_t *pool, size_t size);
mmpool_large_t *mmpool_alloc_large(size_t size);
void mmpool_free_large(mmpool_t *pool, void *p);
void mmpool_destroy(mmpool_t *pool);
void mmpool_reset(mmpool_t *pool);

/* Functions for tests */
/* ==BEGIN== */
void prt_mmpool_details(mmpool_t *pool)
{
    if (pool == NULL)
        return;
    puts("===MEMORY POOL DETAILS===");
    printf("POOL ADDRESS: %p\n", pool);
    printf("POOL SIZE (FOR EACH): %ul\n", MMPOOL_SIZE);
    printf("MAX ALLOCATION SIZE: %ul\n", MMPOOL_MAX_ALLOC);
    printf("MAX FAILED TIMES: %d\n", MMPOOL_MAX_FAILED);
    printf("CURRENT ACTIVE POOL ADDRESS: %p\n", pool->current);
    puts("\nSUB POOL DETAILS:");

    size_t count = 0;
    mmpool_t *cur = pool;
    while (cur != NULL)
    {
        printf("\t-> Sub pool #%lu, address=%p, free_space=%lu (bytes), failed=%lu\n",
               ++count, cur, (size_t)(cur->data.end - cur->data.last), cur->data.failed);
        cur = cur->data.next;
    }
    printf("SUB POOL COUNT: %lu\n", count);

    puts("\nLARGE BLOCK DETAILS: ");
    count = 0;
    mmpool_large_t *large = pool->large;
    while (large != NULL)
    {
        printf("\t-> Large block #%lu, address=%p\n", ++count, large);
        large = large->next;
    }
    printf("LARGE BLOCK COUNT: %lu\n", count);
    puts("===MEMORY POOL DETAILS END===\n");
}
/* ==END== */

mmpool_t *mmpool_create()
{
    mmpool_t *p = NULL;

    p = (mmpool_t *)malloc(sizeof(mmpool_t) + MMPOOL_SIZE);
    if (p != NULL)
    {
        p->data.last = (uint8_t *)p + sizeof(mmpool_t);
        p->data.end = p->data.last + MMPOOL_SIZE;
        p->data.next = NULL;
        p->data.failed = 0;

        p->current = p;
        p->large = NULL;
    }

    return p;
}

/* WRITE YOUR CODE HERE */
/* YOU ONLY NEED TO SUBMIT THIS PART */
/* ==BEGIN== */

/**
 * @brief Allocate a memory block from a memory pool.
 *
 * @param pool the pointer of the memory pool.
 * @param size size of the memory block (in bytes).
 *
 * @return void* pointer of the start address of the memory block.
 */
void *mmpool_alloc(mmpool_t *pool, size_t size)
{
    if (size > MMPOOL_MAX_ALLOC)
    {
        mmpool_large_t *large = mmpool_alloc_large(size);
        if (large == NULL)
            return NULL;
        if (pool->large == NULL)
        {
            pool->large = large;
            return large->alloc;
        }
        mmpool_large_t *cur_large = pool->large;

        while (cur_large->next != NULL)
        {
            cur_large = cur_large->next;
        }
        cur_large->next = large;
        return large->alloc;
    }

    mmpool_t *cur = pool->current; // start from current
    mmpool_t *prev = NULL;
    while (cur != NULL)
    {
        if ((size_t)(cur->data.end - cur->data.last) >= size)
        { // enough space
            void *allocated = (void *)cur->data.last;
            cur->data.last += size;
            return allocated;
        }
        // not enough space
        else
        {
            cur->data.failed++;
            if (pool->current->data.failed > MMPOOL_MAX_FAILED)
            {
                pool->current = cur->data.next;
            }
            prev = cur;
            cur = cur->data.next;
        }
    }
    // run out of subpool
    mmpool_t *new_pool = mmpool_create();
    if (new_pool == NULL)
        return NULL;
    prev->data.next = new_pool;
    void *allocated = (void *)new_pool->data.last;
    new_pool->data.last += size;
    return allocated;
}

/**
 * @brief Allocate a large memory block by `malloc()`.
 * This function must be called by `mmpool_alloc()`. Do not manually call it.
 *
 * @param size size of the memory block (in bytes).
 *
 * @return mmpool_large_t* pointer of the start address of the memory block.
 */
mmpool_large_t *mmpool_alloc_large(size_t size)
{
    mmpool_large_t *large = (mmpool_large_t *)malloc(sizeof(mmpool_large_t));
    if (large == NULL)
        return NULL;
    large->alloc = malloc(size);
    if (large->alloc == NULL)
    {
        free(large);
        return NULL;
    }
    large->next = NULL;
    return large;
}

/**
 * @brief Free a large memory block from a memory pool.
 *
 * @param pool the pointer of the memory pool.
 * @param p `*alloc` of the large memory block.
 */
void mmpool_free_large(mmpool_t *pool, void *p)
{
    mmpool_large_t *cur = pool->large;
    mmpool_large_t *prev = NULL;

    while (cur != NULL)
    {
        if (cur->alloc == p) // found
        {
            if (prev != NULL)
            {
                prev->next = cur->next;
            }
            else
            {
                pool->large = NULL;
            }
            free(cur->alloc);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

/**
 * @brief Destroy a memory pool.Free all related memory.
 *
 * @param pool the pointer of the memory pool.
 */
void mmpool_destroy(mmpool_t *pool)
{
    mmpool_large_t *large = pool->large;
    while (large != NULL)
    {
        mmpool_large_t *temp = large;
        large = large->next;
        free(temp->alloc);
        free(temp);
    }

    mmpool_t *cur = pool;
    while (cur != NULL)
    {
        mmpool_t *temp = cur;
        cur = cur->data.next;
        free(temp);
    }
}

/**
 * @brief Reset a memory pool i.e.
 * reset `*current` to the pool itself, `*last` and `failed`;
 * free all large memory blocks.
 *
 * @param pool the pointer of the memory pool
 */
void mmpool_reset(mmpool_t *pool)
{
    pool->current = pool;
    pool->data.failed = 0;
    pool->data.last = (uint8_t *)pool + sizeof(mmpool_t);
    mmpool_large_t *large = pool->large;
    while (large != NULL)
    {
        mmpool_large_t *temp = large;
        large = large->next;
        free(temp->alloc);
        free(temp);
    }
    pool->large = NULL;

    mmpool_t *cur = pool->data.next;
    while (cur != NULL)
    {
        cur->current = cur;
        cur->data.failed = 0;
        cur->data.last = (uint8_t *)cur + sizeof(mmpool_t);
        cur = cur->data.next;
    }

}
/* ==END== */

#define MAX_POINTERS 100000

int main()
{
    int Q, q, op;
    size_t size;

    mmpool_t *pool;
    void *small[MAX_POINTERS], *big[MAX_POINTERS];
    size_t scnt = 0, bcnt = 0;

    scanf("%d", &Q);
    for (q = 0; q < Q; ++q)
    {
        scanf("%d", &op);
        printf("[DEBUG] Query: %d, Operator: %d\n", q, op);
        if (op == 1)
            pool = mmpool_create();
        else if (op == 2)
        {
            scanf("%lu", &size);
            if (size <= MMPOOL_MAX_ALLOC)
                small[scnt++] = mmpool_alloc(pool, size);
            else
                big[bcnt++] = mmpool_alloc(pool, size);
        }
        else if (op == 3)
            mmpool_free_large(pool, big[--bcnt]);
        else if (op == 4)
            mmpool_reset(pool);
        else if (op == 5)
        {
            mmpool_destroy(pool);
            pool = NULL;
        }
        else
            puts("UNKNOWN OPERATOR!");

        prt_mmpool_details(pool);
    }

    return 0;
}
