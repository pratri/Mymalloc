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
//I think for malloc start of with the chunk pointing to the start of the array which is free.
//Then when you need to malloc, split the chunk according to how many bytes you need and have the next pointer pointing to the other part of the chunk you split
//Also needs somethign to check if there's enough space
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
