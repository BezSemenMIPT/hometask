#include "reader.h"
#include "parser.h"
#include "counter.h"
#include "writer.h"


int main(int argc, char** argv) {
	char* str = read_from_file("text.txt");
	struct arr temp = words_parse(str);
	table_t res = dictionary(temp);
	print_info(res);
	return 0;
}
