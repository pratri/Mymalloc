#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

int main(int argc, char* argv[]){
    double avg_time;

    //Stress Test #1
    clock_t begin1 = clock();
    for(int i=0; i<50; i++){
            for (int i=0; i<120; i++){
            char* ptr = malloc(1);
            free(ptr);
        }   
    }    
    clock_t end1 = clock();
    avg_time = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("Stress Test 1: the average time is %f seconds\n", avg_time/50);

    char* ptrArray[120];

    //Stress Test #2
    clock_t begin2 = clock();
    for(int i=0; i<50; i++){
        for (int i=0; i<120; i++){
            ptrArray[i] = malloc(1);
        }
        for (int i=0; i<120; i++){
            free(ptrArray[i]);
        }
    }
    clock_t end2 = clock();
    avg_time = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("Stress Test 2: the average time is %f seconds\n", avg_time/50);
    
    //Stress Test #3
    clock_t begin3 = clock();
    for (int i=0; i<50; i++){
        int a = 0;
        int malloc_call = 0;
        while(malloc_call!=120){
            int random = rand()%10;
            if(random < 5){
                ptrArray[a] = malloc(1);
                a++;
                malloc_call++;
            }
            else{
                if(a == 0){
                    ptrArray[a] = malloc(1);
                    a++;
                    malloc_call++;
                }
                else{
                    a--;
                    free(ptrArray[a]);
                }
            }
        }
        //Free all remaining chunks
        while(a!=0){
            a--;
            free(ptrArray[a]);
        }
    }
    clock_t end3 = clock();
    avg_time = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("Stress Test 3: the average time is %f seconds\n", avg_time/50);

    //Custom Test 1
    clock_t begin4 = clock();
    for (int i=0; i<50; i++){
        for(int i=0; i<120; i++){
            char* test = malloc(4088);
            free(test);
        }
    }
    clock_t end4 = clock();
    avg_time = (double)(end4 - begin4) / CLOCKS_PER_SEC;
    printf("Custom Test 1: the average time is %f seconds\n", avg_time/50);

    //Custom Test 2
    clock_t begin5 = clock();
    for (int i=0; i<50; i++){
        for (int i=0; i<100; i++){
            int random = rand()%10;
            while(random==0){
                random = rand()%10;
            }
            ptrArray[i] = malloc(random);
        }
        for (int i=0; i<100; i++){
            free(ptrArray[i]);
        }
    }
    clock_t end5 = clock();
    avg_time = (double)(end5 - begin5) / CLOCKS_PER_SEC;
    printf("Custom Test 2: the average time is %f seconds\n", avg_time/50);
}
