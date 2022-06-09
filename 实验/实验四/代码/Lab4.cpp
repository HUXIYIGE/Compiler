#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <string.h>
#include "parser.h"
using namespace std;

int main() {
	input_file.open("testfile.txt", ios::in);
	mid_code_file.open("mid_code.txt", ios::out);
	mips_code_file.open("mips.txt", ios::out);
	// 词法分析、语法分析、语义分析
	program();
	to_mips();
	input_file.close();
	mid_code_file.close();
	mips_code_file.close();
}
