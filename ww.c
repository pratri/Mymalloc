#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int col = atoi(argv[1]);
	int file = open(argv[2], O_RDWR);
	char* buffer = malloc(500);
	read(file, buffer, 500);
	//printf("%s\n", buffer);

	int pos = 0;
	int i = 0;
	int wordLength = 0;
	
	while(buffer[i]!='\0'){
		//If the first character in a line is a white space, skip it until a non white space character is reached
		if(pos==0 && buffer[i]==' '){
			i++;
		}
		int ptr = i;
		//Find the length of the word
		while(buffer[ptr]!=' '&&buffer[ptr]!='\0'){
			ptr++;
			wordLength++;
		}
		//If the length of the word is longer than the remaining space in the line, start a new line
		if(wordLength>(col-pos)){
			dprintf(file, "%c", '\n');
			pos = 0;
		}
		while(i<ptr){
			dprintf(file, "%c", buffer[i]);
			pos++;
			i++;
		}
	}
	free(buffer);
	close(file);
}
