#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int randnum(){
    int num = (rand() % 10);
    return num;
}
int main(int argc, char* argv[]){
    for (int i=0; i<120; i++){
        char* ptr = malloc(1);
        free(ptr);
    }
    char* ptrArray[120];
    for (int i=0; i<120; i++){
        ptrArray[i] = malloc(1);
    }
    for (int i=0; i<120; i++){
        free(ptrArray[i]);
    }
    int a = 0;
    for(int i=0; i<120; i++){
        int random = randnum();
        if(random < 5){
            ptrArray[a] = malloc(1);
            a++;
        }
        else{
            if(a == 0){
                break;
            }
            else{
                a = a-1;
                free(ptrArray[a]);
            }
        }
    }
}
