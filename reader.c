#include "reader.h"
#include "string.h"

char* read_from_file(char* name) {
	FILE* f = fopen(name, "r");
	assert(f);
	int len = 10;
	char ch;
	int counter = 0;
	char* str_arr;
	assert(str_arr = (char*)malloc(len * sizeof(char)));
	while (1) {
		ch=fgetc(f);
		if(ch=='\n') break;
		//printf("%c\n",ch);
		str_arr[counter] = ch;
		counter++;
		if (counter == len) {
			len += len;
			str_arr = (char*)realloc(str_arr, len * sizeof(char));
		}
	}
	//printf("%d\n",counter);
	str_arr[counter]='\0';
	fclose(f);
	//printf("-------%s\n",str_arr);
	return str_arr;
}

char* read_from_argv(int argc, char* argv[]) {
	int len = 80;
	char* str_arr = (char*)malloc(len * sizeof(char));
	for (int i = 0; i < argc; i++) {
		strcat(str_arr, argv[i]);
		str_arr[strlen(argv[i])] = ' ';
		str_arr[strlen(argv[i])+1] = '\0';
		len *= 2;
		str_arr = (char*)realloc(str_arr, len * sizeof(char));
	}
	return str_arr;
}
