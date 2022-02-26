#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void *mymalloc(size_t size, char *file, int line){
    ListNode *ptr;
    ptr = (ListNode*)memory;
    //Start linked list if this is the first malloc
    if (ptr->free == 0){
        ptr->size = mem_size - 1;
        ptr->free = 0;
        ptr->next = NULL;
    }
    //Iterate through linked list until a free block has been reached
    while(ptr->free == 1){
        ptr = ptr->next;
    }
    //Check if there is enough free space in this block
    if (ptr->size > size){
        ListNode *new;
        new = (ListNode*)(ptr+size);
        new->size = ptr->size - size - 1;
        new->free = 0;
        new->next = NULL;

        ptr->size = size;
        ptr->free = 1;
        ptr->next = new;
    }
    else{
        while(ptr!=NULL){
            ptr = ptr->next;
            if(ptr == NULL){
                printf("Error: not enough memory\n");
                break;
            }
            if(ptr->size > size && ptr->free == 0){
                ListNode *new;
                new = (ListNode*)(ptr+size);
                new->size = ptr->size - size - 1;
                new->free = 0;
                new->next = NULL;

                ptr->size = size;
                ptr->free = 1;
                ptr->next = new;
                break;
            }
        }
    }
    return ptr+1;
}

void myfree(void *ptr, char *file, int line){
    
}
int main(int argc, char* argv[]){

}   
