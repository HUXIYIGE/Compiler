#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <assert.h>
#define MAIN "main"
#define PROGRAM "Program"
using namespace std;

#define SIZE 256

ifstream input_file;
char tokenBuffer[256];
char CHAR;
int symbol;

int L_Begin;				// 上一个token起始位置
int L_Symbol;				// 上一个token的类型
char L_tokenBuffer[SIZE];		// 上一个token的字符串

int LL_Begin;			// 上上个token起始位置
int LL_Symbol;			// 上上个token的类型
char LL_tokenBuffer[SIZE];	// 上上个token的字符串

char buffer[SIZE];
int cnt, cnt_len, cnt_line, L_CountLine;
bool isBegin = 1;
//ofstream errorFile;

void error(char errorClass) {
	int tmpCountLine;

	// 根据错误类型判断错误所在行数,这种在一行末尾出错的情况得输出上一行的行数
	if (errorClass == 'k' || errorClass == 'l' || errorClass == 'm')
		tmpCountLine = L_CountLine;
	else
		tmpCountLine = cnt_line;
	//errorFile << tmpCountLine << " " << errorClass << endl;		// 文件输出
	//cout << tmpCountLine << " " << errorClass << endl;
	return;
}
enum classnum {
	IDENFR, INTCON, CHARCON, STRCON, CONSTTK, INTTK, CHARTK, VOIDTK, MAINTK, IFTK, ELSETK, SWITCHTK, CASETK, DEFAULTTK, WHILETK, FORTK, SCANFTK, PRINTFTK,
	RETURNTK, PLUS, MINU, MULT, DIV, LSS, LEQ, GRE, GEQ, EQL, NEQ, COLON, ASSIGN, SEMICN, COMMA, LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE
};

bool isDigit(char c) {
	if ('0' <= c && c <= '9')
		return 1;
	else
		return 0;
}

bool isLetter(char c) {
	if ((c == '_') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return 1;
	else
		return 0;
}

bool isChar(char c) {
	if (isDigit(c) || isLetter(c) || c == '+' || c == '-' || c == '*' || c == '/' )
		return 1;
	else
		return 0;
}

bool isString(char c) {
	if (c == 32 || c == 33 || (35 <= c && c <= 126))
		return 1;
	else
		return 0;
}

void getLowerString(char s[]) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (isLetter(s[i])) {
			s[i] = tolower(s[i]);
		}
	}
}

void getch() {
	CHAR = buffer[cnt];
	cnt++;
}

void backch() {
	cnt--;
}

void getTK(char s[]) {
	if (strcmp(s, "const") == 0) symbol = CONSTTK;
	else if (strcmp(s, "case") == 0) symbol = CASETK;
	else if (strcmp(s, "default") == 0) symbol = DEFAULTTK;
	else if (strcmp(s, "return") == 0) symbol = RETURNTK;
	else if (strcmp(s, "int") == 0) symbol = INTTK;
	else if (strcmp(s, "char") == 0) symbol = CHARTK;
	else if (strcmp(s, "void") == 0) symbol = VOIDTK;
	else if (strcmp(s, "while") == 0) symbol = WHILETK;
	else if (strcmp(s, "for") == 0) symbol = FORTK;
	else if (strcmp(s, "scanf") == 0) symbol = SCANFTK;
	else if (strcmp(s, "printf") == 0) symbol = PRINTFTK;
	else if (strcmp(s, "main") == 0) symbol = MAINTK;
	else if (strcmp(s, "if") == 0) symbol = IFTK;
	else if (strcmp(s, "else") == 0) symbol = ELSETK;
	else if (strcmp(s, "switch") == 0) symbol = SWITCHTK;
	else symbol = IDENFR;
}


int getnbc() {
	while ((buffer[cnt] == ' ' || buffer[cnt] == '\t' || buffer[cnt] == '\n' || buffer[cnt] == '\r') && cnt < cnt_len) {
		cnt++;
	}
	if (cnt >= cnt_len) {
		return 0;
	}
	else {
		LL_Begin = L_Begin;
		L_Begin = cnt;
		CHAR = buffer[cnt];
		cnt++;
		return 1;
	}
}

void copy(char s[], char c) {
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
	return;
}

void get_token(int flag = 1) {
	if (isBegin == 1) {
		isBegin = 0;
	}
	else {
		//outputsym();
		LL_Symbol = L_Symbol;
		strcpy(LL_tokenBuffer, L_tokenBuffer);
		L_Symbol = symbol;
		strcpy(L_tokenBuffer, tokenBuffer);
		L_CountLine = cnt_line;
	}

	symbol = -1;
	tokenBuffer[0] = '\0';
	// 获取一个非空字符，如果获取失败则直接返回
	while (getnbc() == 0) {
		if (!input_file.eof()) {
			cnt = 0;
			cnt_line++;
			input_file.getline(buffer, 256);
			cnt_len = strlen(buffer);
		}
		else {
			symbol = -2;
			return;
		}
	}

	if (isLetter(CHAR)) {
		while (isDigit(CHAR) || isLetter(CHAR)) {
			copy(tokenBuffer, CHAR);
			getch();
		}
		backch();

		char tmptoken[1000];
		strcpy(tmptoken, tokenBuffer);
		getLowerString(tmptoken);
		getTK(tmptoken);
	}
	else if (isDigit(CHAR)) {
		while (isDigit(CHAR)) {
			copy(tokenBuffer, CHAR);
			getch();
		}
		backch();
		symbol = 1;
	}
	else if (CHAR == '\'') {
		// 字符
		getch();

		/*
		*	文法错误，类别码为 a
		*	字符中出现了非法符号，处理方式为 忽略
		*/
		if (isChar(CHAR) == 0 && flag) {
			error('a');
		}

		copy(tokenBuffer, CHAR);
		getch();
		if (CHAR != '\'' && flag) {
			error('a');
			backch();
		}
		else
			symbol = 2;
	}
	else if (CHAR == '\"') {
		// 字符串
		getch();
		while (CHAR != '\"') {
			/*
			*	文法错误，错误类别码为 a
			*	字符串中出现了非法符号，处理方式为 忽略
			*/
			if (isString(CHAR) == 0 && flag) {
				error('a');
			}

			copy(tokenBuffer, CHAR);
			getch();
		}

		//字符串长度为0
		if (tokenBuffer[0] == '\0' && flag) error('a');
		symbol = 3;
	}
	else if (CHAR == '+') symbol = PLUS;
	else if (CHAR == '-') symbol = MINU;
	else if (CHAR == '*') symbol = MULT;
	else if (CHAR == '/') symbol = DIV;
	else if (CHAR == '<') {
		getch();
		if (CHAR == '=')
			symbol = LEQ;
		else {
			symbol = LSS;
			backch();
		}
	}
	else if (CHAR == '>') {
		getch();
		if (CHAR == '=')
			symbol = GEQ;
		else {
			symbol = GRE;
			backch();
		}
	}
	else if (CHAR == '=') {
		getch();
		if (CHAR == '=')
			symbol = EQL;
		else {
			symbol = ASSIGN;
			backch();
		}
	}
	else if (CHAR == '!') {
		getch();
		if (CHAR == '=')
			symbol = NEQ;
		else {
			// e0
			backch();
		}
	}
	else if (CHAR == ':') symbol = COLON;
	else if (CHAR == ';') symbol = SEMICN;
	else if (CHAR == ',') symbol = COMMA;
	else if (CHAR == '(') symbol = LPARENT;
	else if (CHAR == ')') symbol = RPARENT;
	else if (CHAR == '[') symbol = LBRACK;
	else if (CHAR == ']') symbol = RBRACK;
	else if (CHAR == '{') symbol = LBRACE;
	else if (CHAR == '}') symbol = RBRACE;
}
void backToken() {
	cnt = L_Begin;
	symbol = L_Symbol;
	strcpy(tokenBuffer, L_tokenBuffer);

	L_Begin = LL_Begin;
	L_Symbol = LL_Symbol;
	strcpy(L_tokenBuffer, LL_tokenBuffer);
}

// 符号表
struct sym {
	// 以下为通用参数
	string name;
	int kind;	// 符号的种类，0为程序常量，1为程序变量，2为函数名，3为函数参数表
	int type;	// 符号的类型，0为int，1为char
	int dimension;	// 若为数组类型，记录其维度；若为函数类型，记录其参数数量
	int addr;   // 符号地址
	// 以下为特殊参数
	int value;	// 记录数值型符号的值
	string str;	// 记录字符或字符串型符号的值
	int index;		// 若为数组类型，记录其行数
	int columns;	// 若为数组类型，记录其列数
};

map<string, map<string,sym>> symbol_table;
struct sym now_sym;					// 记录当前正在使用的符号
string nowTable;						// 记录当前所在的符号表层次名称
map<string,sym> curMap;		// 记录当前所在的符号表层次的map

// 将当前的curSym初始化
void init_now_sym() {
	now_sym.name = "";
	now_sym.kind = -1;
	now_sym.type = -1;
	now_sym.dimension = 0;
	now_sym.addr = -1;

	now_sym.value = 0;
	now_sym.str = "";
	now_sym.index = -1;
	now_sym.columns = -1;
}

// 该函数将当前的层次插入符号表
void insert_current_level() {
	curMap.clear();
	symbol_table[nowTable] = curMap;
}

int global_addr = 0;
int tmp_addr = 0;
int tmp_var_cnt = 0;
int label_cnt = 0;

// 该函数将当前的符号插入当前的层次
void insert_current_symbol() {
	if (symbol_table[nowTable].find(now_sym.name) != symbol_table[nowTable].end()) {
		error('b');
	}
	else {
		symbol_table[nowTable][now_sym.name] = now_sym;
		symbol_table[nowTable][now_sym.name].addr = (nowTable == PROGRAM) ? global_addr++ : tmp_addr++;
	}
}

void insert_tmp_value(string valueName, int kind, int type) {
	struct sym tmpValue;
	tmpValue.name = valueName;
	tmpValue.kind = kind;
	tmpValue.type = type;
	if (symbol_table[nowTable].find(tmpValue.name) == symbol_table[nowTable].end()) {
		symbol_table[nowTable][tmpValue.name] = tmpValue;
	}
	symbol_table[nowTable][valueName].addr = nowTable == PROGRAM ? global_addr++ : tmp_addr++;
}

string get_tmp_value() {
	tmp_var_cnt++;
	return "T" + to_string(tmp_var_cnt);
}

string get_label() {
	label_cnt++;
	return "Label" + to_string(label_cnt);
}