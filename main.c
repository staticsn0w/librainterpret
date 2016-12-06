// librainterpret //
// copyright (C) 2016 isy //
// under the GPLv3-License (SEE LICENSE.md) //

#include <stdio.h>
#define ARRSIZE 30000 // TODO: wrap underflows and overflows

char* input;
char* array;
int counter = 0;
int loopmode = 0;
int beginloop = 0;
int isdebugfile = 0;
char* debugout = 0;

int debugprintarray() {
	printf("\nDEBUG: [");
	for (int i = 0; i < ARRSIZE; ++i) {
		if (i == ARRSIZE-1)
			printf("\"%c\" = %d", array[i], array[i]);
		else
			printf("\"%c\" = %d, ", array[i], array[i]);
	}
	printf("]\n");

	return 0;
}

int interpret(char x, int i) {
	switch (x) {
		case '>':
			++counter;
			break;
		case '<':
			--counter;
			break;
		case '+':
			++(array[counter]);
			break;
		case '-':
			--(array[counter]);
			break;
		case '.':
			printf("%c", array[counter]);
			break;
		case ',':
			array[counter] = getchar();
			break;
		case '[':
			loopmode = 1;
			beginloop = i;
			break;
		case '!':
			exit(0);
			break;
		case '#': // debugging command, prints out the tape
			debugprintarray();
		case '@': // debugging command, frees array
			memset(array, 0, ARRSIZE);
		case '/':
			#ifdef _WIN32
			system("cls");
			#else
			system("clear");
			#endif
		default:
			break;
	}
 
	return 0;
}
 
void runbrain(char* code, int size) {
	for (int i = 0; i < size; ++i) {
		interpret(code[i], i);
		if (loopmode) {
			if (code[i] == ']') {
				if (array[counter]) {
					i = beginloop;
				}
				else
					loopmode = 0;
			}
		}
	}

	puts("");
}

void runfile(char* filename) {
	// let's read the file in argument 1
	FILE* myfile = fopen(filename, "rb");

	// obtain file size
	fseek(myfile, 0, SEEK_END);
	int filesize = ftell(myfile);
	rewind(myfile);

	// load the file into "input"
	input = (char*)malloc(filesize+1);
	fread(input, 1, filesize, myfile);
	input[filesize] = '\0';
	fclose(myfile);
	//printf("Now input contains: %s\n", input);

	array = (char*)calloc(1, ARRSIZE);
	//int size = sizeof(input)-1;
	int size = filesize;

	runbrain(input, filesize);
}
 
int main(int argc, char** argv) {

end:
	return 0;
}
