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
        printf("\n");
        counter += 1;
        pointer = (ListNode*)((char*)pointer + pointer->size);
        
    }
}

//malloc
//I think for malloc if it is uninitialized start with a struct that occupies the given bytes from memory[0] and return a pointer to that and make a new (next) struct for the rest of the memory and set that to free.
//Then on subsequent calls you would go through the linked list until you find one that is free and large enough then you would cut that based on how many bytes are needed and create a new linked list with the remaining unused bytes which would still be free.
void *mymalloc(size_t size, char *file, int line){
    
    //If malloc 0, return null
    if(size == 0){
        return NULL;
    }

    ListNode *ptr;
    ptr = (ListNode*)memory;
    size += sizeof(ptr);
    if (ptr->size == 0){
        ptr->size = mem_size;
        ptr->free = 0;
    }
    //Iterate through linked list until a free block has been reached
    while(ptr != NULL && ptr->size != 0){
        if(ptr->size >= size && ptr->free == 0){
            ListNode *new;

            new = (ListNode*)((char*)ptr+size);    
            new->size = ptr->size - size;
            new->free = 0;

            ptr->size = size;
            ptr->free = 1;
            return (char*)ptr+1;
        }
        ptr = (ListNode*)((char*)ptr + ptr->size);
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
        if(pointer == (ListNode*)((char*)ptr - 1)){
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
            pointer = (ListNode*)memory;
        }
        else{
            pointer = next;
        }
    }
    return;
}


int main(int argc, char* argv[]){

}
