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
	    int bytes = read(file, buffer, BUFFLEN);
        char* word = malloc(BUFFLEN);
        memset(word, '\0', BUFFLEN);

	    int pos = 0;
	    int i = 0;
	    int wordLength = 0;
        int newPar = 0;
        int wSpace = 0;
	    int exceedLim = 0;
        int wordOver = 1;

	    while(i<bytes){
            //If the end of the file has been reached, end the loop
            if(buffer[i]=='\0'){
                break;
            }
            //Read the word into the word array
		    while(buffer[i]!=' ' && buffer[i]!= '\n' && buffer[i]!='\t' && buffer[i]!='\0'){
                word[wordLength] = buffer[i];
                wordLength++;
                i++;
                //If the end of the word array has been reached, realloc it
                if(wordLength==(wordOver*BUFFLEN)){
                    wordOver++;
                    word = realloc(word, wordOver*BUFFLEN);
                }
                //If the end of the buffer has been reached, realloc it
                if(i==bytes){
                    memset(buffer, '\0', BUFFLEN);
                    bytes = read(file, buffer, BUFFLEN);
                    i = 0;
                }
            }
            //If there is not enough space for the word, create a new line
            if(wordLength>(col-pos)){
                printf("\n");
                pos = 0;
            }
            //Print the word
            printf("%s", word);
            pos += wordLength;
            //If the pos is now past the col width, start a new line
            if(pos==col){
                printf("\n");
                i++;
                pos = 0;
            }
            else{
                //If there is a new line, check if there are other consecutive new lines
                if(buffer[i]=='\n'){
                    while(buffer[i]=='\n'){
                        newPar++;
                        i++;
                        //If the end of the buffer has been reached, read more
                        if(i==bytes){
                            read(file, buffer, BUFFLEN);
                            i = 0;
                        }
                    }
                    //If there is more than one new line, print them all
                    if(newPar>1){
                        while(newPar>0){
                            printf("\n");
                            newPar--;
                        }
                        pos = 0;
                    }
                    //If there is only one new line, ignore it
                    else{
                        printf(" ");
                        pos++;
                        i++;
                    }
                }
                //If there is white space
                else if(pos!= 0 && buffer[i]==' '){
                    printf("%c", buffer[i]);
                    pos++;
                    //Iterate through any remaining spaces
                    while(buffer[i]==' '){
                        i++;
                        //If the end of the buffer has been reached, read more
                        if(i==bytes){
                            read(file, buffer, BUFFLEN);
                            i=0;
                        }
                    }
                }
                else{
                    printf(" ");
                    pos++;
                    i++;
                }
            }
            //Clear the word
            memset(word, '\0', wordOver*BUFFLEN);
            wordLength = 0;
            //If the end of the buffer has been reached, read new characters in
            if(i==bytes){
                bytes = read(file, buffer, BUFFLEN);
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
	else{
	    return 0;
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
            /*
              
                        Check if file name begins with period or string "wrap" 


            */
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
                file = open("Test_dir/Text2.txt", O_RDONLY);
                write_file = open("Test_dir/wrap.Text1.txt", O_WRONLY, 0600);
                //write(write_file, "HEllo WORLD!\n", 13);
                if(file < 0){       
                    perror("Opening");
                    exit(EXIT_FAILURE);
                }
                char* buffer = malloc(BUFFLEN);
                
                
                //Number of bytes written on line
                
                int bytes = 0;
                int position = 0;
                int word_length = 0;
                char* word = malloc(BUFFLEN);
                int size_of_word_available = BUFFLEN;
                memset(word, '\0', BUFFLEN);
                while((bytes = read(file, buffer, BUFFLEN)) > 0){
                    //Lines do not begin or end in whitespace              
                    int i = 0;    
 
                    int next_line_count = 0;
                    while(i < bytes){
                        char letter = buffer[i];
                        
                        
                        if(word_length > 0){
                            
                            if(letter != '\n' && letter != ' '){
                                
                                
                                // //Should mean that it is a letter
                                strncat(word, &letter, 1);
                                //printf("%c", letter);
                                word_length++;
                                
                                if((size_of_word_available - 1) == word_length){
                                    //Keeps the word big enough to fit future ones
                                    size_of_word_available++;
                                    word = realloc(word, size_of_word_available);
                                }

                            }else{
                                int paragraph_tracker = 0;
                                if(letter == '\n'){
                                    
                                    //When next line shows up check for any following next lines
                                    
                                    next_line_count++;
      
                                    while(i<bytes-1){
                                        if(buffer[i+1] == '\n'){
                                            
                                            //Then 2 next lines in a row
                                            next_line_count++;
                                            
                                            i++;
                                        }else{
                                            // printf(" Checking second n: %d ", next_line_count);
                                            //Only when it ends does it set paragraph tracker to print new paragraph. Otherwise it oges to the next one
                                            if(next_line_count >= 2){
                                                paragraph_tracker = 1;
                                                
                                            }else{
                                                next_line_count = 0;
                                            }
                                            break;
                                        }
                                    }

                                }
                                if(position!=0){
                                    
                                    if((position + word_length + 1) <= col){
                                        //Enough space for the word and its not the first one put a space and then add word
                                        printf(" ");
                                        //write(write_file, " ", 1);
                                        printf("%s", word);
                                        //write(write_file, word, word_length);
                                        position += (word_length + 1);
                             
                                        word_length = 0;
                                        memset(word, '\0', strlen(word));

                                        if(paragraph_tracker == 1){
                                            //No more next lines so print out a new paragraph after printing out the word
                                            printf("\n\n");
                                            paragraph_tracker = 0;
                                            next_line_count = 0;
                                            position = 0;
                                        }
                                        
                                    }else{
                                        //Not enough space so make new line and set position to zero
                                        printf("\n");
                                        //write(write_file, "\n", 1);
                                        position = 0;
                                    }
                                }
                                if(position == 0){
                                    
                                    //If first thing  then write whole word
                                    // write(write_file, word, word_length);
                                    printf("%s", word);
                                    position += word_length;
                                    
                                    word_length = 0;
                                    memset(word, '\0', strlen(word));

                                    if(paragraph_tracker == 1){
                                        //No more next lines so print out a new paragraph after printing out the word
                                        printf("\n\n");
                                        paragraph_tracker = 0;
                                        next_line_count = 0;
                                        position = 0;
                                    }
                                }
                                
                            }
                            
                        }
                        if(word_length==0){
                            //No current word in word buffer

                            if(letter == '\n'){
                                
                                int paragraph_tracker1 = 0;
                                next_line_count++;
                                while(i<bytes-1){
                                    //Make sure doesn't go out of buffer range since checking buffer[i+1]
                                    if(buffer[i+1] == '\n'){
                                        //Then next multiple lines in a row with a new line
                                        next_line_count++;
                                        i++;
                                    }else{
                                        //Only when it ends does it set paragraph tracker to print new paragraph. Otherwise it oges to the next one
                                        if(next_line_count >= 2){
                                            paragraph_tracker1 = 1;
                                            
                                        }else{
                                            //Only one next line disregard
                                            next_line_count = 0;
                                        }
                                        break;
                                    }
                                }
                                if(paragraph_tracker1 == 1){
                                    
                                    if(position == 0){
                                        //Only print 1 new line
                                        printf("\n");
                                    }else{
                                        printf("\n\n");
                                    }
                                    
                                    paragraph_tracker1 = 0;
                                    next_line_count = 0;
                                    position = 0;
                                }


                            }else if(letter == ' '){
                                //Do nothing only print space before a not first word
                                i++;
                                continue;
                            }else{
                                
                                //Should be a characters
                                strncat(word, &letter, 1);
                                word_length++;
                            }

                        }
                        //TWO PROBLEMS:

                        //1. After the first line the first two words don't have a space in between them
                            //LINE:            
                    
                        i++;
                    }

                    i = 0;
                    
                    
                }
                //Print out last remaining word in buffer
                if(strlen(word)){
            
                    if((position + word_length + 1) <= col){
                        
                        printf(" %s", word);
                    }else{
                        printf("\n%s", word);
                    }
                    
                }
                free(word);
                printf("\n");
                free(buffer);
                if(close(write_file) < 0){
                    perror("Closing");
                    exit(EXIT_FAILURE);
                }
                if(close(file) < 0){
                    perror("Closing");
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
