#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)

typedef struct _listnode{
    // Number of bytes in memory block
    int size;
    //0 if free, 1 if used
    int free;
    struct _listnode *next;
} ListNode;

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#endif
