#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define mem_size 4096
static char memory[mem_size];

//Basic struct can add stuff later
typedef struct _listnode{
    // Number of bytes in memory block
    int size;
    //0 if free, 1 if used
    int free;
    //Metadata location in memory array
    int location;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

ListNode headNode(){
    ListNode head;
    head.size = mem_size-1;
    head.free = 0;
    head.location = 0;
    head.next = NULL;
    head.prev = NULL;
    return head;
}

//Call when a new node is needed
ListNode newNode(ListNode *current, int bytes, int mem){
    //Creates new node at the end of the newly allocated block
    ListNode new;
    new.size = mem - bytes - 1;
    new.free = 0;
    new.location = current->location + bytes;
    new.next = NULL;
    new.prev = current;
    //Updates current node's parameters
    current->free = 1;
    current->size = bytes;
    current->next = &new;
    return new;
}
}
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
    //Start of the linked list
    ListNode head = headNode();
    //Remaining memory
    int mem = head.size;
}   
