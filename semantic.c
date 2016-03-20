#include "semantic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* 函数指针表：每个产生式对应一个元素 */
sem_helper sem_func_table[FT_SIZE] = {
/* 0x00 */	inv, inv, inv, inv,
/* 0x04 */	inv, ExtDecList, ExtDecList, Specifier1,
/* 0x08 */	Specifier2, StructSpecifier1, StructSpecifier2, OptTag,
/* 0x0c */	Tag, VarDec1, VarDec2, FunDec1,
/* 0x10 */	FunDec2, VarList1, VarList2, ParamDec,
/* 0x14 */	inv, inv, inv, inv,
/* 0x18 */	Stmt1, inv, inv, inv,
/* 0x1c */	DefList, Def, DecList1, DecList2,
/* 0x20 */	Dec, Dec, Exp1, Exp3,
/* 0x24 */	Exp3, Exp3, Exp3, Exp3,
/* 0x28 */	Exp3, Exp3, Exp4, Exp5,
/* 0x2c */	Exp6, Exp7, Exp8, Exp9,
/* 0x30 */	Exp10, Exp11, Exp12, Exp12,
/* 0x34 */	Args, Args, inv, inv
};


/* 哈希表（符号表），这里只用了一个符号表 */
HT_Node* HT[HT_SIZE];

void init_HT() {
	int i;
	for(i = 0; i < HT_SIZE; i++)
	  HT[i] = NULL;
}

int hash_pjw(char* name) {
	unsigned val = 0, i;
	for(; *name; ++name) {
		val = (val << 2) + *name;
		if(i = val & ~HT_SIZE)
		  val = (val ^ (i >> 12)) & HT_SIZE;
	}
	return (int)val;
}

/* 查符号表，若不在符号表中，返回空 */
HT_Node* seekHT(char* name) {
	int loc = hash_pjw(name);
	HT_Node* ph = HT[loc];
	while(ph) {
		if(strcmp(ph->name, name) == 0) return ph;
		else ph = ph->next;
	}
	return ph;
}

/* 检查两个类型是否相同或等价 */
int tpcheck(Type t1, Type t2) {
	if(t1->kind == ANY) return 1;
	if(t2->kind == ANY) return 1;
	if(t1->kind != t2->kind) return 0;
	else {
		switch(t1->kind) {
			case BASIC: {
							if(t1->basic == t2->basic) return 1;
							else return 0; break;
						}
			case ARRAY: {
							Type p, q;
							p = t1->array.elem;
							q = t2->array.elem;
							return tpcheck(p, q);
							break;
						}
			case STRUCTURE: {
								FieldList pf1 = t1->structure, pf2 = t2->structure;
								while(pf1 && pf2) {
									if(!tpcheck(pf1->type, pf2->type)) return 0;
									pf1 = pf1->tail;
									pf2 = pf2->tail;
								}
								if(!pf1 && !pf2) return 1;
								else return 0;
								break;
							}
			default: return 1;
		}
	}
}

void printerr(int type, Node* nd) {
	printf("Error type %d at Line %d: ", type, nd->lineno);
	switch(type) {
		case 1: printf("Undefined variable \"%s\"\n", nd->id); break;
		case 2: printf("Undefined function \"%s\"\n", nd->id); break;
		case 3: printf("Redefined variable \"%s\"\n", nd->attr.name); break;
		case 4: printf("Redefined function \"%s\"\n", nd->id); break;
		case 5: printf("Type mismatched for assignment.\n"); break;
		case 6: printf("The left-hand side of an assignment must be a variable.\n"); break;
		case 7: printf("Type mismathced for operands.\n"); break;
		case 8: printf("Type mismatched for return.\n"); break;
		case 9: printf("Function arguments are not matched.\n"); break;
		case 10: printf("Exp is not an array.\n"); break;
		case 11: printf("\"%s\" is not a function.\n", nd->id); break;
		case 12: printf("Array index is not an integer.\n"); break;
		case 13: printf("Illegal use of \".\".\n"); break;
		case 14: printf("None-existent field \"%s\".\n", nd->id); break;
		case 15: printf("Invalid definition in structure.\n"); break;
		case 16: printf("Duplicated name \"%s\".\n", nd->attr.name); break;
		case 17: printf("Undefined structure \"%s\".\n", nd->attr.name); break;
		default: printf("\n");
	}
}
	  

void ExtDecList(Node* nd) { //0x5 & 0x6
	Log("ExtDecList");
	Node* p = nd->leftmost;
	char* name = p->attr.name;
	nd->attr = p->attr;
	if(!seekHT(name)) {
		int loc = hash_pjw(name);
		HT_Node* ph = (void*)malloc(sizeof(HT_Node));
		ph->var = NULL;
		ph->next = HT[loc];
		ph->name = name;
		ph->type = nd->attr.type;
		HT[loc] = ph;
	}
	else {
		printerr(3, p);
	}
}

void Specifier1(Node* nd) { //0x7
	Log("Specifier1");
	Node* p = nd->leftmost;
	nd->attr.type.kind = BASIC;
	if(strcmp(p->type, "int") == 0) 
		nd->attr.type.basic = 0;
	else
	    nd->attr.type.basic = 1;
	nd->inh = &nd->attr.type;
}

void Specifier2(Node* nd) { //0x8
	Log("Specifier2");
	Node* p = nd->leftmost;
	char* blg = nd->attr.blg_name;
	nd->attr = p->attr;
	nd->attr.blg_name = blg; //这个不变, 小心被覆盖
	nd->inh = &nd->attr.type; //这里要设置继承属性，之后可以被传递
}

void StructSpecifier1(Node* nd) { //0x9
	Log("StructSpecifier1");
	Node* p = nd->leftmost;
	Node* q;
	Node* r = p->right;
	if(strcmp(r->name, "OptTag") == 0) {
		q = p->right->right->right;
		char* name = r->attr.name;
		r->attr = q->attr; //小心name域被覆盖后成空指针，原来的标识符还是要保留的
		r->attr.name = name;
		nd->attr.type = q->attr.type;
		nd->attr.name = name;
		if(!seekHT(name)) {
			int loc = hash_pjw(name);
			HT_Node* ph = (void*)malloc(sizeof(HT_Node));
			ph->var = NULL;
			ph->next = HT[loc];
			ph->name = name;
			ph->type = r->attr.type;
			HT[loc] = ph;
		}
		else {
			printerr(16, r);
		}
	}
	else {
	    q = p->right->right;
		nd->attr = q->attr;
	}
}

void StructSpecifier2(Node* nd) { //0xa
	Log("StructSpecifier2");
	Node* p = nd->leftmost->right;
	nd->attr = p->attr;
	HT_Node* ph = seekHT(p->attr.name);
	if(ph) { //记得传递
		if(ph->type.kind != STRUCTURE)
		  printerr(17, p);
		nd->attr.name = ph->name;
		nd->attr.type = ph->type;
	}
	else {
		printerr(17, p);
	}
}

void OptTag(Node* nd) { //0xb
	Log("OptTag");
	Node* p = nd->leftmost;
	nd->attr.type = *(p->inh);
	nd->attr.name = p->id;
	nd->attr.blg_name = p->id; //这里设置继承属性，以后可以传递
}

void Tag(Node* nd) { //0xc
	Log("Tag");
	Node* p = nd->leftmost;
	nd->attr.type = *(p->inh);
	nd->attr.name = p->id;
}

void VarDec1(Node* nd){ //0xd
	Log("VarDec1");
	Node* p = nd->leftmost;
	nd->attr.type = *(p->inh);
	nd->attr.name = p->id;
}

void VarDec2(Node* nd) { //0xe
	Log("VarDec2");
	Node* p = nd->leftmost;
	nd->attr.name = p->attr.name;
	nd->attr.type.kind = ARRAY;
	nd->attr.type.array.elem = &p->attr.type;
	Node* q = p->right->right;
	nd->attr.type.array.size = q->d;
}

void FunDec1(Node* nd) { //0xf
	Log("FunDec1");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	char* name = p->id;
	nd->attr.name = p->id;
	nd->attr.type.kind = FUNC;
	nd->attr.type.func.para = q->attr.type.func.para;
	int cnt = 0;
	FieldList pn = nd->attr.type.func.para;
	while(pn) {
		cnt++; //参数数量
		pn = pn->tail;
	}
	nd->attr.type.func.pnum = cnt;
	nd->attr.type.func.ret = nd->inh;
	nd->inh = &nd->attr.type; //传给return语句
	HT_Node* ph = seekHT(name);
	if(!ph) {
		int loc = hash_pjw(name);
		HT_Node* ph = (void*)malloc(sizeof(HT_Node));
		ph->var = NULL;
		ph->next = HT[loc];
		ph->name = name;
		ph->type = nd->attr.type;
		ph->blg_name = NULL;
		HT[loc] = ph;
	}
	else {
		printerr(4, p);
	}
}

void FunDec2(Node* nd) { //0x10
	Log("FunDec2");
	Node* p = nd->leftmost;
	char* name = p->id;
	nd->attr.name = p->id;
	nd->attr.type.kind = FUNC;
	nd->attr.type.func.pnum = 0;
	nd->attr.type.func.para = NULL;
	nd->attr.type.func.ret = nd->inh;
	nd->inh = &nd->attr.type;
	HT_Node* ph = seekHT(name);
	if(!ph) {
		int loc = hash_pjw(name);
		HT_Node* ph = (void*)malloc(sizeof(HT_Node));
		ph->var = NULL;
		ph->next = HT[loc];
		ph->name = name;
		ph->type = nd->attr.type;
		ph->blg_name = NULL;
		HT[loc] = ph;
	}
	else {
		printerr(4, p);
	}
}

void VarList1(Node* nd) { //0x11
	Log("VarList1");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	FieldList fl = (void*)malloc(sizeof(struct FieldList_));
	fl->name = p->attr.name;
	fl->type = &p->attr.type;
	fl->tail = q->attr.type.func.para;
	nd->attr.type.func.para = fl;
	nd->attr.type.kind = FUNC;
}

void VarList2(Node* nd) { //0x12
	Log("VarList2");
	Node* p = nd->leftmost;
	FieldList fl = (void*)malloc(sizeof(struct FieldList_));
	fl->name = p->attr.name;
	fl->type = &p->attr.type;
	fl->tail = NULL;
	nd->attr.type.func.para = fl;
	nd->attr.type.kind = FUNC;
}

void ParamDec(Node* nd) { //0x13
	Log("ParamDec");
	Node* p = nd->leftmost->right;
	nd->attr = p->attr;
	char* name = nd->attr.name;
	if(!seekHT(name)) {
		int loc = hash_pjw(name);
		HT_Node* ph = (void*)malloc(sizeof(HT_Node));
		ph->var = NULL;
		ph->next = HT[loc];
		ph->name = name;
		ph->type = nd->attr.type;
		HT[loc] = ph;
	}
	else {
		printerr(3, p);
	}
}

void Stmt1(Node* nd) { //0x18
	Log("Stmt1");
	Node* p = nd->leftmost->right;
	Type tp = &p->attr.type;
	int match = tpcheck(nd->inh->func.ret, tp);
	if(!match)
	  printerr(8, p);
}

void DefList(Node* nd) { //0x1c
	Log("DefList");
	Node* p = nd->leftmost;
	Node* q = p->right;
	nd->attr = p->attr;
	if(nd->inh->kind == STRUCTURE) {
		if(q) {
			FieldList r = nd->attr.type.structure;
			FieldList last;
			while(r) {
				last = r;
				r = r->tail;
			}
			last->tail = q->attr.type.structure;
		}
	}
}

void Def(Node* nd) { //0x1d
	Log("Def");
	Node* p = nd->leftmost;
	Node* q = p->right;
	if(nd->inh->kind == STRUCTURE) {
		nd->attr.type = *(nd->inh);
		nd->attr.type.structure = q->attr.type.structure;
	}
}

void DecList1(Node* nd) { //0x1e
	Log("DecList1");
	Node* p = nd->leftmost;
	FieldList pf = (void*)malloc(sizeof(struct FieldList_));
	pf->name = p->attr.name;
	pf->type = &p->attr.type;
	pf->tail = NULL;
	nd->attr.type.structure = pf;
}

void DecList2(Node* nd) { //0x1f
	Log("DecList2");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	
	/* always create FieldList */
	FieldList pf = (void*)malloc(sizeof(struct FieldList_));
	pf->name = p->attr.name;
	pf->type = &p->attr.type;
	pf->tail = q->attr.type.structure;
	nd->attr.type.structure = pf;
}

void Dec(Node* nd) { //0x20 & 0x21
	Log("Dec");
	Node* p = nd->leftmost;
	nd->attr = p->attr;
	char* name = p->attr.name;
	HT_Node* ph = seekHT(name);
	if(!ph) {
		int loc = hash_pjw(name);
		ph = (void*)malloc(sizeof(HT_Node));
		ph->var = NULL;
		ph->next = HT[loc];
		ph->name = name;
		ph->type = nd->attr.type;
		ph->blg_name = nd->attr.blg_name;
		HT[loc] = ph;
	}
	else {
		if(!ph->blg_name)
			printerr(3, p);
		else {
			char* tmp = nd->attr.blg_name;
			if(tmp && strcmp(tmp, ph->blg_name) == 0) { //先判断tmp是否为空指针
			  printerr(15, p);
			}
			else {
			  printerr(3, p);
			}
		}
	}
	Node* q = p->right;
	if(q) {
		if(nd->attr.blg_name) {
			printerr(15, p); //结构体中不能初始化变量
			return;
		}
		q = q->right;
		int match = tpcheck(&p->attr.type, &q->attr.type);
		if(!match)
		  printerr(5, p);
	}
}

void Exp1(Node* nd) { //0x22
	Log("Exp1");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	int tp = p->pdt_type;
	if(tp != 0x31 && tp != 0x2f && tp != 0x30) {
	  printerr(6, p);
	  return ;
	}
	int match = tpcheck(&p->attr.type, &q->attr.type);
	if(!match)
	  printerr(5, p);
	else
	  nd->attr.type = p->attr.type;
}

void Exp2(Node* nd) { //0x23 & 0x24
	Log("Exp2");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	Type tp = &p->attr.type;
	Type tq = &q->attr.type;
	nd->attr.type = p->attr.type;
	if(tp->kind != BASIC || tp->basic != 0)
	  printerr(7, p);
	else if(tq->kind != BASIC || tq->basic != 0)
	  printerr(7, q);
}

void Exp3(Node* nd) { // 0x25 - 0x29
	Log("Exp3");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	nd->attr.type = q->attr.type;
	if(p->attr.type.kind != BASIC && p->attr.type.kind != ANY) {
		printerr(7, p);
		return;
	}
	nd->attr.type = p->attr.type;
	if(q->attr.type.kind != BASIC && q->attr.type.kind != ANY) {
		printerr(7, q);
		return;
	}
	int match = tpcheck(&p->attr.type, &q->attr.type);
	if(!match)
	  printerr(7, p);
}

void Exp4(Node* nd) { //0x2a
	Log("Exp4");
	Node* p = nd->leftmost->right;
	nd->attr.type = p->attr.type;
}

void Exp5(Node* nd) { //0x2b
	Log("Exp5");
	Node* p = nd->leftmost->right;
	if(p->attr.type.kind != BASIC && p->attr.type.kind != ANY) {
		printerr(7, p);
		nd->attr.type.kind = ANY;
		return;
	}
	nd->attr.type = p->attr.type;
}

void Exp6(Node* nd) { //0x2c
	Log("Exp6");
	Node* p = nd->leftmost->right;
	if((p->attr.type.kind != ANY) && (p->attr.type.kind != BASIC || p->attr.type.basic != 0)) {
		printerr(7, p);
		nd->attr.type.kind = ANY;
		return;
	}
	nd->attr.type = p->attr.type;
}

void Exp7(Node* nd) { //0x2d
	Log("Exp7");
	Node* p = nd->leftmost;
	char* name = p->id;
	HT_Node* r = seekHT(name);
	if(!r) {
		printerr(2, p);
		nd->attr.type.kind = ANY;
	}
	else {
		Type tp = &r->type;
		if(tp->kind != FUNC) {
		  printerr(11, p);
		  return;
		}
		Node* q = p->right->right;
		FieldList fl = r->type.func.para;
		Node* qa = q;
		nd->attr.type = *(r->type.func.ret); //设置表达式头结点类型为函数返回值类型
		if(!fl) {
			printerr(9, q);
			return;
		}
		int match = tpcheck(fl->type, &qa->attr.type);
		while(match) {
			fl = fl->tail;
			Type real;
			if(qa->leftmost->right) {
			  qa = qa->leftmost->right->right;
			  real = &qa->attr.type;
			}
			else {
				qa = NULL;
				real = NULL;
			}
			if(!fl && !real) return;
			else if(!fl) {
				printerr(9, qa);
				return;
			}
			else if(!real) {
				printerr(9, q);
				return;
			}
			match = tpcheck(fl->type, real);
		}
		printerr(9, q);
	}
}

void Exp8(Node* nd) { //0x2e
	Log("Exp8");
	Node* p = nd->leftmost;
	char* name = p->id;
	HT_Node* r = seekHT(name);
	if(!r) {
		printerr(2, p);
		nd->attr.type.kind = ANY;
	}
	else {
		Type tp = &r->type;
		nd->attr.type.kind = ANY;
		if(tp->kind != FUNC) {
			printerr(11, p);
			return;
		}
		nd->attr.type = *(r->type.func.ret);
		FieldList fl = r->type.func.para;
		if(fl)
		  printerr(9, p);
	}
}

void Exp9(Node* nd) { //0x2f
	Log("Exp9");
	Node* p = nd->leftmost;
	char* name = p->attr.name;
	assert(name);
	HT_Node* ph = seekHT(name);
	nd->attr.type.kind = ANY;
	//printf("HERE\n");
	if(!ph) {
	  printerr(2, p);
	}
	else {
		Type tp = &p->attr.type;
		if(tp->kind != ARRAY) {
		  printerr(10, p);
		  return;
		}
		Node* q = p->right->right;
		if(q->attr.type.kind != BASIC || q->attr.type.basic != 0) {
			printerr(12, q);
		}
		assert(tp->array.elem);
		nd->attr.type = *(tp->array.elem); // 脱一层
		nd->attr.name = name;
		//printf("leave\n");
	}
}

void Exp10(Node* nd) { //0x30
	Log("Exp10");
	Node* p = nd->leftmost;
	char* name = p->attr.name;
	HT_Node* ph = seekHT(name);
	if(ph) { // exp已经有类型了
		Type tp = &p->attr.type;
		if(tp->kind != STRUCTURE) {
			nd->attr.type.kind = ANY;
			printerr(13, p);
			return;
		}
		Node* q = p->right->right;
		name = q->id;
		nd->attr.name = name;
		FieldList fl = tp->structure;
		while(fl) {
			if(strcmp(fl->name, name) == 0) {
				nd->attr.type = *(fl->type);
				return;
			}
			fl = fl->tail;
		}
		nd->attr.type.kind = ANY;
		printerr(14, q);
	}
}

void Exp11(Node* nd) { //0x31
	Log("Exp11");
	Node* p = nd->leftmost;
	char* name = p->id;
	assert(name);
	nd->attr.name = name;
	p->attr.name = name;
	HT_Node* ph = seekHT(name);
	if(!ph) {
		printerr(1, p);
		nd->attr.type.kind = ANY;
	}
	else
		nd->attr.type = ph->type;
}

void Exp12(Node* nd) { //0x32 & 0x33
	Log("Exp12");
	Node* p = nd->leftmost;
	nd->d = p->d; //float is also 4 bytes?
	nd->attr = p->attr;
}

void Args(Node* nd) { //0x34 & 0x35
	Node* p = nd->leftmost;
	nd->attr = p->attr;
}

/* 空函数体 */
void inv(Node* nd) {
	return ;
}

