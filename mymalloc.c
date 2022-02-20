#include <stdio.h>
#include <stdlib.h>

#define mem_size 4096
static char memory[mem_size];

//Basic struct can add stuff later
struct chunk_of_memory{
    int bytes;
    //0 if free 1 if not free
    int free;
    int data;
    struct chunk_of_memory *next;
};

//malloc
void *mymalloc(size_t size, char *file, int line){

}



//free
void free(void *ptr, char *file, int line){
    
}
//Has to coalesce adjacent byte chunks into one chunk
//Error:
//Calling free with an address not obtained from malloc
//Calling free with an address not at the start of a chunk
//Calling free a second time on the same pointer

//Optional: Function that can detect memory leaks



int main(int argc, char* argv[]){

}