%locations
%error-verbose
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "semantic.h"

	#define YYSTYPE Node* //不加这个在添加 %locations后YYSTYPE类型会变化

	Node* create_tree(Node* s);
	Node* add_Node1(Node* s1, char* str, int type);
    Node* add_Node2(Node* s1, Node* s2, char* str, int type);
	Node* add_Node3(Node* s1, Node* s2, Node* s3, char* str, int type);
	Node* add_Node4(Node* s1, Node* s2, Node* s3, Node* s4, char* str, int type);
	Node* add_Node5(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, char* str, int type);
	Node* add_Node7(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, Node* s6, Node* s7, char* str, int type);
	void traversal(Node* root, int n);
	void sem_traversal(Node* root);

	extern sem_helper sem_func_table[FT_SIZE];
	extern int ano_num;

	int synright = 1;//标志语法分析中是否有错误产生, 错误恢复也算作有错误，用于此时不输出语法分析树
	Node* root;

%}

%token INT 
%token FLOAT 
%token ID
%token PLUS MINUS STAR DIV
%token SEMI COMMA 
%token ASSIGNOP
%token RELOP
%token AND OR DOT NOT
%token TYPE
%token LP RP LB RB LC RC
%token STRUCT RETURN IF ELSE WHILE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGNOP
%left AND OR
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT 
%left LP RP LB RB DOT

%%

Program : ExtDefList {
		root = $$ = create_tree($1);
		}
		;
ExtDefList : /* empty */ {$$ = NULL;}
		   | ExtDef ExtDefList {$$ = add_Node2($1, $2, "ExtDefList", 1);}
		   ;
ExtDef : Specifier ExtDecList SEMI {$$ = add_Node3($1, $2, $3, "ExtDef", 2);}
	   | Specifier SEMI {$$ = add_Node2($1, $2, "ExtDef", 3);}
	   | Specifier FunDec CompSt {$$ = add_Node3($1, $2, $3, "ExtDef", 4);}
	   | Specifier error SEMI {}
	   | Specifier error {}
	   | Specifier ExtDecList error {}
	   ;
ExtDecList : VarDec {$$ = add_Node1($1, "ExtDecList", 5);}
		   | VarDec COMMA ExtDecList {$$ = add_Node3($1, $2, $3, "ExtDecList", 6);}
		   ;


Specifier : TYPE {$$ = add_Node1($1, "Specifier", 7);}
		  | StructSpecifier {$$ = add_Node1($1, "Specifier", 8);}
		  ;
StructSpecifier : STRUCT OptTag LC DefList RC {$$ = add_Node5($1, $2, $3, $4, $5, "StructSpecifier", 9);}
				| STRUCT Tag {$$ = add_Node2($1, $2, "StructSpecifier", 0xa);}
				;
OptTag : /* empty */ {$$ = NULL;}
	   | ID {$$ = add_Node1($1, "OptTag", 0xb);}
	   ;
Tag : ID {$$ = add_Node1($1, "Tag", 0xc);}
	;


VarDec : ID {$$ = add_Node1($1, "VarDec", 0xd);}
	   | VarDec LB INT RB {$$ = add_Node4($1, $2, $3, $4, "VarDec", 0xe);}
	   ;
FunDec : ID LP VarList RP {$$ = add_Node4($1, $2, $3, $4, "FunDec", 0xf);}
	   | ID LP RP {$$ = add_Node3($1, $2, $3, "FunDec", 0x10);}
	   ;
VarList : ParamDec COMMA VarList {$$ = add_Node3($1, $2, $3, "VarList", 0x11);}
		| ParamDec {$$ = add_Node1($1, "VarList", 0x12);}
		;
ParamDec : Specifier VarDec {$$ = add_Node2($1, $2, "ParamDec", 0x13);}
		 ;


CompSt : LC DefList StmtList RC {$$ = add_Node4($1, $2, $3, $4, "CompSt", 0x14);}
	   ;
StmtList : /* empty */ {$$ = NULL;}
		 | Stmt StmtList {$$ = add_Node2($1, $2, "StmtList", 0x15);}
		 ;
Stmt : Exp SEMI {$$ = add_Node2($1, $2, "Stmt", 0x16);}
	 | CompSt {$$ = add_Node1($1, "Stmt", 0x17);}
	 | RETURN Exp SEMI {$$ = add_Node3($1, $2, $3, "Stmt", 0x18);}
	 | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$ = add_Node5($1, $2, $3, $4, $5, "Stmt", 0x19);}
	 | IF LP Exp RP Stmt ELSE Stmt {$$ = add_Node7($1, $2, $3, $4, $5, $6, $7, "Stmt", 0x1a);}
	 | WHILE LP Exp RP Stmt {$$ = add_Node5($1, $2, $3, $4, $5, "Stmt", 0x1b);}
	 | Exp error {}
	 | error SEMI {}
	 | error ELSE {}
	 | error IF {}
	 | error WHILE {}
	 | error RETURN {}
	 ;

DefList : /* empty */ {$$ = NULL;}
		| Def DefList {$$ = add_Node2($1, $2, "DefList", 0x1c);}
		;
Def : Specifier DecList SEMI {$$ = add_Node3($1, $2, $3, "Def", 0x1d);}
	| Specifier error SEMI {}
	;
DecList : Dec {$$ = add_Node1($1, "DecList", 0x1e);}
		| Dec COMMA DecList {$$ = add_Node3($1, $2, $3, "DecList", 0x1f);}
		| Dec error DecList {}
		;
Dec : VarDec {$$ = add_Node1($1, "Dec", 0x20);}
	| VarDec ASSIGNOP Exp {$$ = add_Node3($1, $2, $3, "Dec", 0x21);}


Exp : Exp ASSIGNOP Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x22);}
	| Exp AND Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x23);}
	| Exp OR Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x24);}
	| Exp RELOP Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x25);}
	| Exp PLUS Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x26);}
	| Exp MINUS Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x27);}
	| Exp STAR Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x28);}
	| Exp DIV Exp {$$ = add_Node3($1, $2, $3, "Exp", 0x29);}
	| LP Exp RP {$$ = add_Node3($1, $2, $3, "Exp", 0x2a);}
	| MINUS Exp {$$ = add_Node2($1, $2, "Exp", 0x2b);}
	| NOT Exp {$$ = add_Node2($1, $2, "Exp", 0x2c);}
	| ID LP Args RP {$$ = add_Node4($1, $2, $3, $4, "Exp", 0x2d);}
	| ID LP RP {$$ = add_Node3($1, $2, $3, "Exp", 0x2e);}
	| Exp LB Exp RB {$$ = add_Node4($1, $2, $3, $4, "Exp", 0x2f);}
	| Exp DOT ID {$$ = add_Node3($1, $2, $3, "Exp", 0x30);}
	| ID {$$ = add_Node1($1, "Exp", 0x31);}
	| INT {$$ = add_Node1($1, "Exp", 0x32);}
	| FLOAT {$$ = add_Node1($1, "Exp", 0x33);}
	| Exp LB Exp error {synright = 0;}
	| error RP {}
	;
Args : Exp COMMA Args {$$ = add_Node3($1, $2, $3, "Args", 0x34);}
	 | Exp {$$ = add_Node1($1, "Args", 0x35);}
	 ;

%%

#include "lex.yy.c"

Node* create_tree(Node* s) {
	Node* p = (Node *)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, "Program");
	p->leftmost = s;
	p->right = NULL;
	if(s) 
		p->lineno = s->lineno;
	else 
		p->lineno = 1; //empty program

	if(s)
		s->right = NULL;

	p->pdt_type = 0;
	return p;
}

Node* add_Node1(Node* s1, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = NULL;

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node2(Node* s1, Node* s2, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	if(s2 != NULL) {
		s1->right = s2;
		s2->right = NULL;
	}
	else {
		s1->right = NULL;
	}
	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node3(Node* s1, Node* s2, Node* s3, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;

	if(s3 != NULL) {
		s2->right = s3;
		s3->right = NULL;
	}
	else 
		s2->right = NULL;

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node4(Node* s1, Node* s2, Node* s3, Node* s4, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;
	if(s2 && s3) { //s2, s3可能为空串
		s2->right = s3;
		s3->right = s4;
		s4->right = NULL;
	}
	else if(s2) {
		s1->right = s2;
		s2->right = s4;
	}
	else if(s3) {
		s1->right = s3;
		s3->right = s4;
	}

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node5(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;

	if(s2 != NULL)
		s2->right = s3;
	else {
		s1->right = s3;

		/* 专门用来处理匿名结构体，这里给它手动设置名字，把名字首先赋给LC */
		/* 每次要开辟新的缓冲区，否则后面的匿名结构体名字会把前面的覆盖掉 */
		char* p = (void*)malloc(4);
		int i;
		for(i = 0; i < 4; i++)
			p[i] = '\0';
		sprintf(p, "%d", ++ano_num);
		s3->attr.blg_name = p;
	}

	s3->right = s4;

	if(s5 != NULL && s4 != NULL) {
		s4->right = s5;
		s5->right = NULL;
	}
	else if(s4 != NULL)
		s4->right = NULL;
	else if(s5 != NULL) 
		s3->right = s5;

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node7(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, Node* s6, Node* s7, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;
	s2->right = s3;
	s3->right = s4;
	s4->right = s5;
	s5->right = s6;

	if(s7 != NULL) {
		s6->right = s7;
		s7->right = NULL;
	}
	else
		s6->right = NULL;
	
	root = p;
	p->pdt_type = type;

	return p;
}

void traversal(Node *root, int n) {
	int i;
	for(i = 0; i < n; i++)
		printf("  ");
	printf("%s", root->name);
	if(root->flag) {
		if(strcmp(root->name, "ID") == 0) 
			printf(": %s\n", root->id);
		else if(strcmp(root->name, "TYPE") == 0)
			printf(": %s\n", root->type);
		else if(strcmp(root->name, "INT") == 0)
			printf(": %d\n", root->d);
		else if(strcmp(root->name, "FLOAT") == 0)
			printf(": %f\n", root->f);
		else
			printf("\n");
	}
	else
		printf(" (%d)\n", root->lineno);
	Node* p = root->leftmost;
	while(p) {
		traversal(p, n+1);
		p = p->right;
	}
}

void sem_traversal(Node* root) {

	Node* p = root->leftmost;
	Node* last = root;

	while(p) {

		/* 当底层继承属性为空时，顶层才给底层传递继承属性 */
		if(!p->attr.blg_name)
			p->attr.blg_name = last->attr.blg_name;
		if(!p->inh)
			p->inh = last->inh;

		sem_traversal(p);
		last = p;
		assert(p);
		p = p->right;
	}

	assert(root);
	//printf("%d\n", root->pdt_type);
	sem_func_table[root->pdt_type](root);

}

yyerror(char* msg) {
	synright = 0;
	int lineno = yylineno;
	if(token_in_line == 1 && yylineno != root->lineno)
		lineno = root->lineno;
	fprintf(stderr, "Error type B at Line %d: %s \n", lineno, msg);
}
