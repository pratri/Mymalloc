#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"
#define mem_size 4096

static char memory[mem_size];

//Basic struct can add stuff later
typedef struct _listnode{
    // Number of bytes in memory block
    int size;
    //0 if free, 1 if used
    int free;
} ListNode;

void printnode(){
    ListNode* pointer = (ListNode*)memory;
    int counter = 0;
    while(pointer != NULL && pointer->size != 0){
        printf("Counter: %d\n", counter);
        printf("Free: %d\n", pointer->free);
        printf("Size: %d\n", pointer->size);
        counter += 1;
        pointer = (ListNode*)((char*)pointer + pointer->size);
        
    }
}

//malloc
//I think for malloc if it is uninitialized start with a struct that occupies the given bytes from memory[0] and return a pointer to that and make a new (next) struct for the rest of the memory and set that to free.
//Then on subsequent calls you would go through the linked list until you find one that is free and large enough then you would cut that based on how many bytes are needed and create a new linked list with the remaining unused bytes which would still be free.
void *mymalloc(size_t size, char *file, int line){
    
    //If someone mallocs 0 
    if(size == 0){
        return NULL;
    }

    ListNode *ptr;
    ptr = (ListNode*)memory;
    //Sets the size to the size of the total chunk not just the data
    //printf("OLD SIZE: %zu\n", size);
    size += sizeof(ptr);
    //printf("NEW SIZE: %zu\n", size);
    //Start linked list if this is the first malloc
    if (ptr->size == 0){
        printf("Started linked list:\n");
        ptr->size = mem_size;
        ptr->free = 0;
    }
    //Iterate through linked list until a free block has been reached
    printf("NEW MALLOC\n");
    printf("SIZE: %zu\n", size);
    while(ptr != NULL && ptr->size != 0){
        //printf("Checking for free\n");
        printf("PTR TESTING SIZE: %zu, PTR size: %d, ptr free: %d, address: %p\n", size, ptr->size, ptr->free, ptr);
        printnode();
        if(ptr->size >= size && ptr->free == 0){
            //Creates a new node that splits the chunk
            //printf("SPLITTING NEW NODE\n");
            printf("SIZE: %zu\n", size);
            ListNode *new;

            new = (ListNode*)((char*)ptr+size);
            printf("PTR: size: %d\n", ptr->size);     
            new->size = ptr->size - size;
            
            new->free = 0;
            
            printf("New Size: %d ", new->size);
            printf("New Free: %d\n", new->free);
            //ptr->next = new;      
            ptr->size = size;
            printf("PTR NEW SIZE: %d, new is: %d", ptr->size, new->size);
            ptr->free = 1;
            
            printf(" PTR: free: %d\n", ptr->free);
            
            printf("Last: %p ", ptr);
            printf("NEW: %p ", new);
            printf("New Size: %d ", new->size);
            printf("New Free: %d\n", new->free);
            return ptr+1;
        }
        ptr = (ListNode*)((char*)ptr + ptr->size);
        printf("PTR SIZE: %d\n", ptr->size);
    }
    printf("Error: not enough memory\n");
    return NULL;
            
}

//free
void myfree(void *ptr, char *file, int line){
    //Checking if the ptr is not in the memory array at all

    ListNode* pointer = (ListNode*)memory;
    //Checking if the memory has not been malloced to
    if (pointer->size == 0){
        printf("ERROR, Memory is uninitialized");
        return;
    }

    //Callling free with an address not obtained from malloc() or not at the start of a chunk
    int checker = 0;
    
    while(pointer!=NULL && pointer->size!=0){
        //printf("ADD pointer: %p, ptr: %p\n", pointer, (ListNode*)ptr -1);
        if(pointer == (ListNode*)ptr - 1){
            checker = 1;
            break;
        }
        pointer = (ListNode*)((char*)pointer + pointer->size);
    }
    if(checker == 0){
        printf("Given pointer input is not valid\n");
        return;
    }
    else{
        //If the chunk is being used, free it
        if(pointer->free == 1){
            printf("FREED\n");
            pointer->free = 0;
        }
        //If the chunk is already freed, return error
        else{
            printf("This chunk has already been freed\n");
            return;
        }
      
    }
    //Coalesce empty adjacent memory chunks
    pointer = (ListNode*)memory;
    ListNode* next = (ListNode*)((char*)pointer + pointer->size);
    while(next!= NULL && next->size!=0){ 
        next = (ListNode*)((char*)pointer + pointer->size);
        if(pointer->free == 0 && next->free == 0){
            pointer->size = pointer->size + next->size;
        }
        pointer = next;
    }
    return;
}


int main(int argc, char* argv[]){
    char* c;
    
    mymalloc(128, c, 5);
    mymalloc(64, c, 5);
    mymalloc(4, c, 5);
    mymalloc(256, c, 5);
    mymalloc(512, c, 5);
    mymalloc(256, c, 5);
    mymalloc(512, c, 5);
    printnode();
    //int* a = malloc(5*sizeof(int));
    // for(int i = 0; i<5; i++){
    //     a[i] = i;
    //     printf("%d\n", a[i]);
    // }

    
}
