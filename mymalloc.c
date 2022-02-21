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
//I think for malloc start of with a base case for initializing the first struct to be in the memory array with the given number of bytes.
//Then when you need to malloc use the header to loop through to the end and add the new struct there.
//Issue I see with that is that there could be empty space in between two structs that will not be used if the one in the middle is freed. 
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
