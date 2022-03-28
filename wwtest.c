#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFLEN 500

int main(int argc, char* argv[])
{
    int col;
    int file;

    DIR *dir;
    int isDir = 0;

    if(argc > 2){
        col = atoi(argv[1]);
        file = fopen(argv[2], "r");
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
        //Read the file into the buffer
        char* buffer = malloc(BUFFLEN);
	    read(file, buffer, BUFFLEN);

	    int pos = 1;
	    int i = 0;
        int ptr;
	    int wordLength = 0;
	    int exceedLim = 0;

	    while(i<BUFFLEN && buffer[i]!='\0'){
		    //If the next character is a white space
		    if(buffer[i]==' '){
                //If the white space is not going to be the first character in a line, add it
                if(pos!=1 && pos<col){
                    printf("%c", buffer[i]);
                    pos++;
                }
                //Iterate through all the remaining white spaces
                while(buffer[i]==' '){
                    i++;
                }
		    }
            //If the next character is a new line
            if(buffer[i]=='\n'){
                //If there are multiple consecutive new lines, add them all
                if(buffer[i+1]=='\n'){
                    while(buffer[i]=='\n'){
                        printf("%c", buffer[i]);
                        i++;
                    }
                    pos = 1;
                }
                //If the new line is stand alone, ignore it
                else{
                    printf(" ");
                    i++;
                    pos++;
                }
            }
		    ptr = i;
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
                    printf("\n");
                }
                exceedLim = 1;
		    }
            //Write the word into the file
		    while(i<ptr){
			    printf("%c", buffer[i]);
			    pos++;
			    i++;
		    }
            //Reset word length
            wordLength = 0;
            //If the position after printing out the word hasn't reached the col limit, add the white space
            if(pos<=col && buffer[i]!='\n' && buffer[i]!='\t' && buffer[i]!='\0'){
                printf("%c", buffer[i]);
                pos++;
                i++;
            }
            //If the end of the buffer is reached, read more from the file
            if(i==BUFFLEN && buffer[i]=='\0'){
                memset(buffer, '\0', BUFFLEN);
                read(file, buffer, BUFFLEN);
                i = 0;
            }
	    }
        printf("\n");
	    free(buffer);
	    close(file);

        if(exceedLim!=0){
            exit(EXIT_FAILURE);
        }
    }
    //If the input is a directory
    else{
        printf("yo this is a directory\n");
        //Assume that the directory only contains text files
        int files = 0;
        struct dirent *entry;
        //char add_on[] = "wrap.";
        
        

        while((entry=readdir(dir)) != NULL){
            files++;
            //file = open(entry->d_name, O_RDWR);
            struct stat path_stat;
            char str[100];
            strcpy(str, argv[2]);
            strcat(str, "/");
            strcat(str, entry->d_name);

            stat(str, &path_stat);

            if(S_ISREG(path_stat.st_mode)){
                char add_on[] = "wrap.";
                char filename[100];
                printf("FILENAME SHOULD BE BLANK: %s\n", filename);
                strcpy(filename, argv[2]);
                strcat(filename, "/");
                strcat(filename, add_on);
                strcat(filename, entry->d_name);
                printf("FILENAME: %s\n", filename);
                file = open(filename, O_WRONLY, 0644);
                if(file < 0){
                    perror("Opening");
                    exit(EXIT_FAILURE);
                }
                char* buffer = '\0';
                while((read(file, buffer, 1)) > 0){
                    //Stuff in file to read;
                    printf("%s", buffer);
                }
                
                

                if(close(file) < 0){
                    perror("Clsoing");
                    exit(EXIT_FAILURE);
                }
                free(buffer);
                filename = "";
            }

            //close(entry->d_name);
            printf("File %d: %s, ISFILE: %d\n", files, entry->d_name, S_ISREG(path_stat.st_mode));
        }

        //Closes directory
        closedir(dir);
        return 0;
    }
}
