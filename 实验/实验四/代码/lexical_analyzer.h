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

int L_Begin;				// ��һ��token��ʼλ��
int L_Symbol;				// ��һ��token������
char L_tokenBuffer[SIZE];		// ��һ��token���ַ���

int LL_Begin;			// ���ϸ�token��ʼλ��
int LL_Symbol;			// ���ϸ�token������
char LL_tokenBuffer[SIZE];	// ���ϸ�token���ַ���

char buffer[SIZE];
int cnt, cnt_len, cnt_line, L_CountLine;
bool isBegin = 1;
//ofstream errorFile;

void error(char errorClass) {
	int tmpCountLine;

	// ���ݴ��������жϴ�����������,������һ��ĩβ���������������һ�е�����
	if (errorClass == 'k' || errorClass == 'l' || errorClass == 'm')
		tmpCountLine = L_CountLine;
	else
		tmpCountLine = cnt_line;
	//errorFile << tmpCountLine << " " << errorClass << endl;		// �ļ����
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
	// ��ȡһ���ǿ��ַ��������ȡʧ����ֱ�ӷ���
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
		// �ַ�
		getch();

		/*
		*	�ķ����������Ϊ a
		*	�ַ��г����˷Ƿ����ţ�����ʽΪ ����
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
		// �ַ���
		getch();
		while (CHAR != '\"') {
			/*
			*	�ķ����󣬴��������Ϊ a
			*	�ַ����г����˷Ƿ����ţ�����ʽΪ ����
			*/
			if (isString(CHAR) == 0 && flag) {
				error('a');
			}

			copy(tokenBuffer, CHAR);
			getch();
		}

		//�ַ�������Ϊ0
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

// ���ű�
struct sym {
	// ����Ϊͨ�ò���
	string name;
	int kind;	// ���ŵ����࣬0Ϊ��������1Ϊ���������2Ϊ��������3Ϊ����������
	int type;	// ���ŵ����ͣ�0Ϊint��1Ϊchar
	int dimension;	// ��Ϊ�������ͣ���¼��ά�ȣ���Ϊ�������ͣ���¼���������
	int addr;   // ���ŵ�ַ
	// ����Ϊ�������
	int value;	// ��¼��ֵ�ͷ��ŵ�ֵ
	string str;	// ��¼�ַ����ַ����ͷ��ŵ�ֵ
	int index;		// ��Ϊ�������ͣ���¼������
	int columns;	// ��Ϊ�������ͣ���¼������
};

map<string, map<string,sym>> symbol_table;
struct sym now_sym;					// ��¼��ǰ����ʹ�õķ���
string nowTable;						// ��¼��ǰ���ڵķ��ű�������
map<string,sym> curMap;		// ��¼��ǰ���ڵķ��ű��ε�map

// ����ǰ��curSym��ʼ��
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

// �ú�������ǰ�Ĳ�β�����ű�
void insert_current_level() {
	curMap.clear();
	symbol_table[nowTable] = curMap;
}

int global_addr = 0;
int tmp_addr = 0;
int tmp_var_cnt = 0;
int label_cnt = 0;

// �ú�������ǰ�ķ��Ų��뵱ǰ�Ĳ��
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