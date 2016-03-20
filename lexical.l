%option yylineno

%{
	#include "syntax.tab.h"
	#include <stdlib.h>

	unsigned myotoi();//要声明，否则conflicting types
	unsigned myhtoi();
	void error_oct();
	void error_hex();
	void error_handle();
	float myetof();

	int yycolumn = 1;
	int lexright = 1;//标志词法分析是否成功，失败的话不输出语法分析树
	extern struct Node* root;
	int token_in_line = 0;

	/* 下面的宏定义每识别出一个词法单元就会调用，包括位置的追踪以及语法树叶节点的创建 */

	#define YY_USER_ACTION\
	yylloc.first_line = yylloc.last_line = yylineno;\
	yylloc.first_column = yycolumn;\
	yylloc.last_column = yycolumn + yyleng - 1;\
	yycolumn += yyleng;\
	yylval = (void*)malloc(sizeof(Node));\
	yylval->flag = 1;\
	yylval->lineno = yylineno;\
	yylval->leftmost = NULL;\
	yylval->right = NULL;\
	yylval->inh = NULL;\
	yylval->ic = NULL;\
	yylval->place = NULL;\
	yylval->truelabel = NULL;\
	yylval->falselabel = NULL;\
	yylval->arg_list = NULL;\
	root = yylval;\
	token_in_line++;

%}

LETTER [_a-zA-Z]
DIGIT [0-9]
DIGITO [0-7]
DIGITH [0-9A-Fa-f]
RELOP_ ">"|"<"|">="|"<="|"=="|"!="
TYPE_ "int"|"float"
ID_ {LETTER}({LETTER}|{DIGIT})*
INTD "0"|[1-9]{DIGIT}*
INTO "0"("0"|[1-7]{DIGITO}*)
INTH "0"[xX]("0"|[1-9A-Fa-f]{DIGITH}*)
INTOERR "0"{DIGIT}+
INTHERR "0"[xX][0-9A-Za-z]*
FLOATN {INTD}\.{DIGIT}+
FLOATE {FLOATN}[eE][+-]?{INTD}

%%
";" {strcpy(yylval->name, "SEMI");
	 return SEMI;
	}
"," {strcpy(yylval->name, "COMMA");
	 return COMMA;
	}
"=" {strcpy(yylval->name, "ASSIGNOP");
	 return ASSIGNOP;
	}
{RELOP_} {strcpy(yylval->name, "RELOP");
		  memset(yylval->relop, 0, 3);
		  strcpy(yylval->relop, yytext);
		  //printf("%s\n", yylval->relop);
		  return RELOP;
		 }
"+" {strcpy(yylval->name, "PLUS");
	 return PLUS;
	}
"-" {strcpy(yylval->name, "MINUS");
	 return MINUS;
	}
"*" {strcpy(yylval->name, "STAR");
	 return STAR;
	}
"/" {strcpy(yylval->name, "DIV");
	 return DIV;
	}
"&&" {strcpy(yylval->name, "AND");
	  return AND;
	 }
"||" {strcpy(yylval->name, "OR");
	  return OR;
	 }
"." {strcpy(yylval->name, "DOT");
	 return DOT;
	}
"!" {strcpy(yylval->name, "NOT");
	 return NOT;
	}
{TYPE_} {strcpy(yylval->name, "TYPE");
		 strcpy(yylval->type, yytext);
		 return TYPE;
		}
"(" {strcpy(yylval->name, "LP");
	 yylval->attr.type.kind = FUNC; 
	 //yylval->inh = &yylval->attr.type; 这么继承是错的 从函数名那里继承就好 这样继承不到返回值和参数等信息
	 return LP;
	}
")" {strcpy(yylval->name, "RP");
	 return RP;
	}
"[" {strcpy(yylval->name, "LB");
	 return LB;
	}
"]" {strcpy(yylval->name, "RB");
	 return RB;
	}
"{" {strcpy(yylval->name, "LC");
	 return LC;
	}
"}" {strcpy(yylval->name, "RC");
	 return RC;
	}
"struct" {strcpy(yylval->name, "STRUCT");
		  yylval->attr.type.kind = STRUCTURE;
		  yylval->attr.type.structure = NULL;
		  yylval->inh = &yylval->attr.type; //继承属性的关键用武之地
		  return STRUCT;
		 }
"return" {strcpy(yylval->name, "RETURN");
		  return RETURN;
		 }
"if" {strcpy(yylval->name, "IF");
	  return IF;
	 }
"else" {strcpy(yylval->name, "ELSE");
		return ELSE;
	   }
"while" {strcpy(yylval->name, "WHILE");
		 return WHILE;
		}
{INTD} {strcpy(yylval->name, "INT");
		yylval->d = atoi(yytext);
		yylval->attr.type.kind = BASIC;
		yylval->attr.type.basic = 0;
		yylval->inh = &yylval->attr.type;
		return INT;
	   }
{INTO} {strcpy(yylval->name, "INT");
		yylval->d = myotoi();
		return INT; 
	   }
{INTH} {strcpy(yylval->name, "INT");
		yylval->d = myhtoi();
		return INT;
	   }
{INTOERR} {error_oct(); return INT;}
{INTHERR} {error_hex(); return INT;}
{FLOATN} {strcpy(yylval->name, "FLOAT");
		  yylval->f = atof(yytext);
		  yylval->attr.type.kind = BASIC;
		  yylval->attr.type.basic = 1;
		  yylval->inh = &yylval->attr.type;
		  return FLOAT;
		 }
{FLOATE} {strcpy(yylval->name, "FLOAT");
		  yylval->f = myetof();
		  return FLOAT;
		 }
{ID_} {strcpy(yylval->name, "ID");
	   strcpy(yylval->id, yytext);
	   return ID;
	  }
" " {}
"\t" {}
"\n" {yycolumn = 1; token_in_line = 0;}
. {error_handle();}

%%

/*
int main(int argc, char** argv) {
	if(argc > 1) {
		if(!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	yylex();
	printf("\nDone!\n");
	return 0;
}
*/

unsigned myotoi() {
	unsigned r = (unsigned)0;
	int i;
	for(i = 1; yytext[i] != '\0'; i++) {
		r = r * 8 + (yytext[i] - '0');
	}
	return r;
}

unsigned myhtoi() {
	unsigned r = (unsigned)0;
	int i;
	for(i = 2; yytext[i] != '\0'; i++) {
		if(yytext[i] >= 'A' && yytext[i] <= 'F')
		  yytext[i] = yytext[i] - 'A' + 'a';
		if(yytext[i] >= 'a' && yytext[i] <= 'f')
		  r = r * 16 + (yytext[i]- 'a' + 10);
		else
		  r = r * 16 + (yytext[i] - '0');
	}
	return r;
}

float myetof() {
	int i;
	char basestr[33] = "";
	for(i = 0; (yytext[i] != 'e' && \
					yytext[i] != 'E'); i++)
	  basestr[i] = yytext[i];
	float factor1 = atof(basestr);

	i++;
	int flag = 1; //flag = 1 表示是10的正幂次
	int start = i;
	if(yytext[i] == '-') {
		flag = 0;
		start = i + 1;
	}
	else if(yytext[i] == '+') {
		start = i + 1;
	}

	char expstr[33] = "";
	for(i = start; yytext[i] != '\0'; i++)
	  expstr[i-start] = yytext[i];
	int exp = atoi(expstr);

	float factor2 = 1;
	if(flag) {
		for(i = 0; i < exp; i++)
		  factor2 *= 10;
	}
	else {
		for(i = 0; i < exp; i++)
		  factor2 /= 10;
	}

	return factor1 * factor2;
}

void error_oct() {
	lexright = 0;
	printf("Error type A at Line %d: Illegal octal number '%s'\n", yylineno, yytext);
}

void error_hex() {
	lexright = 0;
	printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n", yylineno, yytext);
}

void error_handle() {
	lexright = 0;
	printf("Error type A at Line %d: Mysterious character \"%c\"\n", yylineno, yytext[0]);
}

