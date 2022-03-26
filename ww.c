#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int col;
    int file;
    if(argc > 2){
        col = atoi(argv[1]);
        file = open(argv[2], O_RDWR);
    }
	else{
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    if(file == -1){
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
	char* buffer = malloc(1000);
	read(file, buffer, 1000);
    close(file);
    file = open(argv[2], O_WRONLY);	
    //printf("%s\n", buffer);

	int pos = 0;
	int i = 0;
	int wordLength = 0;
	int exceedLim = 0;

	while(buffer[i]!='\0'){
		//If the next character is a white space
		if(buffer[i]==' '){
            //If the white space is not going to be the first character in a line, add it
            if(pos!=0){
                dprintf(file, "%c", buffer[i]);
                pos++;
            }
            //Iterate through all the remaining white spaces
            while(buffer[i]==' '){
                i++;
            }
		}
		int ptr = i;
		//Find the length of the word
		while(buffer[ptr]!=' '&&buffer[ptr]!='\0'){
			ptr++;
			wordLength++;
		}
		//If the length of the word is longer than the remaining space in the line it isn't the start of a new line, start a new line
		if(wordLength>(col-pos)&&pos!=0){
			dprintf(file, "%c", '\n');
			pos = 0;
            exceedLim = 1;
		}
		while(i<ptr){
			dprintf(file, "%c", buffer[i]);
			pos++;
			i++;
		}
        if(pos<col){
            dprintf(file, "%c", buffer[i]);
            i++;
        }
	}
	free(buffer);
	close(file);
    if(exceedLim!=0){
        exit(EXIT_FAILURE);
    }
}
