#include <stdio.h>
#include <stdlib.h>

#define mem_size 4096
static char memory[mem_size];

#include "mymalloc.h"

int main(int argc, char* argv[]){
    //Start of the linked list
    ListNode head = headNode();
    //Remaining memory
    int mem = head.size;
}   
