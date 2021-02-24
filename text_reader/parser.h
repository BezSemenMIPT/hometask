#pragma once
#include "info.h"

struct arr {
	int argc;
	char** argv;
};

struct arr words_parse(char* str);
