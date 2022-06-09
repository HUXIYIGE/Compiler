#pragma once
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "lexical_analyzer.h"
#include "code_gener.h"
using namespace std;

// 语法分析相关变量
int dimension = 0;	  // 变量定义的数组维数
int indexCount = 0;	  // 无初始化变量的数组的行数
int columnsCount = 0; // 有初始化变量的数组的列数

// 保存上一个标识符，保存到函数列表中
int last_type_identifier;				// 记录上一个类型标识符，0代表整数，1代表字符
string L_Identifier;					// 记录上一个标识符
set<string> functionWithReturnValue;	// 记录有返回值函数
set<string> functionWithoutReturnValue; // 记录无返回值函数
map<string, int> functionReturnType;	// 记录函数返回值类型，0为无返回值，1为整型，2为字符

// 错误处理相关变量
int last_operator;			// 保存上一个整数的符号，-1表示为负数
int last_integer;			// 保存上一个整数
int last_unsigned_interger; // 保存上一个无符号整数
string last_char;			// 保存上一个字符
int last_const_type;		// 记录上一个常数的类型，0代表整数，1代表字符
int last_expression_type;	// 记录上一个表达式的类型，1代表整数，2代表字符
int last_constant_type;		// 记录上一个常量的类型，0代表整数，1代表字符
int last_variable_type;		// 记录上一个变量定义的类型，0代表整数，1代表字符

int func_return_type; // 记录当前函数是否有返回值，0为无返回值，1为整型，2为字符
int has_returned;	  // 记录当前函数是否已经返回，0为无返回值，1为整型，2为字符
int returned_type;	  // 记录已经返回值的类型，0为无返回值，1为整型，2为字符，3为return;

string last_func_call;					   // 记录上一个函数调用
int parameter_count;					   // 记录函数参数表的数量
int value_parameter_count;				   // 记录函数值参数表的数量
map<string, int> func_parameter_count;	   // 记录有返回值函数的参数数量
map<string, int[100]> func_parameter_type; // 记录有返回值函数的参数类型

void getADD();				// <�ӷ������>
void getMULT();				// <�˷������>
void relational_operator(); // <��ϵ�����>
void Char();				// <�ַ�>
void Char(string &c);
void String(); //*<�ַ���>

void program();			 //*<����>
void constant_dec();	 //*<����˵��>
void constant_def();	 //*<��������>
void unsigned_integer(); //*<�޷�������>
void integer();			 //*<����>
void integer(int &integer);

void identifier();				  // <��ʶ��>
void declaration_header();		  //*<����ͷ��>
void constant();				  //*<����>
void variable_dec();			  //*<����˵��>
void variable_def(int flag = 1);  //*<��������>
void variable_def_without_init(); //*<���������޳�ʼ��>
void variable_def_with_init();	  //*<�������弰��ʼ��>
void type_of_indentifier();		  // <���ͱ�ʶ��>
void compound_statement();		  //*<�������>
void parameter_table();			  //*<������>
void expression();				  // ����ʽ
void expression(int &type, string &ansTmp);
void item(); // ��
void item(int &type, string &ansTmp);
void factor(); // ����
void factor(int &type, string &ansTmp);

void statement();
void assign_statement();
void condition_statement();
void condition();
void loop_statement();
void step();
void switch_statement();
void fact_sheet();
void case_statement();
void deft();
void func_call();
void void_func_call();
void value_parameter_table();
void statement_column();
void read_statement();
void write_statement();
void return_statement();
void program_variable_dec();
void Main();

void getADD()
{
	// symbol == PLUS || symbol == MINU
	assert(symbol == PLUS || symbol == MINU);

	get_token();
}

void getMULT()
{
	// symbol == MULT || symbol == DIV
	assert(symbol == MULT || symbol == DIV);

	get_token();
}

void relational_operator()
{
	// symbol == LSS || symbol == LEQ || symbol == GRE || symbol == GEQ || symbol == EQL || symbol == NEQ
	get_token();
}

void Char()
{
	// symbol == CHARCON
	assert(symbol == CHARCON);

	last_char = tokenBuffer;
	get_token();
}

void Char(string &c)
{
	assert(symbol == CHARCON);
	last_char = tokenBuffer;
	c = tokenBuffer;
	get_token();
}

void String()
{
	// symbol == STRCON
	assert(symbol == STRCON);
	get_token();
}
void unsigned_integer()
{
	// symbol == INTCON
	assert(symbol == INTCON);

	last_unsigned_interger = atoi(tokenBuffer);			   // 记录上一个识别的无符号整数
	last_integer = last_operator * last_unsigned_interger; // 记录上一个识别的整数
	now_sym.value = last_integer;
	get_token();
	// ofile << "<无符号整数>" << endl;
}

void integer()
{
	// 识别符号部分
	last_operator = 1;
	if (symbol == PLUS)
	{
		last_operator = 1;
		get_token();
	}
	else if (symbol == MINU)
	{
		last_operator = -1;
		get_token();
	}

	unsigned_integer();
}

void integer(int &integer)
{
	last_operator = 1;
	last_operator = (symbol == MINU) ? -1 : 1;
	if (symbol == PLUS || symbol == MINU)
		get_token();
	unsigned_integer();
	integer = last_integer;
}

void identifier()
{
	// symbol == IDENFR
	L_Identifier = tokenBuffer;
	get_token();
}

void constant()
{
	// 整数或者字符
	if (symbol == INTCON || symbol == PLUS || symbol == MINU)
	{
		last_const_type = 0;
		integer();
	}
	else if (symbol == CHARCON)
	{
		last_const_type = 1;
		Char();
	}

	// 常量
}

void constant(int &tmpConstType, int &tInteger, string &tChar)
{
	// 整数或者字符
	if (symbol == INTCON || symbol == PLUS || symbol == MINU)
	{
		tmpConstType = 0;
		last_const_type = 0;
		int tmpInteger;
		integer(tmpInteger);
		tInteger = tmpInteger;
	}
	else if (symbol == CHARCON)
	{
		tmpConstType = 1;
		last_const_type = 1;
		string tmpChar;
		Char(tmpChar);
		tChar = tmpChar;
	}
	else
	{
		error('0');
	}
}

void type_of_indentifier()
{
	// symbol == INTTK || symbol == CHARTK
	assert(symbol == INTTK || symbol == CHARTK);
	last_type_identifier = symbol;
	get_token();
}

void constant_def()
{
	if (symbol == INTTK)
	{

		// 准备添加当前常量到符号表
		init_now_sym();
		now_sym.kind = 0;
		now_sym.type = 1; // 符号表相关，一维int

		do
		{
			get_token();				// symbol == INDENFR
			now_sym.name = tokenBuffer; // 更新当前符号的名字，即标识符的名字

			get_token(); // symbol == '='

			get_token(); // 整数
			integer();

			now_sym.value = last_integer; // 更新当前符号的整数值
			insert_current_symbol();
			insert_mid_code(now_sym.name, "int", CONST, to_string(last_integer));
		} while (symbol == COMMA);
	}
	else if (symbol == CHARTK)
	{

		// 准备添加当前常量到符号表
		init_now_sym();
		now_sym.kind = 0;
		now_sym.type = 4; // 符号表相关，一维char

		do
		{
			get_token();				// symbol == INDEFR
			now_sym.name = tokenBuffer; // 更新当前符号的名字，即标识符的名字

			get_token(); // symbol == '='

			get_token();			   // symbol == CHARCON
			now_sym.str = tokenBuffer; // 更新当前符号的字符值
			insert_current_symbol();

			insert_mid_code(now_sym.name, "char", CONST, now_sym.str); //插入常量字符

			get_token(); // , or else
		} while (symbol == COMMA);
	}
}
void constant_dec()
{
	while (symbol == CONSTTK)
	{
		get_token();
		constant_def(); // 在该子程序中添加常量到符号表
		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
}
void variable_def_with_init()
{
	// 初始化临时变量
	indexCount = 0;
	columnsCount = 0;
	string nowVar;
	insert_mid_code(now_sym.name, "", VARINIT, "");
	get_token();

	if (dimension == 0)
	{
		int tmpConstantType;
		int tmpInteger;
		string tmpChar;
		constant(tmpConstantType, tmpInteger, tmpChar);
		if (last_const_type != last_constant_type)
		{
			error('o');
		}
		if (last_const_type == 0)
		{
			now_sym.value = tmpInteger;
		}
		else if (last_const_type == 1)
		{
			now_sym.str = tmpChar;
		}
	}
	else if (dimension == 1)
	{
		// symbol == {
		get_token();
		constant();
		if (last_const_type != last_constant_type)
		{
			error('o');
		}
		indexCount++;

		while (symbol == COMMA)
		{
			get_token();
			constant();
			if (last_const_type != last_constant_type)
			{
				error('o');
			}
			indexCount++;
		}

		// symbol == }
		assert(symbol == RBRACE);

		if (indexCount != now_sym.index)
		{
			error('n');
		}

		get_token();
	}
	else if (dimension == 2)
	{
		// symbol == {
		get_token(); // symbol == {
		get_token();
		constant();
		if (last_const_type != last_constant_type)
		{
			error('o');
		}
		columnsCount++;
		while (symbol == COMMA)
		{
			get_token();
			constant();
			if (last_const_type != last_constant_type)
			{
				error('o');
			}
			columnsCount++;
		}

		// symbol == }
		indexCount++;

		// 判断数组的列数是否相同
		if (columnsCount != now_sym.columns)
		{
			error('n');
		}

		get_token();

		while (symbol == COMMA)
		{
			columnsCount = 0; // 初始化列变量
			get_token();
			// symbol == {
			get_token();
			constant();
			if (last_const_type != last_constant_type)
			{
				error('o');
			}
			columnsCount++;
			while (symbol == COMMA)
			{
				get_token();
				constant();
				if (last_const_type != last_constant_type)
				{
					error('o');
				}
				columnsCount++;
			}

			// symbol == }
			indexCount++; // 行变量叠加

			// 判断数组的列数是否相同
			if (columnsCount != now_sym.columns)
			{
				error('n');
			}

			get_token();
		}

		if (symbol != RBRACE)
		{
			error('0');
		}

		// 判断数组的行数是否相同
		if (indexCount != now_sym.index)
		{
			error('n');
		}

		get_token();
	}
	// 变量定义及初始化
}

void variable_def_without_init()
{
	while (symbol == COMMA)
	{
		dimension = 0; // 初始化维度

		get_token();
		identifier();

		// 初始化当前符号
		init_now_sym();
		now_sym.kind = 2; // 更新当前符号类型，无初始化的变量定义
		now_sym.type = last_variable_type;
		now_sym.name = L_Identifier;

		while (symbol == LBRACK)
		{
			get_token();
			unsigned_integer();

			if (dimension == 0)
			{
				now_sym.index = last_unsigned_interger;
			}
			else
				now_sym.columns = last_unsigned_interger; // 记录当前变量定义的行数

			if (symbol != RBRACK)
			{
				error('m');
			}
			else
			{
				get_token();
			}
			dimension++;
		}

		// 更新当前符号保存的数组维度
		now_sym.type = now_sym.type + dimension;
		insert_current_symbol();
	}
}

void declaration_header()
{ // 声明头部
	if (symbol != INTTK && symbol != CHARTK)
	{
		error('0');
	}
	identifier();
}

void program_variable_dec()
{
	variable_def(0);
	if (symbol != SEMICN)
	{
		error('k');
	}
	else
	{
		get_token();
	}
}

void parameter_table()
{
	parameter_count = 0; // 初始化函数参数计数器
	if (symbol == INTTK || symbol == CHARTK)
	{
		type_of_indentifier();
		identifier();

		// 将参数添加到函数专属符号表中，仅包含参数数量和类型

		if (last_type_identifier == INTTK)
		{
			func_parameter_type[nowTable][parameter_count] = 1;
		}
		else if (last_type_identifier == CHARTK)
		{
			func_parameter_type[nowTable][parameter_count] = 2;
		}
		parameter_count++;

		// 将参数添加到符号表中，仅有kind和type，没有value
		init_now_sym();
		now_sym.kind = 5;
		if (last_type_identifier == INTTK)
		{
			now_sym.type = 1;
		}
		else
		{
			now_sym.type = 4;
		}
		now_sym.name = L_Identifier;
		insert_current_symbol();

		while (symbol == COMMA)
		{
			get_token();
			type_of_indentifier();
			identifier();

			// 将参数添加到函数专属符号表中，仅包含参数数量和类型
			if (last_type_identifier == INTTK)
			{
				func_parameter_type[nowTable][parameter_count] = 1;
			}
			else if (last_type_identifier == CHARTK)
			{
				func_parameter_type[nowTable][parameter_count] = 2;
			}
			parameter_count++;

			// 将参数添加到符号表中，仅有kind和type，没有value
			init_now_sym();
			now_sym.kind = 5;
			if (last_type_identifier == INTTK)
			{
				now_sym.type = 1;
			}
			else
			{
				now_sym.type = 4;
			}
			now_sym.name = L_Identifier;
			insert_current_symbol();
		}
	}

	func_parameter_count[nowTable] = parameter_count;

	// 参数表
}

void variable_def(int flag)
{
	dimension = 0; // 初始化数组维数
	// 变量定义的共同部分
	if (flag)
		type_of_indentifier();
	identifier();

	// 初始化当前符号
	init_now_sym();
	if (last_type_identifier == INTTK || LL_Symbol == INTTK)
	{
		now_sym.type = 1;
		last_constant_type = 0;
		last_variable_type = 1;
	}
	else if (last_type_identifier == CHARTK || LL_Symbol == CHARTK)
	{
		now_sym.type = 4;
		last_constant_type = 1;
		last_variable_type = 4;
	}
	now_sym.name = L_Identifier;

	//判断数组维度
	while (symbol == LBRACK)
	{
		get_token();
		unsigned_integer();

		if (dimension == 0)
			now_sym.index = last_unsigned_interger;
		else
			now_sym.columns = last_unsigned_interger;
		if (symbol != RBRACK)
		{
			error('m');
		}
		else
		{
			get_token();
		}
		dimension++;
	}

	// 更新当前符号保存的数组维度
	now_sym.type = now_sym.type + dimension;

	// 判断是否进行初始化
	if (symbol == ASSIGN)
	{
		now_sym.kind = 1; // 更新当前符号类型，有初始化的变量定义
		variable_def_with_init();
		insert_current_symbol(); // 变量定义及初始化每行仅有一个
	}
	else
	{
		now_sym.kind = 2;		 // 更新当前符号类型，无初始化的变量定义
		insert_current_symbol(); // 由于变量定义无初始化每行能有多个，所以先将当前的加入符号表
		variable_def_without_init();
	}
}

void variable_dec()
{
	while (symbol == INTTK || symbol == CHARTK)
	{
		variable_def();
		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
	// 变量说明
}

void step()
{
	unsigned_integer();
	// 步长
}

void expression()
{
	last_expression_type = 2;
	if (symbol == PLUS || symbol == MINU)
	{

		getADD();
		last_expression_type = 1;
	}

	item();
	while (symbol == PLUS || symbol == MINU)
	{
		getADD();
		last_expression_type = 1;
		item();
	}
	// 表达式
}

void expression(int &type, string &ansTmp)
{
	bool isMinu = false;
	string res, left, right;
	if (symbol == PLUS || symbol == MINU)
	{
		isMinu = (symbol == MINU);
		getADD();
		type = 1;
	}

	item(type, left);

	if (isMinu)
	{
		res = get_tmp_value();
		//向符号表插入一个新的中间变量
		insert_tmp_value(res, 1, 0);
		//如果项的开头第一个token是负号，用0-负号后内容作为新的变量来表示它
		//例如 a=-b;---->t1=0-b;a=t1;
		insert_mid_code(res, "0", MINUOP, left);
		//那么左操作数就是0-负号的变量
		left = res;
	}

	while (symbol == PLUS || symbol == MINU)
	{
		isMinu = (symbol == MINU);
		getADD();
		type = 1;
		item(type, right);
		res = get_tmp_value();
		insert_tmp_value(res, 1, 0);
		//如果是减号输出中间代码为减法
		//例如a-b---->t1=a-b
		if (isMinu)
			insert_mid_code(res, left, MINUOP, right);
		//如果是加号输出中间代码为加法
		//例如a+b---->t1=a+b
		else
			insert_mid_code(res, left, PLUSOP, right);
		left = res;
	}
	//把现在形成的最左操作数返回给上层
	ansTmp = left;
}

void item()
{
	factor();
	while (symbol == MULT || symbol == DIV)
	{
		getMULT();
		last_expression_type = 1;
		factor();
	}
	// 项
}

void item(int &type, string &ansTmp)
{
	string res, left, right;
	//因子的类型传回给项
	factor(type, left);
	while (symbol == MULT || symbol == DIV)
	{
		int multOp = symbol;
		get_token();
		//因子的类型传回给项
		type = 1;
		factor(type, right);
		//存放中间变量
		res = get_tmp_value();
		insert_tmp_value(res, 1, 0);
		//如果token是乘号生成新的乘法中间代码
		if (multOp == MULT)
			insert_mid_code(res, left, MULTOP, right);
		//如果token是除号生成新的除法中间代码
		else
			insert_mid_code(res, left, DIVOP, right);
		left = res;
	}
	//把最后的中间变量返回给上层
	ansTmp = left;
}

void value_parameter_table()
{
	int tmpParameterCount = 0;
	string tmpFunctionCall = last_func_call;

	// 如果直接遇上分号，进行错误处理
	if (symbol == RPARENT || symbol == SEMICN)
	{
		// 值参数表		// 值参数表为空，直接返回
	}
	else
	{
		expression();
		// 判断值参数表和参数表中对应位置的参数类型是否相同
		if (tmpParameterCount < func_parameter_count[tmpFunctionCall] &&
			last_expression_type != func_parameter_type[tmpFunctionCall][tmpParameterCount])
		{
			error('e');
		}
		tmpParameterCount++;

		while (symbol == COMMA)
		{
			get_token();
			expression();
			// 判断值参数表和参数表中对应位置的参数类型是否相同
			if (tmpParameterCount < func_parameter_count[tmpFunctionCall] &&
				last_expression_type != func_parameter_type[tmpFunctionCall][tmpParameterCount])
			{
				error('e');
			}
			tmpParameterCount++;
		}
		// 值参数表
	}
	// 判断值参数表和参数表中对应位置的参数数量是否相同
	if (tmpParameterCount != func_parameter_count[tmpFunctionCall])
	{
		error('d');
	}
}

void func_call()
{
	identifier();
	// 检查是否有未定义的名字
	if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
	{
		error('c');
	}
	else
	{
		// 如果该标识符为函数，且返回值为整型
		if (functionReturnType.count(L_Identifier) > 0 && functionReturnType[L_Identifier] == 1)
		{
			last_expression_type = 1;
		}
	}

	// 更新函数调用的名称
	last_func_call = L_Identifier;

	get_token(); // symbol = (

	int tmpLastExpressionType = last_expression_type;
	value_parameter_table();
	last_expression_type = tmpLastExpressionType;

	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	// 有返回值函数调用语句
}

void factor()
{
	if (symbol == IDENFR)
	{
		// 可能为变量或者有返回值函数调用语句
		get_token(0);

		if (symbol == LPARENT)
		{
			backToken();
			func_call();
		}
		else
		{
			backToken();
			identifier();

			// 检查是否有未定义的名字
			if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
			{
				error('c');
			}
			else if (symbol_table[nowTable].find(L_Identifier) != symbol_table[nowTable].end())
			{
				if (symbol_table[nowTable][L_Identifier].type >= 1 && symbol_table[nowTable][L_Identifier].type <= 3)
				{
					last_expression_type = 1;
				}
			}
			else if (symbol_table[PROGRAM].find(L_Identifier) != symbol_table[PROGRAM].end())
			{
				if (symbol_table[PROGRAM][L_Identifier].type >= 1 && symbol_table[PROGRAM][L_Identifier].type <= 3)
				{
					last_expression_type = 1;
				}
			}

			int tmpLastExpressionType = last_expression_type; // 记录表达式类型临时变量

			if (symbol == LBRACK)
			{
				get_token();
				expression();

				// 数组下标不可为字符型
				if (last_expression_type == 2)
				{
					error('i');
				}

				if (symbol != RBRACK)
				{
					error('m');
				}
				else
				{
					get_token();
				}
			}
			if (symbol == LBRACK)
			{
				get_token();
				expression();

				// 数组下标不可为字符型
				if (last_expression_type == 2)
				{
					error('i');
				}

				if (symbol != RBRACK)
				{
					error('m');
				}
				else
				{
					get_token();
				}
			}
			last_expression_type = tmpLastExpressionType;
		}
	}
	else if (symbol == LPARENT)
	{
		get_token();
		expression();
		last_expression_type = 1;
		if (symbol != RPARENT)
		{
			error('l');
		}
		else
		{
			get_token();
		}
	}
	else if (symbol == INTCON || symbol == PLUS || symbol == MINU)
	{
		integer();
		last_expression_type = 1;
	}
	else
	{ // if (symbol == CHARCON)
		Char();
	}
	// 因子
}

void factor(int &type, string &ansTmp)
{
	type = 1;
	if (symbol == IDENFR)
	{
		get_token(0);
		if (symbol == LPARENT)
		{
			backToken();
			func_call();
		}
		else
		{
			backToken();
			identifier();
			string tmpL_Identifier = L_Identifier;

			// 检查是否有未定义的名字
			if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
			{
				error('c');
			}
			else if (symbol_table[nowTable].find(L_Identifier) != symbol_table[nowTable].end())
			{
				if (symbol_table[nowTable][L_Identifier].type >= 1 && symbol_table[nowTable][L_Identifier].type <= 3)
				{
					last_expression_type = 1;
				}
			}
			else if (symbol_table[PROGRAM].find(L_Identifier) != symbol_table[PROGRAM].end())
			{
				if (symbol_table[PROGRAM][L_Identifier].type >= 1 && symbol_table[PROGRAM][L_Identifier].type <= 3)
				{
					last_expression_type = 1;
				}
			}

			int tmpLastExpressionType = last_expression_type; // 记录表达式类型临时变量

			int d = 0;
			if (symbol == LBRACK)
			{
				d++;
				get_token();
				expression();
				// 数组下标不可为字符型
				if (last_expression_type == 2)
					error('i');

				if (symbol != RBRACK)
					error('m');
				else
					get_token();
			}
			if (symbol == LBRACK)
			{
				d++;
				get_token();
				expression();
				// 数组下标不可为字符型
				if (last_expression_type == 2)
					error('i');
				if (symbol != RBRACK)
					error('m');
				else
					get_token();
			}
			if (d == 0)
				ansTmp = tmpL_Identifier;
			last_expression_type = tmpLastExpressionType;
		}
	}
	else if (symbol == LPARENT)
	{
		get_token();
		expression(type, ansTmp);
		type = 1;
		if (symbol != RPARENT)
			error('1');
		else
			get_token();
	}
	else if (symbol == INTCON || symbol == PLUS || symbol == MINU)
	{
		int value;
		integer(value);
		ansTmp = to_string(value);
	}
	else if (symbol == CHARCON)
	{
		Char(ansTmp);
	}
}

void condition()
{
	expression();
	if (last_expression_type == 2)
	{
		error('f');
	}

	relational_operator();

	expression();
	if (last_expression_type == 2)
	{
		error('f');
	}

	// 条件
}
void fact_sheet()
{
	while (symbol == CASETK)
	{
		case_statement();
	}
	// 情况表
}
void write_statement()
{
	get_token();
	get_token();
	if (symbol == STRCON)
	{
		string nowString = tokenBuffer;
		int pos = 0;
		while ((pos = nowString.find("\\", pos + 2)) != string::npos)
		{
			nowString.replace(pos, 1, "\\\\");
		}
		insert_string_const(nowString);
		String();
		if (symbol == COMMA)
		{
			//如果在逗号之后，那么一定是打印字符串和表达式
			//输出打印字符串的中间代码
			insert_mid_code(nowString, "3", PRINT, "");
			get_token();
			int type = 2;
			string tmpExpress;
			expression(type, tmpExpress);
			//输出打印表达式的中间代码
			insert_mid_code(tmpExpress, to_string(type), PRINT, "");
			//输出打印换行符的中间代码
			insert_mid_code("changeLine", "4", PRINT, "");
		}
		else
		{
			//如果没有逗号，那么就是单纯的打印字符串
			//输出打印字符串的中间代码
			insert_mid_code(nowString, "3", PRINT, "");
			//输出打印换行符的中间代码
			insert_mid_code("changeLine", "4", PRINT, "");
		}
	}
	else
	{
		//没有字符串，只打印表达式
		int type = 2;
		string tmpExpress;
		expression(type, tmpExpress);
		//输出打印表达式的中间代码
		insert_mid_code(tmpExpress, to_string(type), PRINT, "");
		//输出打印换行符的中间代码
		insert_mid_code("changeLine", "4", PRINT, "");
	}

	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	// 写语句
}

void switch_statement()
{
	// symbol == SWITCHTK
	get_token(); // symbol = (
	get_token();
	expression();

	last_constant_type = last_expression_type - 1; // 更新switch语句中的常量的类型

	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	// symbol == {
	get_token();
	fact_sheet();

	// 错误处理，如果没有缺省语句
	if (symbol != DEFAULTTK)
	{
		error('p');
	}
	else
	{
		deft();
	}

	// symbol == }
	get_token();
	// 情况语句
}
void statement()
{
	if (symbol == WHILETK || symbol == FORTK)
	{
		loop_statement();
	}
	else if (symbol == IFTK)
	{
		condition_statement();
	}
	else if (symbol == IDENFR)
	{
		string tmpIdenfr = tokenBuffer;

		// 检查是否有未定义的名字
		if (symbol_table[nowTable].find(tmpIdenfr) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(tmpIdenfr) == symbol_table[PROGRAM].end())
		{
			error('c');
		}
		else
		{
			if (functionWithReturnValue.count(tmpIdenfr) > 0)
			{
				func_call();
			}
			else if (functionWithoutReturnValue.count(tmpIdenfr) > 0)
			{
				void_func_call();
			}
			else
			{
				// 判断是否给常量进行了赋值操作
				if ((symbol_table[nowTable].find(tmpIdenfr) != symbol_table[nowTable].end() && symbol_table[nowTable][tmpIdenfr].kind == 0) || (symbol_table[PROGRAM].find(tmpIdenfr) != symbol_table[PROGRAM].end() && symbol_table[PROGRAM][tmpIdenfr].kind == 0))
				{
					error('j');
				}
				assign_statement();
			}
		}

		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
	else if (symbol == SCANFTK)
	{
		read_statement();
		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
	else if (symbol == PRINTFTK)
	{
		write_statement();
		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
	else if (symbol == SWITCHTK)
	{
		switch_statement();
	}
	else if (symbol == SEMICN)
	{
		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
	else if (symbol == RETURNTK)
	{
		return_statement();
		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}
	}
	else if (symbol == LBRACE)
	{
		get_token();
		statement_column();
		// symbol == }
		get_token();
	}
	// 语句
}
void loop_statement()
{
	if (symbol == WHILETK)
	{
		get_token(); // symbol == (
		get_token();
		condition();
		if (symbol != RPARENT)
		{
			error('l');
		}
		else
		{
			get_token();
		}
		statement();
	}
	else if (symbol == FORTK)
	{
		get_token(); // symbol = (
		get_token();
		identifier();

		// 检查是否有未定义的名字
		if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
		{
			error('c');
		}

		// symbol == '='
		get_token();
		expression();

		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}

		condition();

		if (symbol != SEMICN)
		{
			error('k');
		}
		else
		{
			get_token();
		}

		identifier();

		// 检查是否有未定义的名字
		if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
		{
			error('c');
		}

		// symbol == '='
		get_token();
		identifier();

		// 检查是否有未定义的名字
		if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
		{
			error('c');
		}

		getADD();
		step();
		if (symbol != RPARENT)
		{
			error('l');
		}
		else
		{
			get_token();
		}
		statement();
	}
	// 循环语句
}
void condition_statement()
{
	// symbol == IFTK
	get_token(); // symbol == (
	get_token();
	condition();
	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	statement();
	while (symbol == ELSETK)
	{
		get_token();
		statement();
	}
	// 条件语句
}
void return_statement()
{
	// symbol == RETURNTK
	get_token();
	if (symbol == LPARENT)
	{
		get_token();
		expression();
		returned_type = last_expression_type; // 获取函数实际返回值类型
		if (symbol != RPARENT)
		{
			error('l');
		}
		else
		{
			get_token();
		}

		// 无返回值函数产生了返回值
		if (functionWithoutReturnValue.count(nowTable) > 0)
		{
			error('g');
		}
	}
	else
	{
		returned_type = 3;
	}

	// 有返回值函数返回类型不同
	if (functionWithReturnValue.count(nowTable) > 0 && functionReturnType[nowTable] != returned_type)
	{
		error('h');
	}

	// 返回语句
}
void void_func_call()
{
	identifier();

	// 检查是否有未定义的名字
	if (symbol_table[nowTable].find(L_Identifier) == symbol_table[nowTable].end() && symbol_table[PROGRAM].find(L_Identifier) == symbol_table[PROGRAM].end())
	{
		error('c');
	}

	// 更新函数调用的名称
	last_func_call = L_Identifier;

	// symbol == (
	get_token();

	int tmpLastExpressionType = last_expression_type;
	value_parameter_table();
	last_expression_type = tmpLastExpressionType;

	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	// 无返回值函数调用语句
}
void assign_statement()
{
	identifier();
	string nowIdentifier = L_Identifier;
	if (symbol == LBRACK)
	{
		get_token();
		expression();

		// 数组下标不可为字符型
		if (last_expression_type == 2)
		{
			error('i');
		}

		if (symbol != RBRACK)
		{
			error('m');
		}
		else
		{
			get_token();
		}
	}

	if (symbol == LBRACK)
	{
		get_token();
		int type;
		string tmpExpress;
		expression(type, tmpExpress);

		// 数组下标不可为字符型
		if (last_expression_type == 2)
		{
			error('i');
		}

		if (symbol != RBRACK)
		{
			error('m');
		}
		else
		{
			get_token();
		}
	}

	// symbol == '=';
	get_token();
	int tmpType;
	string tmpExpress;
	expression(tmpType, tmpExpress);
	//插入中间代码，表示赋值
	insert_mid_code(nowIdentifier, tmpExpress, ASSIGNOP, "");
}

void read_statement()
{
	// symbol == SCANFTK
	get_token(); // symbol == (
	get_token();
	identifier();
	string nowIdentifier = L_Identifier;
	// 检查该标识符是否定义以及是否为常量
	if (symbol_table[nowTable].count(L_Identifier) == 1)
	{
		if (symbol_table[nowTable][L_Identifier].kind == 0)
		{
			error('j');
		}
	}
	else if (symbol_table[PROGRAM].count(L_Identifier) == 1)
	{
		if (symbol_table[PROGRAM][L_Identifier].kind == 0)
		{
			error('j');
		}
	}
	else
	{
		error('c');
	}

	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	// 读语句
	insert_mid_code(nowIdentifier, "", SCAN, "");
}

void case_statement()
{
	// symbol == CASETK
	get_token();
	constant();

	// switch语句中常量类型不一致
	if (last_const_type != last_constant_type)
	{
		error('o');
	}

	// symbol == COLON
	get_token();
	statement();
}

void deft()
{
	// symbol == DEFAULTTK
	get_token(); // symbol == COLON
	get_token();
	statement();
}

void statement_column()
{
	while (symbol != RBRACE)
	{
		statement();
	}
}

void compound_statement()
{
	if (symbol == CONSTTK)
	{
		constant_dec();
	}
	if (symbol == INTTK || symbol == CHARTK)
	{
		variable_dec();
	}
	statement_column();
}

void getFunctionDefination(int kind)
{
	returned_type = 0; // 初始化已经返回的参数类型

	identifier();
	// 类型标识符在getProgram中识别
	if (kind == 3)
		functionWithReturnValue.insert(L_Identifier);
	else
		functionWithoutReturnValue.insert(L_Identifier);
	functionReturnType[L_Identifier] = func_return_type;

	// 将该函数名添加到符号表
	init_now_sym();
	now_sym.kind = kind;
	now_sym.type = 0;
	now_sym.name = L_Identifier;
	insert_current_symbol();

	// 更新符号表，增加新的层次
	nowTable = L_Identifier;
	insert_current_level();

	// symbol == (
	get_token();
	parameter_table();
	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	// symbol == {
	get_token();
	compound_statement();

	// symbol == }

	// 有返回值函数缺少返回语句
	if (functionWithReturnValue.count(nowTable) > 0 && returned_type == 0)
	{
		error('h');
	}

	nowTable = PROGRAM; // 返回外层函数

	get_token();
	// 有返回值函数定义
}

void Main()
{
	// 将main添加到无返回值函数
	functionWithoutReturnValue.insert(MAIN);
	functionReturnType[MAIN] = 0;

	// 将main添加到符号表的当前层次
	init_now_sym();
	now_sym.kind = 6;
	now_sym.type = 0;
	now_sym.name = MAIN;
	insert_current_symbol();

	// 更新符号表的层次
	nowTable = MAIN;
	insert_current_level();

	// symbol == MAINTK
	get_token();
	// symbol == (
	get_token(); // symbol == )
	if (symbol != RPARENT)
	{
		error('l');
	}
	else
	{
		get_token();
	}
	insert_mid_code("void", MAIN, FUNC, "");
	// symbol == {
	get_token();
	compound_statement();
	// symbol == }
	get_token();
	// 主函数
}
void program()
{
	// 更新符号表的层次，此处为最外层
	get_token();
	nowTable = PROGRAM;
	insert_current_level();
	// 常量说明
	if (symbol == CONSTTK)
	{
		constant_dec();
	}
	// 变量说明
	while (symbol == INTTK || symbol == CHARTK)
	{
		get_token(0);
		get_token(0);
		if (symbol != LPARENT)
		{
			backToken();
			// outputlastsym();
			program_variable_dec();
		}
		else
		{
			backToken();
			backToken();
			break;
		}
	}
	//函数定义部分
	while (symbol == INTTK || symbol == CHARTK || symbol == VOIDTK)
	{
		if (symbol == INTTK)
		{
			func_return_type = 1;
		}
		else if (symbol == CHARTK)
		{
			func_return_type = 2;
		}
		else
		{
			func_return_type = 0;
		}
		get_token();
		if (symbol == MAINTK)
		{
			break;
		}
		if (func_return_type > 0)
		{
			//有返回值的函数定义
			getFunctionDefination(3);
		}
		else if (func_return_type == 0)
		{
			//无返回值的函数定义
			getFunctionDefination(4);
		}
	}
	// 主函数
	Main();
}
