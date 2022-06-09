#pragma once
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include "parser.h"
using namespace std;

ofstream mid_code_file;
ofstream mips_code_file;

enum mid_code_op
{
	PLUSOP,	  //+
	MINUOP,	  //-
	MULTOP,	  //*
	DIVOP,	  // /
	LSSOP,	  //<
	LEQOP,	  //<=
	GREOP,	  //>
	GEQOP,	  //>=
	EQLOP,	  //==
	NEQOP,	  //!=
	ASSIGNOP, //=
	GOTO,	  //无条件跳转
	BZ,		  //不满足条件跳转
	BNZ,	  //满足条件跳转
	PUSH,	  //函数调用时参数传递
	CALL,	  //函数调用
	RET,	  //函数返回语句
	RETVALUE, //有返回值函数返回的结果
	SCAN,	  //读
	PRINT,	  //写
	LABEL,	  //标号
	CONST,	  //常量
	ARRAY,	  //数组
	VAR,	  //变量
	VARINIT,
	FUNC,	  //函数定义
	PARAM,	  //函数参数
	GETARRAY, //取数组的值  t = a[]
	PUTARRAY, //给数组赋值  a[] = t
	EXIT,	  //退出 main最后
};
struct mid_code
{
	string res;		// 结果
	string left;	// 左操作数
	mid_code_op op; // 运算符
	string right;	// 右操作数
};
vector<mid_code> mid_codes;

enum mips_op
{
	add,
	addi,
	sub,
	mult,
	divop,
	mflo,
	mfhi,
	j,
	lw,
	sw,
	syscall,
	la,
	moveop,
	dataSeg,   //.data
	textSeg,   //.text
	asciizSeg, //.asciiz
	globlSeg,  //.globl
	label,	   //产生标号
};
struct mips_code
{
	mips_op op;	  //操作类型
	string res;	  //结果
	string left;  //左操作数
	string right; //右操作数
	int imm;	  //立即数
};
vector<mips_code> mips_codes;

//其他变量
string func_name = "";
vector<string> string_const;				 //存放字符常量
unordered_map<string, int> string_index_map; //根据字符串反查下标
int string_cnt = 0;							 //字符常量的个数

void insert_mid_code(string result, string left, mid_code_op op, string right)
{
	mid_codes.emplace_back(mid_code{result, left, op, right});
}

void output_mid_code(struct mid_code mc)
{
	switch (mc.op)
	{
	case PLUSOP:
		mid_code_file << mc.res << " = " << mc.left << " + " << mc.right << "\n";
		break;
	case MINUOP:
		mid_code_file << mc.res << " = " << mc.left << " - " << mc.right << "\n";
		break;
	case MULTOP:
		mid_code_file << mc.res << " = " << mc.left << " * " << mc.right << "\n";
		break;
	case DIVOP:
		mid_code_file << mc.res << " = " << mc.left << " / " << mc.right << "\n";
		break;
	case ASSIGNOP:
		mid_code_file << mc.res << " = " << mc.left << "\n";
		break;
	case RETVALUE:
		mid_code_file << "RETVALUE " << mc.res << " = " << mc.left << "\n";
		break;
	case SCAN:
		mid_code_file << "SCAN " << mc.res << "\n";
		break;
	case PRINT:
		mid_code_file << "PRINT " << mc.res << " " << mc.left << "\n";
		break;
	case LABEL:
		mid_code_file << mc.res << ": \n";
		break;
	case VARINIT:
		mid_code_file << mc.res << " VARINIT" << endl;
		break;
	case FUNC:
		mid_code_file << "FUNC " << mc.res << " " << mc.left << "()" << endl;
		break;
	case PARAM:
		mid_code_file << "PARA " << mc.res << " " << mc.left << endl;
		break;
	default:
		break;
	}
}

void output_mid_code_all()
{
	for (auto mid_code : mid_codes)
		output_mid_code(mid_code);
}

void insert_string_const(string s)
{
	string_const.push_back(s);
	string_index_map[s] = string_cnt++;
}

void insert_mips_code(mips_op op, string res, string left, string right, int imm = 0)
{
	mips_codes.push_back(mips_code{op, res, left, right, imm});
}

void save_instr(string identifier, string reg)
{
	if (symbol_table[PROGRAM].find(identifier) != symbol_table[PROGRAM].end() &&
		((symbol_table[PROGRAM][identifier].kind == 1) || symbol_table[PROGRAM][identifier].kind == 2))
	{
		int addr = (symbol_table[PROGRAM][identifier].addr << 2);
		insert_mips_code(sw, reg, "$gp", "", addr);
	}
	else if (symbol_table[func_name].find(identifier) != symbol_table[func_name].end() &&
			 (symbol_table[func_name][identifier].kind == 1 || symbol_table[func_name][identifier].kind == 2))
	{
		int addr = -(symbol_table[func_name][identifier].addr << 2);
		insert_mips_code(sw, reg, "$fp", "", addr);
	}
}

void load_instr(string identifier, string reg, bool gene, int &va, bool &get)
{
	struct sym now_identifier;
	if (symbol_table[PROGRAM].find(identifier) != symbol_table[PROGRAM].end())
	{
		now_identifier = symbol_table[PROGRAM][identifier];
		if (now_identifier.kind == 0)
		{
			if (now_identifier.type == 1)
				va = now_identifier.value;
			else
				va = now_identifier.str[0];
			if (gene)
				insert_mips_code(addi, reg, "$0", "", va);
			get = true;
		}
		else
		{
			int addr = (symbol_table[PROGRAM][identifier].addr << 2);
			insert_mips_code(lw, reg, "$gp", "", addr);
		}
	}
	else if (symbol_table[func_name].find(identifier) != symbol_table[func_name].end())
	{
		now_identifier = symbol_table[func_name][identifier];
		if (now_identifier.kind == 0)
		{
			if (now_identifier.type == 1)
				va = now_identifier.value;
			else
				va = now_identifier.str[0];
			if (gene)
				insert_mips_code(addi, reg, "$0", "", va);
			get = true;
		}
		else
		{
			int addr = -(symbol_table[func_name][identifier].addr << 2);
			insert_mips_code(lw, reg, "$fp", "", addr);
		}
	}
	else
	{
		va = stoi(identifier);
		if (gene)
			insert_mips_code(addi, reg, "$0", "", va);
		get = true;
	}
}

void generate_mips_code()
{
	//首先是data段
	insert_mips_code(dataSeg, "", "", "", 0);
	//先把常量字符串加载进去
	for (int i = 0; i < string_const.size(); i++)
	{
		insert_mips_code(asciizSeg, "string" + to_string(i), string_const[i], "");
	}
	insert_mips_code(asciizSeg, "changeLine", "\\n", "");

	//其次是text代码段
	insert_mips_code(textSeg, "", "", "");

	bool get1 = false, get2 = false;
	bool flag = false;
	int pushCnt = 0;
	int paramSize = 0;
	int va = 0, addr = 0, len = 0, va2 = 0;
	bool goMain = false;
	stack<struct mid_code> pushOpStack;

	for (auto mc : mid_codes)
	{
		get1 = false;
		get2 = false;
		switch (mc.op)
		{
		case VARINIT:
		{
			if (symbol_table[PROGRAM].find(mc.res) != symbol_table[PROGRAM].end())
			{
				struct sym tmp = symbol_table[PROGRAM][mc.res];
				if (tmp.kind == 1)
				{
					insert_mips_code(addi, "$t0", "$0", "", tmp.value);
				}
				else
				{
					insert_mips_code(addi, "$t0", "$0", "", tmp.str[0]);
				}
				save_instr(mc.res, "$t0");
			}
			else if (symbol_table[func_name].find(mc.res) != symbol_table[func_name].end())
			{
				struct sym tmp = symbol_table[func_name][mc.res];
				if (tmp.kind == 1)
				{
					insert_mips_code(addi, "$t0", "$0", "", tmp.value);
				}
				else
				{
					insert_mips_code(addi, "$t0", "$0", "", tmp.str[0]);
				}
				save_instr(mc.res, "$t0");
			}
			break;
		}
		case PLUSOP:
		{
			load_instr(mc.left, "$t0", false, va, get1);
			load_instr(mc.right, "$t1", false, va2, get2);
			if (get1 && get2)
			{
				insert_mips_code(addi, "$t2", "$0", "", va + va2);
			}
			else if (get1 && !get2)
			{
				insert_mips_code(addi, "$t2", "$t1", "", va);
			}
			else if (!get1 && get2)
			{
				insert_mips_code(addi, "$t2", "$t0", "", va2);
			}
			else
			{
				insert_mips_code(add, "$t2", "$t0", "$t1");
			}
			save_instr(mc.res, "$t2");
			break;
		}
		case MINUOP:
		{
			load_instr(mc.left, "$t0", false, va, get1);
			load_instr(mc.right, "$t1", false, va2, get2);
			if (get1 && get2)
			{
				insert_mips_code(addi, "$t2", "$0", "", va - va2);
			}
			else if (get1 && !get2)
			{
				insert_mips_code(addi, "$t2", "$t1", "", -va);
			}
			else if (!get1 && get2)
			{
				insert_mips_code(addi, "$t2", "$t0", "", -va2);
			}
			else
			{
				insert_mips_code(sub, "$t2", "$t0", "$t1");
			}
			save_instr(mc.res, "$t2");
			break;
		}
		case MULTOP:
		{
			load_instr(mc.left, "$t0", true, va, get1);
			load_instr(mc.right, "$t1", true, va2, get2);
			insert_mips_code(mult, "$t0", "$t1", "");
			insert_mips_code(mflo, "$t2", "", "");
			save_instr(mc.res, "$t2");
			break;
		}
		case DIVOP:
		{
			load_instr(mc.left, "$t0", true, va, get1);
			load_instr(mc.right, "$t1", true, va2, get2);
			insert_mips_code(divop, "$t0", "$t1", "");
			insert_mips_code(mflo, "$t2", "", "");
			save_instr(mc.res, "$t2");
			break;
		}
		case ASSIGNOP:
		{
			load_instr(mc.left, "$t0", true, va, get1);
			save_instr(mc.res, "$t0");
			break;
		}
		case SCAN:
		{
			if (symbol_table[PROGRAM].find(mc.res) != symbol_table[PROGRAM].end() &&
				(symbol_table[PROGRAM][mc.res].kind == 1 || symbol_table[PROGRAM][mc.res].kind == 2))
			{
				int callType;
				callType = (symbol_table[PROGRAM][mc.res].type == 1) ? 5 : 12;
				insert_mips_code(addi, "$v0", "$0", "", callType);
				insert_mips_code(syscall, "", "", "");
				addr = (symbol_table[PROGRAM][mc.res].addr << 2);
				insert_mips_code(sw, "$v0", "$gp", "", addr);
			}
			else if (symbol_table[func_name].find(mc.res) != symbol_table[func_name].end() &&
					 (symbol_table[func_name][mc.res].kind == 1 || symbol_table[func_name][mc.res].kind == 2))
			{
				int callType;
				callType = (symbol_table[func_name][mc.res].type == 1) ? 5 : 12;
				insert_mips_code(addi, "$v0", "$0", "", callType);
				insert_mips_code(syscall, "", "", "");
				addr = -(symbol_table[func_name][mc.res].addr << 2);
				insert_mips_code(sw, "$v0", "$fp", "", addr);
			}
			break;
		}
		case PRINT:
		{
			if (mc.left[0] == '1')
			{ // int
				load_instr(mc.res, "$a0", true, va, get1);
				insert_mips_code(addi, "$v0", "$0", "", 1);
				insert_mips_code(syscall, "", "", "");
			}
			else if (mc.left[0] == '2')
			{ // char
				load_instr(mc.res, "$a0", true, va, get1);
				insert_mips_code(addi, "$v0", "$0", "", 11);
			}
			else if (mc.left[0] == '3')
			{ // string
				insert_mips_code(la, "$a0", "string" + to_string(string_index_map[mc.res]), "", 0);
				insert_mips_code(addi, "$v0", "$0", "", 4);
				insert_mips_code(syscall, "", "", "");
			} // changeLine
			else if (mc.left[0] == '4')
			{
				insert_mips_code(la, "$a0", "changeLine", "", 0);
				insert_mips_code(addi, "$v0", "$0", "", 4);
				insert_mips_code(syscall, "", "", "");
			}
			break;
		}
		case FUNC:
		{
			if (!goMain)
			{
				//进入main函数入口
				insert_mips_code(j, "main", "", "");
				goMain = true;
			}
			insert_mips_code(label, mc.left, "", "", 0);
			func_name = mc.left;
			if (mc.left == MAIN)
			{
				len = symbol_table[MAIN].size();
				insert_mips_code(addi, "$fp", "$sp", "", 0);
				insert_mips_code(addi, "$sp", "$sp", "", -4 * len - 8);
			}
			break;
		}
		default:
			break;
		}
	}

	insert_mips_code(addi, "$v0", "$0", "", 10);
	insert_mips_code(syscall, "", "", "");
}

void output_mips_code(struct mips_code mc)
{
	switch (mc.op)
	{
	case add:
		mips_code_file << "add " << mc.res << "," << mc.left << "," << mc.right << "\n";
		break;
	case sub:
		mips_code_file << "sub " << mc.res << "," << mc.left << "," << mc.right << "\n";
		break;
	case mult:
		mips_code_file << "mult " << mc.res << "," << mc.left << "\n";
		break;
	case divop:
		mips_code_file << "div " << mc.res << "," << mc.left << "\n";
		break;
	case addi:
		mips_code_file << "addi " << mc.res << "," << mc.left << "," << mc.imm << "\n";
		break;
	case mflo:
		mips_code_file << "mflo " << mc.res << "\n";
		break;
	case j:
		mips_code_file << "j " << mc.res << "\n";
		break;
	case lw:
		mips_code_file << "lw " << mc.res << "," << mc.imm << "(" << mc.left << ")\n";
		break;
	case sw:
		mips_code_file << "sw " << mc.res << "," << mc.imm << "(" << mc.left << ")\n";
		break;
	case la:
		mips_code_file << "la " << mc.res << "," << mc.left << "\n";
		break;
	case syscall:
		mips_code_file << "syscall\n";
		break;
	case moveop:
		mips_code_file << "move " << mc.res << "," << mc.left << "\n";
		break;
	case dataSeg:
		mips_code_file << ".data\n";
		break;
	case textSeg:
		mips_code_file << ".text\n";
		break;
	case asciizSeg:
		mips_code_file << mc.res << ": .asciiz \"" << mc.left << "\"\n";
		break;
	case label:
		mips_code_file << mc.res << ":\n";
		break;
	default:
		break;
	}
}

void output_mips_code_all()
{
	for (auto mips_code : mips_codes)
		output_mips_code(mips_code);
}

void to_mips()
{
	output_mid_code_all();
	generate_mips_code();
	output_mips_code_all();
}