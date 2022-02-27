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

void printnode(){
    ListNode* pointer = (ListNode*)memory;
    int counter = 0;
    while(pointer != NULL && pointer->size != 0){
        printf("Counter: %d\n", counter);
        printf("Free: %d\n", pointer->free);
        printf("Size: %d\n", pointer->size);
        counter += 1;
        pointer = pointer->next;
        
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
    size += sizeof(ptr);
    //Start linked list if this is the first malloc
    if (ptr->size == 0){
        printf("Started linked list:\n");
        ptr->size = mem_size;
        ptr->free = 0;
        ptr->next = NULL;
        printf("PTRSIZE: %d\n", ptr->size);
        printf("PTR FREE: %d\n", ptr->free);
    }
    //Iterate through linked list until a free block has been reached
    while(ptr != NULL){
        printf("Checking for free\n");
        if(ptr->size >= size && ptr->free == 0){
            //Creates a new node that splits the chunk
            printf("SPLITTING NEW NODE\n");
            
            ListNode *new;
            new = (ListNode*)(ptr+size);
            
            
            new->size = ptr->size - size;
            new->free = 0;
            
            new->next = ptr->next;
           
            ptr->next = new;      
            ptr->size = size;
            ptr->free = 1;
            printf("PTR: size: %d\n", ptr->size);
            printf("PTR: free: %d\n", ptr->free);
            printf("New Size: %d\n", new->size);
            printf("New Free: %d\n", new->free);
            return ptr+1;
        }
        ptr = ptr->next;
    }
    printf("Error: not enough memory\n");
    return NULL;
            
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


int main(int argc, char* argv[]){
    char* c;
    for(int i = 0; i<100; i++){
        mymalloc(1, c, 5);
    }
    printnode();
    int* a = malloc(5*sizeof(int));
    for(int i = 0; i<5; i++){
        a[i] = i;
        printf("%d\n", a[i]);
    }

    
}
