#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    int col;
    int file;

    DIR *dir;
    int isDir = 0;

    if(argc > 2){
        col = atoi(argv[1]);
        file = open(argv[2], O_RDWR);
    }
	else{
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    //If the second input is not a file, check if it is a directory
    if(file == -1){
        dir = opendir(argv[2]);
        //If the second input is not a directory, return error
        if(dir == NULL){
            perror("ERROR");
            exit(EXIT_FAILURE);
        }
        isDir = 1;
    }
    //You can't wrap to negative or 0 columns, so make the columns the minimum of 1
    if(col <= 0){
        col = 1;
    }
    //If the input is a file, not a directory
    if(isDir == 0){
        char* buffer = malloc(1000);
	    read(file, buffer, 1000);
        close(file);
        file = open(argv[2], O_WRONLY);	

	    int pos = 1;
	    int i = 0;
	    int wordLength = 0;
	    int exceedLim = 0;

	    while(buffer[i]!='\0'){
		    //If the next character is a white space
		    if(buffer[i]==' '){
                //If the white space is not going to be the first character in a line, add it
                if(pos!=1 && pos<=col){
                    dprintf(file, "%c", buffer[i]);
                    pos++;
                }
                //Iterate through all the remaining white spaces
                while(buffer[i]==' '){
                    i++;
                }
		    }
            //If the next character is a new line
            else if(buffer[i]=='\n'){
                //If there are multiple consecutive new lines, add them all
                if(buffer[i+1]=='\n'){
                    while(buffer[i]=='\n'){
                        dprintf(file, "%c", buffer[i]);
                        i++;
                    }
                    pos = 1;
                }
                //If the new line is stand alone, ignore it
                else{
                    dprintf(file, "%c", ' ');
                    i++;
                    pos++;
                }
            }
		    int ptr = i;
		    //Find the length of the word
		    while(buffer[ptr]!=' ' && buffer[ptr]!='\0' && buffer[ptr]!='\n' && buffer[ptr]!='\t'){
			    ptr++;
			    wordLength++;
		    }
		    //If the length of the word is longer than the remaining space
		    if(wordLength>(col-pos)){
                //If it isn't the start of a line or at the end of a line, start a new line
                if(pos!=1){
                    pos = 1;
                    dprintf(file, "%c", '\n');
                }
                exceedLim = 1;
		    }
            //Account for the additional +1 to ptr that moves it past the end of the word 
            ptr--;
            //Write the word into the file
		    while(i<ptr){
			    dprintf(file, "%c", buffer[i]);
			    pos++;
			    i++;
		    }
            //Reset word length
            wordLength = 0;
            //If the position after printing out the word hasn't reached the col limit, add the white space
            if(pos<=col && buffer[i]!='\n' && buffer[i]!='\t' && buffer[i]!='\0'){
                dprintf(file, "%c", buffer[i]);
                pos++;
                i++;
            }
	    }
	    free(buffer);
	    close(file);
        if(exceedLim!=0){
            exit(EXIT_FAILURE);
        }
    }
    //If the input is a directory
    else{
        printf("yo this is a directory\n");
    }
}
