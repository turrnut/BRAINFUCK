#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
    printf("FATAL: Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) {
    printf("FATAL: Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize) {
    printf("FATAL: Could not read file \"%s\".\n", path);
    exit(74);
  }
  
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

int loop(char *text, int i, int mode){
    int sum = 0;
    int movIdx = i;
    while(sum > -1){
        movIdx -= mode;
        if(text[movIdx] == ']') sum += mode;
        else if(text[movIdx]=='[') sum -= mode;
    }
    return movIdx;
}

int brainfuck(char text[]) {
	uint8_t arr[60000];
	int pointer = 0;
	int i = 0;
	while(1) {
		switch(text[i]) {
			case '\0':
				return 0;
			case '>':
				pointer ++;
				break;
			case '<':
				pointer --;
				break;
			case '+':
				if(arr[pointer] >= 255) arr[pointer] = 0; else arr[pointer] ++;
				break;
			case '-':
				if(arr[pointer] <= 0) arr[pointer] = 0; else arr[pointer] --;
				break;
			case '.':
				putchar(arr[pointer]);
				break;
			case ',':
				arr[pointer] = getchar();
				break;
			case ']':
                		if(arr[pointer]!=0) {
					i=loop(text,i,1);
                		}
            			break;
            		case '[':
                		if(arr[pointer]==0){
                    			i=loop(text,i,-1);
                		}
 		                break;
			default:
				continue;
		}
		i++;
	}
	return 0;
}

int main(int argc, char* argv[]){
	if(argc != 2) {
		printf("Usage: bf [file]");
		return 1;
	}
	char *text = readFile(argv[1]);
	return brainfuck(text);
}
