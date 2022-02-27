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
    struct _listnode *next;
} ListNode;

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
    //Start linked list if this is the first malloc
    if (ptr->size == 0){
        ptr->size = mem_size - 1;
        ptr->free = 0;
        ptr->next = NULL;
    }
    //Iterate through linked list until a free block has been reached
    while(ptr->free == 1){
        ptr = ptr->next;
    }
    //Check if there is enough free space in this block
    if (ptr->size >= size){
        //Only make a new node if the chunk can be fragmented
        if(ptr->size > size){
            ListNode *new;
            new = (ListNode*)((char*)ptr+size);
            new->size = ptr->size - size - 1;
            new->free = 0;
            //If ptr is the latest chunk
            if(ptr->next == NULL){
                new->next = NULL;
            }
            //If this chunk isn't the last
            else{
                new->next = ptr->next;
            }
            ptr->next = new;        
            ptr->size = size;
        }
        //Update ptr parameters
        ptr->free = 1;
    }
    //There is not enough space in this chunk
    else{
        //Continue iterating through list to find a large enough free chunk
        while(ptr!=NULL){
            ptr = ptr->next;
            //Return null if end of the list is reached with no free chunk found
            if(ptr == NULL){
                printf("Error: not enough memory\n");
                return NULL;
            }
            //If a large enough chunk that is free is found, allocate it
            if(ptr->size >= size && ptr->free == 0){
                if(ptr->size > size){
                    ListNode *new;
                    new = (ListNode*)((char*)ptr+size);
                    new->size = ptr->size - size - 1;
                    new->free = 0;
                    //If ptr is the latest chunk
                    if(ptr->next == NULL){
                        new->next = NULL;
                    }
                    //If this chunk isn't the last
                    else{
                        new->next = ptr->next;
                    }
                    ptr->next = new;        
                    ptr->size = size;
                }
                //Update ptr parameters
                ptr->free = 1;
                break;
            }
        }
    }
    return (char*)ptr+1;
}



//free
void myfree(void *ptr, char *file, int line){
    ListNode* pointer = (ListNode*)memory;
    //Checking if the memory has not been malloced to
    if (pointer->size == 0){
        printf("ERROR, Memory is uninitialized");
        return;
    }
    //Callling free with an address not obtained from malloc() or not at the start of a chunk
    int checker = 0;
    while(pointer!=NULL){
        if((char*)pointer == (char*)ptr-1){
            checker = 1;
            break;
        }
        pointer = pointer->next;
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
    while(pointer->next != NULL){ 
        if(pointer->free == 0 && pointer->next->free == 0){
            pointer->size = pointer->size + pointer->next->size + 1;
            pointer->next = pointer->next->next;
            pointer = (ListNode*)memory;
        }
        else{
            pointer = pointer->next;
        }
    }
    return;
}
//Has to coalesce adjacent byte chunks into one chunk
//Error:
//Calling free with an address not obtained from malloc
//Calling free with an address not at the start of a chunk
//Calling free a second time on the same pointer

//Optional: Function that can detect memory leaks

int main(int argc, char* argv[]){

}
