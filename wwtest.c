#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFLEN 12

int main(int argc, char* argv[])
{
    int col;
    int file;

    DIR *dir;
    int isDir = 0;

    if(argc > 2){
        col = atoi(argv[1]);
        struct stat is_file;
        stat(argv[2], &is_file);
        //printf("IS REGISTER? %s, %d\n", argv[2], S_ISREG(is_file.st_mode));
        if(!(S_ISREG(is_file.st_mode))){
            printf("ARGUMENT IS A DIRECTORY\n");
            dir = opendir(argv[2]);
            if(dir == NULL){
                perror("DIRECTORY FAILED");
                exit(EXIT_FAILURE);
            }
            isDir = 1;
        }else{
            printf("ARGUMENT IS A FILE\n");
            file = open(argv[2], O_RDONLY);
        }
       
    }
    
	else{
        perror("NOT ENOUGH ARGUMENTS");
        exit(EXIT_FAILURE);
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
        char* word = malloc(BUFFLEN);
        memset(word, '\0', sizeof(word));

	    int pos = 1;
	    int i = 0;
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
		    //Find the length of the word, copy the characters into the word array
		    while(buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\t'){
                word[wordLength] = buffer[i];
			    i++;
			    wordLength++;
                //If the word is longer than the allocated space, realloc more
                if(wordLength>sizeof(word)){
                    word = realloc(word, 2*sizeof(word));
                }
                //If the end of the buffer has been reached, read more characters from the file
                if(buffer[i]=='\0' && i==BUFFLEN){
                    memset(buffer, '\0', BUFFLEN);
                    read(file, buffer, BUFFLEN);
                    i = 0;
                }
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
            //Print out the word
            int j = 0;
            while(word[j]!='\0'){
                printf("%c", word[j]);
                j++;
                pos++;
            }
            //Reset word length and word array
            wordLength = 0;
            memset(word, '\0', sizeof(word));
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
        free(word);
	    close(file);

        if(exceedLim!=0){
            exit(EXIT_FAILURE);
        }
    }
    //If the input is a directory
    else{
        
        //Assume that the directory only contains text files
        struct dirent *entry;

        while((entry=readdir(dir)) != NULL){
            
            //file = open(entry->d_name, O_RDWR);
            struct stat path_stat;
            char str[100];
            strcpy(str, argv[2]);
            strcat(str, "/");
            strcat(str, entry->d_name);
            int write_file = 0;

            stat(str, &path_stat);
            //printf("str: %s, is a %d\n", str, S_ISREG(path_stat.st_mode));
            if(S_ISREG(path_stat.st_mode)){
                // char add_on[] = "wrap.";
                // char filename[100];
                // strcpy(filename, argv[2]);
                // strcat(filename, "/");
                // strcat(filename, add_on);
                // strcat(filename, entry->d_name);
                // file = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0644);
                // if(file < 0){
                //     perror("Opening");
                //     exit(EXIT_FAILURE);
                // }
                file = open("Test_dir/Text1.txt", O_RDONLY);
                write_file = open("Test_dir/wrap.Text1.txt", O_WRONLY, 0600);
                //write(write_file, "HEllo WORLD!\n", 13);
                if(file < 0){       
                    perror("Opening");
                    exit(EXIT_FAILURE);
                }
                char* buffer = malloc(BUFFLEN);
                printf("READING\n");
                int i = 0;
                //Number of bytes written on line
                int position = 0;
                int bytes = 0;
                while((bytes = read(file, buffer, BUFFLEN)) > 0){
                    //Stuff in file to read;
                    // for(position = 0; position < bytes; position++){
                    //     if(buf[position] == '\n'){

                    //     }
                        
                    // }
                    //Case where word is cut off in buffer
                    
                    //Case where word is too big for line length

                    //Lines do not begin or end in whitespace
                    

                    while(i < bytes){
                        //Check if end of line is reached
                        if(position >= col);
                        //If whitespace check if next is a word otherwise go until there is a word and only print one space in between
                        write(write_file, &buffer[i], 1);
                        i++;

                        //At end check for spaces, should never end in space
                    }
                    i = 0;
                }
                
                
                free(buffer);
                if(close(write_file) < 0){
                    perror("Clsoing");
                    exit(EXIT_FAILURE);
                }
                if(close(file) < 0){
                    perror("Clsoing");
                    exit(EXIT_FAILURE);
                }
                //free(buffer);
                
            }

            //close(entry->d_name);
            
        }

        //Closes directory
        closedir(dir);
        return 0;
    }
}
