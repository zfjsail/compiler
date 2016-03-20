#include "lib.h"
#include "debug.h"
#include <stdio.h>
#include <assert.h>

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_ {
	enum { BASIC, ARRAY, STRUCTURE, FUNC, ANY } kind; // ANY匹配任何类型
	union {
		int basic; //0 is int; 1 is float
		struct { Type elem; int size; int width; int length; } array;
		FieldList structure;
		struct { Type ret; int pnum; FieldList para; } func;
	} ;
};

struct FieldList_ {
	char* name;
	Type type;
	FieldList tail;
};

typedef struct Operand_* Operand;

typedef struct HT_Node {
	char* name;
	struct Type_ type;
	char* blg_name; // the name of structure it belongs to 
	struct HT_Node* next;
	Operand var; //符号表中对应的中间代码的局部变量
} HT_Node;

struct Operand_ {
	enum { VARIABLE, TMP_VAR, CONSTANT, ADDRESS, LABEL, POINTER, POINTER2ADDR } kind;
	union {
		int var_no; //局部变量标号
		int tmp_no; //临时变量标号
		int value; //常数数值
		struct {
			int lbl_no; //标号编号
			int ref; //该标号被引用的次数
		};	
		Operand addr;
		Operand op;
		Operand p2a;
	};
	unsigned op_desc; //变量描述符
	int reg_idx; //to be discarded
	int off; //stk off
	bool save;
};

typedef struct op_node_ op_node_;
typedef op_node_* op_node;
typedef op_node_* reg_desc;
typedef op_node_* act_node;
struct op_node_ {
	Operand op;
	op_node next;
};

typedef struct InterCode_* InterCode;

struct InterCode_ {
	enum { ASSIGN, ASSIGN3, ADD, SUB, MUL, READ, WRITE, FUNCTION, RETURN_, IF_OP, GOTO, LABEL_, PARAM, CALL, ARG, DEC } kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand left, right1, right2; char op; } assign3;
		struct { Operand result, op1, op2; } binop;
		struct { Operand dest; } read;
		struct { Operand dest; } write;
		struct { char* name; } func;
		struct { Operand val; } ret;
		struct { Operand t1; char* op; Operand t2; Operand label_true; } if_op;
		struct { Operand label; } go_to;
		struct { Operand label; } lbl;
		struct { Operand para; } param;
		struct { Operand place; char* name; } call;
		struct { Operand arg; } arg;
		struct { Operand v; int len; } dec;
	};
};

typedef struct InterCodes_* InterCodes;
struct InterCodes_ {
	struct InterCode_ code;
	InterCodes next;
	bool isTail; //是否是基本块的tail
	act_node active_list; //本句之后那点的活跃变量列表
};

typedef struct Arg_Node_* Arg_Node;
struct Arg_Node_ {
	Operand arg;
	Arg_Node next;
};

typedef struct Node {
	int flag; //表示浮点数指数部分是正or负
	char name[33];
	int lineno;
	union {
		char id[33];
		char type[6];
		int d;
		float f;
		char relop[3];
	};
	struct Node* leftmost;
	struct Node* right;
	int pdt_type; //产生式编号（类型）
	HT_Node attr; //综合属性
	Type inh; //继承属性
	InterCodes ic; //中间代码（序列）
	Operand place; //针对表达式，指代存放的临时位置
	Operand truelabel;
	Operand falselabel;
	Arg_Node arg_list;
} Node;
