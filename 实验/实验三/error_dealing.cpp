#include <stdlib.h>
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<map>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
using namespace std; 

//------------------------词法分析的变量---------------------------
const int MAXN=2000;
//词法分析token序列
string token[MAXN];		
string val[MAXN];
int row[MAXN];
int col[MAXN];
int p = 0;
int cnmd =0;
int line=1;
int cur=0;
ofstream fout=ofstream("error.txt");
//------------------------词法分析的函数---------------------------
//看是否为数字
bool number(char A){
	if(A>='0'&&A<='9')
		return true;
	return false;
}
//看是否为字母或下划线 
bool letter(char A){
	if((A=='_')||(A>='A'&&A<='Z')||(A>='a'&&A<='z'))
		return true;
	return false;
}
//看是否是保留字或标识符 
bool reserved_word(string s){
	if(s=="const")
	{
		token[p++] = "CONSTTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="int"){
		token[p++] = "INTTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="char"){
		token[p++] = "CHARTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="void"){
		token[p++] = "VOIDTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="main"){
		token[p++] = "MAINTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="if"){
		token[p++] = "IFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="else"){
		token[p++] = "ELSETK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="do"){
		token[p++] = "DOTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="while"){
		token[p++] = "WHILETK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="for"){
		token[p++] = "FORTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="scanf")
	{
		token[p++] = "SCANFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="printf")
	{
		token[p++] = "PRINTFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="return")
	{ 
		token[p++] = "RETURNTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="switch")
	{ 
		token[p++] = "SWITCHTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="case")
	{ 
		token[p++] = "CASETK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="default")
	{ 
		token[p++] = "DEFAULTTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="PRINTF")
	{ 
		token[p++] = "PRINTFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	if(s=="printF"){
		token[p++] = "PRINTFTK";
		val[cnmd++] = s;
		row[p-1]=line;
		col[p-1]=cur;
		return true;
	}
	return false;
}
void lexical_analysis(){
	//标识符、整数、字符、字符串、保留字、运算符、分界符
	FILE *f;
	char CHAR;
	f=fopen("testfile.txt","r"); 
	//读取文件并处理
	while((CHAR=fgetc(f))!=EOF){
		cur++;
		//除了空格和Tab全读取
		while(CHAR!=' '&&int(CHAR)!=9){
			//以字母或开头,要么是保留字，要么是标识符 
			if(letter(CHAR)){
				string s="";
				int k=0;
				do{
					s+=CHAR;
				}
				while((CHAR=fgetc(f))!=EOF&&CHAR!=' '&&(letter(CHAR)||number(CHAR)));
				fseek(f,-1,SEEK_CUR);
				if(!(reserved_word(s)))//判断标识符是保留字还是标识符 
				{
					token[p++] = "IDENFR";
					val[cnmd++] = s;
					row[p-1]=line;
					col[p-1]=cur;
				} 
				cur+=s.length();
			}
			//整数
			else if(number(CHAR)){
				string s="";
				int i=0;
				do{
					s+=CHAR;
		
				}
				while((CHAR=fgetc(f))!=EOF&&CHAR!=' '&&number(CHAR));
				fseek(f,-1,SEEK_CUR);
				token[p++] = "INTCON";
				val[cnmd++] = s;
				row[p-1]=line;
				col[p-1]=cur;
				cur+=s.length();
			}
			//运算符 
			else if(CHAR=='+'){
				token[p++] = "PLUS";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='-'){
				token[p++] = "MINU";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='*'){
				token[p++] = "MULT";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			//不用处理注释
			else if(CHAR=='/'){
				token[p++] = "DIV";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='='){
				//后一个符号也是等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='=')
				{
					token[p++] = "EQL";
					val[cnmd++] = "==";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//直接标记等号，然后回退
				else{
					token[p++] = "ASSIGN";
					val[cnmd++] = "=";
					row[p-1]=line;
					col[p-1]=cur;
					fseek(f,-1,SEEK_CUR);
					break;
				}
			}
			else if(CHAR=='<'){
				//小于等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='='){
					token[p++] = "LEQ";
					val[cnmd++] = "<=";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//小于，回退，因为向后读取了一个字符
				else {
					token[p++] = "LSS";
					val[cnmd++] = "<";
					row[p-1]=line;
					col[p-1]=cur;
					fseek(f,-1,SEEK_CUR);
				}
			}
			else if(CHAR=='>'){
				//大于等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='='){
					token[p++] = "GEQ";
					val[cnmd++] = ">=";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//大于，回退，因为向后读取了一个字符
				else {
					token[p++] = "GRE";
					val[cnmd++] = ">";
					row[p-1]=line;
					col[p-1]=cur;
					fseek(f,-1,SEEK_CUR);
				}
			}
			else if(CHAR=='!'){
				//不等于
				if((CHAR=fgetc(f))!=EOF&&CHAR=='='){
					token[p++] = "NEQ";
					val[cnmd++] = "!=";
					row[p-1]=line;
					col[p-1]=cur;
					cur+=1;
				}
				//感叹号后只可能是等于
			}
			//分界符
			else if(CHAR=='('){
				token[p++] = "LPARENT";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==')'){
				token[p++] = "RPARENT";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='['){
				token[p++] = "LBRACK";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==']'){
				token[p++] = "RBRACK";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='{'){
				token[p++] = "LBRACE";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR=='}'){
				token[p++] = "RBRACE";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			//标点符号
			else if(CHAR==':'){
				token[p++] = "COLON";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==';'){
				token[p++] = "SEMICN";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			else if(CHAR==','){
				token[p++] = "COMMA";
				val[cnmd++] += CHAR;
				row[p-1]=line;
				col[p-1]=cur;
			}
			//判断字符和字符串
			//如果是单影号，字符
			else if(CHAR=='\''){
				string s = ""; 
				while((CHAR=fgetc(f))!=EOF&&CHAR!='\'')
				{
					s+=CHAR;
				}
				token[p++] = "CHARCON";
				val[cnmd++] = s;
				row[p-1]=line;
				col[p-1]=cur+1;
				cur+=s.length()+1;
			}
			//如果是双赢号，字符串
			else if(CHAR=='"'){
				string s = ""; 
				while((CHAR=fgetc(f))!=EOF&&CHAR!='"')
				{
					s+=CHAR;	
				}
				token[p++] = "STRCON";
				val[cnmd++] = s;
				row[p-1]=line;
				col[p-1]=cur+1;
				cur+=s.length()+1;
			}
			else if(CHAR=='\n'){
				line++;
				cur=0;
			}
			else{
				//错误处理接口
				cout<<"\""<<CHAR<<"\""<<" in line "<<line<<" , column "<<cur<<endl;
			}
			break;
		}
	}
	fclose(f);
	for(int i=0;i<p;i++){
		//cout<<token[i]<<" "<<val[i]<<" "<<row[i]<<" "<<col[i]<<endl;
	}
}


class attributes{
public:
	string type;
	vector<int> quote_lines;
	int declaim_line;
	vector<string> parameter_types;
	bool has_retval;
	bool is_const=false;
};

//-------------------------语法分析--------------------------
class yufafenxi{
private:
	string curtok="";
	string unregonized="";
	int toknum=0;
	int curindex=0;
	int is_def_func =0;
	string def_func_type="";
	unordered_map<string, bool> has_retval;
	unordered_map<string, vector<string>> parameters;
	stack<unordered_map<string,attributes>*>symbol_table;
	unordered_map<string,attributes>*global_symbol_table;
public:
	void nexttoken(){
	if(curindex<toknum){
		curtok=token[curindex++];
		//fout<<token[curindex-1]<<" "<<val[curindex-1]<<endl;
	}
	else{
		curtok=unregonized;
	}
}
	string seek(int step){
		if(step+curindex>=0&&curindex+step-1<toknum){
			return token[curindex+step-1];
		}
		else{
			return unregonized;
		}
	}

	void b_error(){
		fout<<row[curindex-1]<<" "<<"b"<<endl;
	}
	void c_error(){
		fout<<row[curindex-1]<<" "<<"c"<<endl;
	}
	void d_error(){
		fout<<row[curindex-1]<<" "<<"d"<<endl;
	}
	void e_error(){
		fout<<row[curindex-1]<<" "<<"e"<<endl;
	}
	void f_error(){
		fout<<row[curindex-1]<<" "<<"f"<<endl;
	}
	void g_error(){
		fout<<row[curindex-1]<<" "<<"g"<<endl;
	}
	void h_error(){
		fout<<row[curindex-1]<<" "<<"h"<<endl;
	}
	void i_error(){
		fout<<row[curindex-1]<<" "<<"i"<<endl;
	}
	void j_error(){
		fout<<row[curindex-1]<<" "<<"j"<<endl;
	}
	void k_error(){
		fout<<row[curindex-1]<<" "<<"k"<<endl;
	}
	void l_error(){
		fout<<row[curindex-1]<<" "<<"l"<<endl;
	}
	void m_error(){
		if(seek(1)=="RBRACK"){
			nexttoken();
		}
		else{
			fout<<row[curindex-1]<<" "<<"m"<<endl;
		}
	}
	void n_error(){
		fout<<row[curindex-1]<<" "<<"n"<<endl;
	}
	void o_error(){
		fout<<row[curindex-1]<<" "<<"o"<<endl;
	}
	void p_error(){
		fout<<row[curindex-1]<<" "<<"p"<<endl;
	}
	void CHAR(){
		if(val[curindex-1]=="+"||val[curindex-1]=="-"||val[curindex-1]=="*"||val[curindex-1]=="/"\
		||val[curindex-1]=="_"||isalpha(int(val[curindex-1][0]))||isdigit(int(val[curindex-1][0]))){
		
		}
		else{
			fout<<row[curindex-1]<<" "<<"a"<<endl;
		}
	}
	string CONST(){
		if(curtok=="PLUS"||curtok=="MINU"||curtok=="INTCON"||curtok=="CHARCON"){
			if(curtok!="CHARCON"){
				integer();
				return "INTTK";
			}
			else{
				CHAR();
				return "CHARTK";
			}
			//fout<<"<常量>"<<endl;
		}
		return "";
	}
	//无符号整数
	void unsigned_integer(){
		if(curtok=="INTCON"){
			//fout<< "<无符号整数>" << endl;
		}
	}

	//整数
	void integer(){
		if(curtok=="PLUS"||curtok=="MINU"){
			nexttoken();
			unsigned_integer();
		}
		else if(curtok=="INTCON"){
			unsigned_integer();
		}
		//fout<< "<整数>" << endl;
	}

	//常量定义
	void constant_def(){
		if(curtok=="INTTK"){
			nexttoken();
			if(symbol_table.top()->count(val[curindex-1])){
				b_error();
			}
			else{
				attributes att;
				att.type="INTTK";
				att.is_const=true;
				symbol_table.top()->emplace(val[curindex-1],att);
			}
			nexttoken();
			nexttoken();
			integer();
			while (seek(1)=="COMMA"){
				nexttoken();
				nexttoken();
				if(symbol_table.top()->count(val[curindex-1])){
					b_error();
				}
				else{
					attributes att;
					att.type="INTTK";
					symbol_table.top()->emplace(val[curindex-1],att);
				}
				nexttoken();
				nexttoken();
				integer();
			}
		}
		if(curtok=="CHARTK"){
			nexttoken();
			if(symbol_table.top()->count(val[curindex-1])){
				b_error();
			}
			else{
				attributes att;
				att.type="CHARTK";
				att.is_const=true;
				symbol_table.top()->emplace(val[curindex-1],att);
			}
			nexttoken();
			nexttoken();
			CHAR();
			while (seek(1)=="COMMA"){
				nexttoken();
				nexttoken();
				if(symbol_table.top()->count(val[curindex-1])){
					b_error();
				}
				else{
					attributes att;
					att.type="CHARTK";
					symbol_table.top()->emplace(val[curindex-1],att);
				}
				nexttoken();
				nexttoken();
				CHAR();
			}
		}
		//fout<< "<常量定义>" << endl;
	}

	//常量说明
	void constant_desc(){
		nexttoken();
		constant_def();
		if(seek(1)=="SEMICN"){
			nexttoken();
		}
		else{
			k_error();
		}
		while (seek(1)=="CONSTTK"){
			nexttoken();
			nexttoken();
			constant_def();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
		}
		//fout<< "<常量说明>" << endl;
	}

	// 变量定义
	void variable_def(){
		string type=curtok;
		bool is_const_same=true;
		string ttype="";
		//有初始化
		if(seek(2)=="ASSIGN"||(seek(4)=="RBRACK"&&seek(5)=="ASSIGN")||(seek(4)=="RBRACK"&&seek(7)=="RBRACK"&&seek(8)=="ASSIGN")){
			nexttoken();
			if(symbol_table.top()->count(val[curindex-1])){
				b_error();
			}
			else{
				attributes att;
				att.type=type;
				symbol_table.top()->emplace(val[curindex-1],att);
			}
			if(seek(1)=="ASSIGN"){
				nexttoken();
				nexttoken();
				if(curtok!="SEMICN"){
					ttype=CONST();
					if(ttype!=type){
						is_const_same=false;
					}
					ttype="";
				}
				else{
					n_error();
				}
			}
			else if(seek(4)=="ASSIGN"){
				nexttoken();//[
				nexttoken();//ui
				unsigned_integer();
				int def_size=stoi(val[curindex-1]);
				int act_size=0;
				m_error();
				nexttoken();//=
				nexttoken();//{
				nexttoken();
				ttype=CONST();
				if(ttype!=type){
					is_const_same=false;
				}
				ttype="";
				act_size++;
				while (seek(1)=="COMMA")
				{
					nexttoken();
					nexttoken();
					ttype=CONST();
					if(ttype!=type){
						is_const_same=false;
					}
					ttype="";
					act_size++;
				}
				nexttoken();//}
				if(def_size!=act_size){
					n_error();
				}
			}
			else if(seek(7)=="ASSIGN"){
				nexttoken();//[
				nexttoken();//ui
				unsigned_integer();
				int def_size=stoi(val[curindex-1]);
				m_error();
				nexttoken();//[
				nexttoken();
				unsigned_integer();
				int def_len=stoi(val[curindex-1]);
				m_error();
				nexttoken();//=
				int act_size=0;
				vector<int>act_len;
				int cnt=0;
				nexttoken();//{
				nexttoken();//{
				nexttoken();
				ttype=CONST();
				if(ttype!=type){
					is_const_same=false;
				}
				ttype="";
				cnt++;
				while (seek(1)=="COMMA")
				{
					nexttoken();
					nexttoken();
					ttype=CONST();
					if(ttype!=type){
						is_const_same=false;
					}
					ttype="";
					cnt++;
				}	
				nexttoken();//}
				act_size++;
				act_len.push_back(cnt);
				cnt=0;
				while (seek(1)=="COMMA")
				{
					nexttoken();
					nexttoken();
					nexttoken();
					ttype=CONST();
					if(ttype!=type){
						is_const_same=false;
					}
					ttype="";
					cnt++;
					while (seek(1)=="COMMA"){
						nexttoken();
						nexttoken();
						ttype=CONST();
						if(ttype!=type){
							is_const_same=false;
						}
						ttype="";
						cnt++;
					}
					nexttoken();
					act_size++;
					act_len.push_back(cnt);
					cnt=0;
				}
				nexttoken();//}
				if(act_size!=def_size){
					n_error();
				}
				else{
					for(auto &i:act_len){
						if(i!=def_len){
							n_error();
							break;
						}
					}
				}
			}
			if(!is_const_same){
				o_error();
			}
			//fout<< "<变量定义及初始化>" << endl;
		}
		else{
			nexttoken();
			if(symbol_table.top()->count(val[curindex-1])){
				b_error();
			}
			else{
				attributes att;
				att.type=type;
				symbol_table.top()->emplace(val[curindex-1],att);
			}
			if(seek(1)=="LBRACK"){
				nexttoken();
				nexttoken();
				unsigned_integer();
				m_error();
				if(seek(1)=="LBRACK"){
					nexttoken();
					nexttoken();
					unsigned_integer();
					m_error();
				}
			}
			while (seek(1)=="COMMA"){
				nexttoken();
				nexttoken();
				if(symbol_table.top()->count(val[curindex-1])){
					b_error();
				}
				else{
					attributes att;
					att.type=type;
					symbol_table.top()->emplace(val[curindex-1],att);
				}
				if(seek(1)=="LBRACK"){
					nexttoken();
					nexttoken();
					unsigned_integer();
					m_error();
					if(seek(1)=="LBRACK"){
						nexttoken();
						nexttoken();
						unsigned_integer();
						m_error();
					}
				}
			}
			//fout<< "<变量定义无初始化>" << endl;
		}
		//fout<< "<变量定义>" << endl;
	}
	//变量说明
	void variable_desc(){
		variable_def();
		if(seek(1)=="SEMICN"){
			nexttoken();
		}
		else{
			k_error();
		}
		while ((seek(1)=="INTTK"||seek(1)=="CHARTK")&&(seek(3)=="SEMICN"||\
		seek(3)=="COMMA"||seek(3)=="ASSIGN"||seek(3)=="LBRACK")){
			nexttoken();
			variable_def();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
		}
		//fout<<"<变量说明>" << endl;
	}

	//声明头部
	void declaration_header(){
		string type=curtok;
		def_func_type=type;
		type+="FUN";
		nexttoken();
		if(symbol_table.top()->count(val[curindex-1])){
			b_error();
		}
		else{
			attributes att;
			att.type=type;
			symbol_table.top()->emplace(val[curindex-1],att);
			has_retval.insert(pair<string,bool>(val[curindex-1],true));
		}
		//fout<< "<声明头部>" << endl;
	}
	//参数表
	void parameters_table(){
		string funcname=val[curindex-3];
		if (curtok == "INTTK" || curtok == "CHARTK") {
			parameters[funcname].push_back(curtok);
			(*global_symbol_table)[funcname].parameter_types.push_back(curtok);
			nexttoken();//eat 类型标识符
			if(symbol_table.top()->count(val[curindex-1])){
				b_error();
			}
			else{
				attributes att;
				att.type=token[curindex-2];
				symbol_table.top()->emplace(val[curindex-1],att);
			}
			while (seek(1)== "COMMA") {
				nexttoken();
				nexttoken();
				parameters[funcname].push_back(curtok);
				(*global_symbol_table)[funcname].parameter_types.push_back(curtok);
				nexttoken();
				if(symbol_table.top()->count(val[curindex-1])){
					b_error();
				}
				else{
					attributes att;
					att.type=token[curindex-2];
					symbol_table.top()->emplace(val[curindex-1],att);
				}
			}
		}
		//fout<< "<参数表>" << endl;
	}
	//＜因子＞ ::= ＜标识符＞
//          ｜＜标识符＞'['＜表达式＞']'
//			｜＜标识符＞'['＜表达式＞']''['＜表达式＞']'
//          |'('＜表达式＞')'
//          ｜＜整数＞
//          |＜字符＞
//          ｜＜有返回值函数调用语句＞
	void factor(){
		if(curtok=="IDENFR"){
			if(!symbol_table.top()->count(val[curindex-1])&&\
			!has_retval.count(val[curindex-1])&&\
			!global_symbol_table->count(val[curindex-1])){
				c_error();
			}
			if(has_retval[val[curindex-1]]){
				funcall();
			}
			else if(seek(1)=="LBRACK"){
				nexttoken();
				nexttoken();
				string type=express();
				if(type=="CHARTK"){
					i_error();
				}
				m_error();
				if(seek(1)=="LBRACK"){
					nexttoken();
					nexttoken();
					string type2=express();
					if(type2=="CHARTK"){
						i_error();
					}
					m_error();
				}
			}
		}
		else if(curtok=="LPARENT"){
			nexttoken();
			express();
			nexttoken();
		}
		else if(curtok=="INTCON"||curtok=="PLUS"||curtok=="MINU"){
			integer();
		}
		else if(curtok=="CHARCON"){
			CHAR();
		}
		//fout<<"<因子>"<<endl;
	}

	//item
	void item(){
		factor();
		while (seek(1)=="MULT"||seek(1)=="DIV"){
			nexttoken();
			nexttoken();
			factor();
		}
		//fout<< "<项>" << endl;
	}

	//express
	string express(){
		string type="INTTK";
		if(curtok=="IDENFR"){
			if(symbol_table.top()->count(val[curindex-1])){
				unordered_map<string,attributes>tst=*symbol_table.top();
				if(tst[val[curindex-1]].type=="CHARTK"){
					type="CHARTK";
				}
			}
			else if(global_symbol_table->count(val[curindex-1])){
				unordered_map<string,attributes>gst=*global_symbol_table;
				if(gst[val[curindex-1]].type=="CHARTKFUN"\
				||gst[val[curindex-1]].type=="CHARTK"){
					type="CHARTK";
				}
			}
		}
		else if(curtok=="CHARCON"){
			type="CHARTK";
		}
		if(curtok=="PLUS"||curtok=="MINU"){
			nexttoken();
		}
		item();
		while(seek(1)=="PLUS"||seek(1)=="MINU"){
			type="INTTK";
			nexttoken();
			nexttoken();
			item();
		}
		return type;
		//fout<< "<表达式>" << endl;
	}

	//condition
	void conditon(){
		string type1,type2;
		type1=express();
		
		if(seek(1)=="LSS"||seek(1)=="LEQ"||seek(1)=="GRE"||seek(1)=="GEQ"||seek(1)=="EQL"||seek(1)=="NEQ"){
			nexttoken();
			nexttoken();
			type2=express();
		}
		if(type1!="INTTK"||type2!="INTTK"){
			f_error();
		}
		//fout<< "<条件>" << endl;	
	}
	//condition statement
	void condition_statement(){
		nexttoken();
		nexttoken();
		conditon();
		nexttoken();
		nexttoken();
		statement();
		if(seek(1)=="ELSETK"){
			nexttoken();
			nexttoken();
			statement();
		}
		//fout<< "<条件语句>" << endl;
	}
	//Value parameter table
	void value_par_table(){
		unordered_map<string,attributes> gst=*global_symbol_table;
		int count1=parameters[val[curindex-3]].size();
		string namet=val[curindex-3];
		int count2=0;
		vector<string>p1;
		vector<string>p2;
		//p1=gst[val[curindex-3]].parameter_types;
		p1=(*global_symbol_table)[val[curindex-3]].parameter_types;
		p2.push_back(express());
		count2++;
		while (seek(1)=="COMMA")
		{
			nexttoken();
			nexttoken();
			p2.push_back(express());
			count2++;
		}
		if(count1!=count2){
			d_error();
		}
		else{
			for(int i=0;i<p2.size();i++){
				if(p1[i]!=p2[i]){
					e_error();
					break;
				}
			}
		}
		//fout<< "<值参数表>" << endl;
	}
	//funcall
	void funcall(){
		nexttoken();
		if(seek(1)!="RPARENT"){
			nexttoken();
			value_par_table();
			nexttoken();
		}
		else{
			if(parameters[val[curindex-2]].size()!=0){
				d_error();
			}
			//fout<<"<值参数表>"<<endl;
			nexttoken();
		}
		//fout<< "<有返回值函数调用语句>" << endl;
	}
	//
	void voidfuncall(){
		nexttoken();
		if(seek(1)=="PLUS"||seek(1)=="MINU"||seek(1)=="IDENFR"\
		||seek(1)=="LPARENT"||seek(1)=="INTCON"||seek(1)=="CHARCON"){
			nexttoken();
			value_par_table();
			nexttoken();
		}
		else{
			if(parameters[val[curindex-2]].size()!=0){
				d_error();
			}
			if(seek(1)!="RPARENT"){
				l_error();
			}
			else{
				nexttoken();
			}
			//fout<<"<值参数表>"<<endl;
			
		}
		//fout<< "<无返回值函数调用语句>" << endl;

	}
	//＜赋值语句＞ ::= ＜标识符＞＝＜表达式＞
	//              |＜标识符＞'['＜表达式＞']'=＜表达式＞
	//              |＜标识符＞'['＜表达式＞']''['＜表达式＞']'=＜表达式＞
	void assign_statement(){
		if(!symbol_table.top()->count(val[curindex-1])&&!global_symbol_table->count(val[curindex-1])){
			c_error();
		}
		bool is_const=false;
		if(symbol_table.top()->count(val[curindex-1])){
			is_const=(*symbol_table.top())[val[curindex-1]].is_const;
		}
		else if(global_symbol_table->count(val[curindex-1])){
			is_const=(*global_symbol_table)[val[curindex-1]].is_const;
		}
		if(is_const==true){
			j_error();
		}
		nexttoken();
		if(curtok=="ASSIGN"){
			nexttoken();
			express();
		}
		else{
			nexttoken();
			string type1=express();
			if(type1=="CHARTK"){
				i_error();
			}
			m_error();
			if(seek(1)=="ASSIGN"){
				nexttoken();
				nexttoken();
				express();
			}
			else{//seek(1)="["
				nexttoken();
				nexttoken();
				string type2=express();
				if(type2=="CHARTK"){
					i_error();
				}
				m_error();
				nexttoken();
				nexttoken();
				express();
			}
		}
		//fout<<"<赋值语句>"<<endl;
	}

	//step
	void step(){
		unsigned_integer();
		//fout<< "<步长>" << endl;
	}
	//＜循环语句＞ ::= while '('＜条件＞')'＜语句＞
	//        | do＜语句＞while '('＜条件＞')'
	//        |for'('＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞')'＜语句＞
	void loop_statement(){
		if(curtok=="WHILETK"){
			nexttoken();
			nexttoken();
			conditon();
			nexttoken();
			nexttoken();
			statement();
		}
		else if(curtok=="FORTK"){
			nexttoken();
			nexttoken();
			if(!symbol_table.top()->count(val[curindex-1])&&!global_symbol_table->count(val[curindex-1])){
				c_error();
			}
			//是不是常量
			bool is_const=false;
			if(symbol_table.top()->count(val[curindex-1])){
				is_const=(*symbol_table.top())[val[curindex-1]].is_const;
			}
			else if(global_symbol_table->count(val[curindex-1])){
				is_const=(*global_symbol_table)[val[curindex-1]].is_const;
			}
			if(is_const==true){
				j_error();
			}
			nexttoken();
			nexttoken();
			express();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
			nexttoken();
			conditon();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
			nexttoken();
			if(!symbol_table.top()->count(val[curindex-1])){
				c_error();
			}
			nexttoken();
			nexttoken();
			if(!symbol_table.top()->count(val[curindex-1])){
				c_error();
			}
			nexttoken();
			nexttoken();
			step();
			nexttoken();
			nexttoken();
			statement();
		}
		//fout<< "<循环语句>" << endl;
	}

	//read statement
	void read_statement(){
		nexttoken();
		nexttoken();
		if(!symbol_table.top()->count(val[curindex-1])&&!global_symbol_table->count(val[curindex-1])){
			c_error();
		}
		bool is_const=false;
		if(symbol_table.top()->count(val[curindex-1])){
			is_const=(*symbol_table.top())[val[curindex-1]].is_const;
		}
		else if(global_symbol_table->count(val[curindex-1])){
			is_const=(*global_symbol_table)[val[curindex-1]].is_const;
		}
		if(is_const==true){
			j_error();
		}
		nexttoken();
		//fout<< "<读语句>" << endl;
	}

	//string
	void str(){
		if(curtok=="STRCON"){
			if(val[curindex-1]==""){
				fout<<"a"<<" "<<row[curindex-1]<<endl;
			}
			else{
				for(auto &c:val[curindex-1]){
					if(int(c)!=34&&int(c)<=126&&int(c)>=32){

					}
					else{
						fout<<row[curindex-1]<<" "<<"a"<<endl;
						break;
					}
				}
			}
			//fout<< "<字符串>" << endl;
		}
	}

	//write statement
	void write_statement(){
		nexttoken();
		nexttoken();
		if(curtok=="STRCON"){
			if(seek(1)=="COMMA"){
				str();
				nexttoken();
				nexttoken();
				express();
				nexttoken();
			}
			else{
				str();
				nexttoken();
			}
		}
		else{
			express();
			nexttoken();
		}
		//fout<< "<写语句>" << endl;

	}

	//＜返回语句＞ ::= return['('＜表达式＞')']
	void return_statement(){
		if(seek(1)=="LPARENT"){
			if(is_def_func==2){
				g_error();
			}
			nexttoken();
			nexttoken();
			string type1=express();
			if(type1!=def_func_type){
				h_error();
			}
			nexttoken();
		}
		else{
			if(is_def_func==1){
				h_error();
			}
			//do nothing
		}
		is_def_func=0;
		//fout<<"<返回语句>"<<endl;
	}

	//case clause
	bool case_clause(string type){
		nexttoken();
		string type2=CONST();
		nexttoken();
		nexttoken();
		statement();
		if(type2==type){
			return true;
		}
		else{
			return false;
		}
		//fout<<"<情况子语句>"<<endl;
	}
	//Fact Sheet
	bool fact_sheet(string type){
		bool is_const_same=true;
		is_const_same=case_clause(type);
		while(seek(1)=="CASETK"){
			nexttoken();
			is_const_same=case_clause(type);
		}
		return is_const_same;
		//fout<<"<情况表>"<<endl;
	}
	void deft(){
		nexttoken();
		nexttoken();
		statement();
		//fout<<"<缺省>"<<endl;
	}
	//case statement
	void case_statement(){
		nexttoken();
		nexttoken();
		string type1=express();
		nexttoken();
		nexttoken();
		nexttoken();
		bool is_const_same=fact_sheet(type1);
		nexttoken();
		if(curtok=="DEFAULTTK"){
			deft();
		}
		else{
			p_error();
		}
		nexttoken();
		if(!is_const_same){
			o_error();
		}
		//fout<<"<情况语句>"<<endl;
	}

	//语句
	void statement(){
		if(curtok=="IFTK"){
			condition_statement();
		}
		else if(curtok=="WHILETK"||curtok=="FORTK"){
			loop_statement();
		}
		else if(curtok=="LBRACE"){
			if(seek(1)=="RBRACE"){
				//fout<< "<语句列>" << endl;
				nexttoken();
			}
			else{
				nexttoken();
				statement_column();
				nexttoken();
			}
		}
		else if(curtok=="IDENFR"){
			if(!symbol_table.top()->count(val[curindex-1])&&\
			!has_retval.count(val[curindex-1])&&\
			!global_symbol_table->count(val[curindex-1])){
				c_error();
			}
			if(has_retval[val[curindex-1]]){
				funcall();
				if(seek(1)=="SEMICN"){
					nexttoken();
				}
				else{
					k_error();
				}
			}
			else if(seek(1)=="ASSIGN"||seek(1)=="LBRACK"){
				assign_statement();
				if(seek(1)=="SEMICN"){
					nexttoken();
				}
				else{
					k_error();
				}
			}
			else if(!has_retval[val[curindex-1]]){
				voidfuncall();
				if(seek(1)=="SEMICN"){
					nexttoken();
				}
				else{
					k_error();
				}
			}
			
		}
		else if(curtok=="SCANFTK"){
			read_statement();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
		}
		else if(curtok=="PRINTFTK"){
			write_statement();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
		}
		else if(curtok=="RETURNTK"){
			return_statement();
			if(seek(1)=="SEMICN"){
				nexttoken();
			}
			else{
				k_error();
			}
		}
		else if(curtok=="SWITCHTK"){
			case_statement();
		}
		else if(curtok=="SEMICN"){
			//nothing
		}
		//fout<< "<语句>" << endl;
	}

	//语句列
	void statement_column(){
		if (curtok!= "RBRACE") {
			while (seek(1)!= "RBRACE"&&curindex<toknum||curtok=="SEMICN") {
				statement();
				if (seek(1)!= "RBRACE"&&curindex<toknum) {
					nexttoken();
				}
				else if(seek(1)== "RBRACE"){
					break;
				}

			}
		}
		//fout<< "<语句列>" << endl;
	}

	//复合语句
	void compound_statement(){
		if(curtok=="CONSTTK"){
			constant_desc();
			nexttoken();
		}
		if(curtok=="CHARTK"||curtok=="INTTK"){
			variable_desc();
			nexttoken();
		}
		
		statement_column();
		//fout<< "<复合语句>" << endl;
	}

	//有返回值函数定义
	void func_def(){
		is_def_func=1;
		declaration_header();
		vector<string> tempvec;
		parameters.emplace(val[curindex-1],tempvec);
		nexttoken();
		symbol_table.push(new unordered_map<string,attributes>());
		if (seek(1)!="RPARENT"){
			nexttoken();
			parameters_table();
			nexttoken();
		}else{
			//fout<< "<参数表>" << endl;
			nexttoken();
		}
		
		nexttoken();
		nexttoken();
		compound_statement();
		symbol_table.pop();
		nexttoken();
		if(is_def_func==1){
			h_error();
		}
		is_def_func=0;
		def_func_type="";
		//fout<< "<有返回值函数定义>" << endl;
	}

	//无返回值函数定义
	void void_func_def(){
		is_def_func=2;
		nexttoken();
		if(symbol_table.top()->count(val[curindex-1])){
			b_error();
		}
		else{
			attributes att;
			att.type="VOIDTK";
			symbol_table.top()->emplace(val[curindex-1],att);
			has_retval.insert(pair<string, bool>(val[curindex-1], false));
		}
		vector<string> tempvec;
		parameters.emplace(val[curindex-1],tempvec);
		nexttoken();
		symbol_table.push(new unordered_map<string,attributes>());
		if (seek(1)!="RPARENT"){
			nexttoken();
			parameters_table();
			nexttoken();
		}else{
			//fout<< "<参数表>" << endl;
			nexttoken();
		}
		nexttoken();
		nexttoken();
		compound_statement();
		symbol_table.pop();
		nexttoken();
		is_def_func=0;
		//fout<< "<无返回值函数定义>" << endl;
	}
	//main
	void mainfun(){
		is_def_func=2;
		nexttoken();
		nexttoken();
		nexttoken();
		nexttoken();
		nexttoken();
		symbol_table.push(new unordered_map<string,attributes>());
		compound_statement();
		nexttoken();
		symbol_table.pop();
		is_def_func=0;
		//fout<< "<主函数>" << endl;
	}
	void program(){
		symbol_table.push(new unordered_map<string,attributes>());
		global_symbol_table=symbol_table.top();
		nexttoken();
		if(curtok=="CONSTTK"){
			constant_desc();
			nexttoken();
		}
		if((curtok=="INTTK"||curtok=="CHARTK")&&(seek(2)=="SEMICN"||\
		seek(2)=="COMMA"||seek(2)=="ASSIGN"||seek(2)=="LBRACK")){
			variable_desc();
			nexttoken();
		}
		//函数定义
		while(((curtok=="INTTK"||curtok=="CHARTK")&&seek(2)=="LPARENT")\
		||(curtok=="VOIDTK"&&seek(2)=="LPARENT"&&seek(1)!="MAINTK")){
			if((curtok=="INTTK"||curtok=="CHARTK")&&seek(2)=="LPARENT"){
				
				func_def();
				nexttoken();
			}
			else{
				void_func_def();
				nexttoken();
			}
		}
		mainfun();
		//fout<< "<程序>" << endl;
	}
	//语法分析
	void start(){
		toknum=p;
		program();
	}
};
int main(){
	try{
		lexical_analysis();
		yufafenxi yffx;
		yffx.start();
	}
	catch(const char * msg){
		cerr <<msg<<endl;
	}
	return 0;
}
