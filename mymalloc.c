#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define mem_size 4096
static char memory[mem_size];

//Basic struct can add stuff later
struct ListNode{
    int bytes;
    //0 if free 1 if not free
    int free;
    int data;
    struct ListNode *next;
};

//malloc
//I think for malloc if it is uninitialized start with a struct that occupies the given bytes from memory[0] and return a pointer to that and make a new (next) struct for the rest of the memory and set that to free.
//Then on subsequent calls you would go through the linked list until you find one that is free and large enough then you would cut that based on how many bytes are needed and create a new linked list with the remaining unused bytes which would still be free.
void *mymalloc(size_t size, char *file, int line){

}



//free
void myfree(void *ptr, char *file, int line){
    
}
//Has to coalesce adjacent byte chunks into one chunk
//Error:
//Calling free with an address not obtained from malloc
//Calling free with an address not at the start of a chunk
//Calling free a second time on the same pointer

//Optional: Function that can detect memory leaks



int main(int argc, char* argv[]){

}
