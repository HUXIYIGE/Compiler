#include <stdlib.h>
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<map>
#include <fstream>
using namespace std; 
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
				throw "illegal input";
			}
			break;
		}
	}
	
	fclose(f);
	ofstream fout("output.txt");
	for(int i=0;i<p;i++){
		fout<<token[i]<<" "<<val[i]<<endl;
		cout<<token[i]<<" "<<val[i]<<" "<<row[i]<<" "<<col[i]<<endl;
	}
}
int main(){
	try{
		lexical_analysis();
	}
	catch(const char * msg){
		cerr <<msg<<endl;
	}
	return 0;
}
