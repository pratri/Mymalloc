#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int col;
    FILE *ptr;
    //Only scan argv if there are enough inputs
    if (argc>2){
        col = atoi(argv[1]);
        ptr = fopen(argv[2], "r");
    }
    else{
        perror("ERROR");
        return -1;
    }
    //If file name given does not exist
    if(ptr == NULL)
    {
        perror("ERROR");
        return -1;                
    }
    //Read entire text file into char array and close the file
    fseek(ptr, 0L, SEEK_END);
    long fileLength = ftell(ptr);
    rewind(ptr);
    char* buffer = malloc(fileLength);
    fread(buffer, fileLength, 1, ptr);
    fclose(ptr);

    //Clear the file of its contents and reopen in append mode
    ptr = fopen(argv[2], "w");
    fclose(ptr);
    ptr = fopen(argv[2], "a");

    int count = 0;
    int wordSize = 0;
    long i = 0;
    //Iterate through the char array
    while(i<fileLength){
        long pos = i;

        if(buffer[i] == '\t'){
            fprintf(ptr, "%c", buffer[i]);
            i++;
            count = 0;
        }
        if(buffer[i]!=' '){
            //Determine the length of a word
            while(buffer[pos]!=' '){
                pos++;
                wordSize++;
                count++;
            }
            //If there is not enough space in the col to hold the word, tab to the next line
            if(wordSize > (col - count)){
                fprintf(ptr, "%c", '\t');
                count = 0;
            }
            //Write the word to the text file
            while(i<pos){
                fprintf(ptr, "%c", buffer[i]);
                i++;
                count++;
            }
            //If the word is greater than or equal to the col width, it gets a line to itself
            if(wordSize >= col){
                fprintf(ptr, "%c", '\t');
                wordSize = 0;
                count = 0;
            }
        }
        //Only keep one white space if there are multiple consecutive white spaces
        if(buffer[pos]==' '){
            while(buffer[pos]==' '){
                pos++;
                i++;
            }
            fprintf(ptr, "%c", ' ');
            count++;
        }
    }
    
    fclose(ptr);
    free(buffer);

    return 0;
}
