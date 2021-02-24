#include "parser.h"


struct arr words_parse(char* str) {
	struct arr p_arr;
	char** argv;
	int len_arr = 10;
	int len_str = 80;
	argv = (char**)malloc(len_arr * sizeof(char*));
	for (int i = 0; i < len_arr; i++) {
		argv[i]= (char*)malloc(len_str * sizeof(char));
	}
	int counter = 0;
	int m=0;
	int k=0;
	while (str[m] != '\0') {
		if (counter == len_arr) {
			len_arr += len_arr;
			argv = (char**)realloc(argv, len_arr * sizeof(char*));
			for (int i = counter; i < len_arr; i++) {
				argv[i] = (char*)malloc(len_str * sizeof(char));
			}
		}
		while((str[m] != ' ')&&(str[m]!='\0')){
			argv[counter][k]=str[m];
			k++;
			//printf("++%d %c\n",k,str[m]);
			m++;			
		}
		//printf("+++++%d\n", k);
		if(k>0){
			argv[counter][k]='\0';
			//printf("****%s\n",argv[counter]);
			counter++;
			k=0;		
		}
		if(str[m]=='\0') break;
		while(str[m]==' ') m++;
	}
	//printf("++%d\n", (int)strlen(argv[0]));
	free(str);
	p_arr.argv = argv;
	p_arr.argc = counter;
	//printf("****************%d\n", counter);
	//for(int i=0;i<counter;i++) printf("%s\n", argv[i]);
	return p_arr;
}
