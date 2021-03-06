#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

#define mem_size 4096
static char memory[mem_size];

void *mymalloc(size_t size, char *file, int line){
    
    //If malloc 0, return null
    if(size == 0){
        return NULL;
    }

    ListNode *ptr;
    ptr = (ListNode*)memory;
    //Make size the size of the whole chunk including the pointer
    size += sizeof(ptr);
    //Case where memory array is unitialized since ptr-> size = 0 then initialize it by setting the size to the whole memory array and set it to free
    if (ptr->size == 0){
        ptr->size = mem_size;
        ptr->free = 0;
    }
    //Iterate through linked list until a free block has been reached
    while(ptr != NULL && ptr->size != 0){
        //Check if the chunk is large enough and is free
        if(ptr->size >= size && ptr->free == 0){
            //Split the chunk into two chunks and set the first one to the size requested and set it to not free and the rest would be the othe chunk
            ListNode *new;
            new = (ListNode*)((char*)ptr+size);    
            new->size = ptr->size - size;
            new->free = 0;

            ptr->size = size;
            ptr->free = 1;
            //Return the payload
            return (char*)ptr+1;
        }
        ptr = (ListNode*)((char*)ptr + ptr->size);
    }
    //No available chunk that was large enough and free
    printf("ERROR: not enough memory available. File: %s, Line: %d\n", file, line);
    return NULL;
            
}
void myfree(void *ptr, char *file, int line){
    //Checking if the ptr is not in the memory array at all
    if((char*)ptr < memory || (char*)ptr > memory + mem_size){
        printf("ERROR: pointer not in memory array, File: %s, Line: %d\n", file, line);
        return;
    }
    ListNode* pointer = (ListNode*)memory;
    //Checks if the memory array was never initizlized (malloc was never called)
    if (pointer->size == 0){
        printf("ERROR: Memory array is uninitialized, please malloc first. File: %s, Line: %d\n", file, line);
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
        printf("ERROR: given pointer is not at the start of a chunk. File: %s, Line: %d\n", file, line);
        return;
    }
    else{
        //If the chunk is being used, free it
        if(pointer->free == 1){
            pointer->free = 0;
        }
        //If the chunk is already freed, return error
        else{
            printf("ERROR: this chunk has already been freed. File: %s, Line: %d\n", file, line);
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
