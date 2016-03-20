#include "inter_code.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

extern HT_Node* HT[HT_SIZE];
extern int t_cnt;
extern int v_cnt;
extern int l_cnt;
bool isTranslate = true;

/* 函数指针表：每个产生式对应一个元素 */

/* 头文件中已经对inv函数进行了声明 */

trans_helper trans_func_table[FT_SIZE] = {
	/* 0x00 */	inv_, extdeflist, inv_, inv_,
	/* 0x04 */	extdef, inv_, inv_, inv_,
	/* 0x08 */	specifier, inv_, inv_, inv_,
	/* 0x0c */	inv_, vardec1, vardec2, fundec1,
	/* 0x10 */	fundec2, varlist, inv_, paramdec,
	/* 0x14 */	compst, stmtlist, inv_, inv_,
	/* 0x18 */	stmt1, stmt2, stmt3, stmt4,
	/* 0x1c */	deflist, def, inv_, declist,
	/* 0x20 */	dec1, dec2, exp1, exp2,
	/* 0x24 */	exp3, exp4, exp5, exp6,
	/* 0x28 */	exp7, exp8, exp9, exp10,
	/* 0x2c */	exp11, exp12, exp13, exp14,
	/* 0x30 */	inv_, exp15, exp16, inv_,
	/* 0x34 */	args1, args2, inv_, inv_
};

void prepare_rw() {
	int locr = hash_pjw("read");
	HT_Node* ph = (void*)malloc(sizeof(HT_Node));
	ph->next = HT[locr];
	ph->name = "read";

	Type type_int = (void*)malloc(sizeof(struct Type_));
	type_int->kind = BASIC;
	type_int->basic = 0;

	ph->type.kind = FUNC;
	ph->type.func.ret = type_int;
	ph->type.func.pnum = 0;
	ph->type.func.para = NULL;
	HT[locr] = ph;

	int locw = hash_pjw("write");
	ph = (void*)malloc(sizeof(HT_Node));
	ph->next = HT[locw];
	ph->name = "write";

	ph->type.kind = FUNC;
	ph->type.func.ret = type_int;
	ph->type.func.pnum = 1;

	FieldList fl = (void*)malloc(sizeof(struct FieldList_));
	fl->name = "n";
	fl->type = type_int;
	fl->tail = NULL;

	ph->type.func.para = fl;
	HT[locw] = ph;
}

void trans_traversal(Node* root) {
	Node* p = root->leftmost;
	Node* q = p; //memory
	Node* last = root;
	trans_func_table[root->pdt_type](root, true);
	if(!isTranslate) return;
	while(p) {
		trans_traversal(p);
		if(!isTranslate) return;

		last = p;
		p = p->right;
	}
	/* 函数指针表的好处 */
	if(q) // assert who ?!
	  root->ic = q->ic; //较通用,综合时设置, p已经发生变化，必定为空 
	trans_func_table[root->pdt_type](root, false);
}

Operand new_var() {
	Operand op = NEW(struct Operand_);
	op->kind = VARIABLE;
	op->var_no = ++v_cnt;
	op->op_desc = 0;
	op->reg_idx = -1;
	op->off = 0;
	op->save = true;
	return op;
}

Operand new_tmp() {
	Operand op = NEW(struct Operand_);
	op->kind = TMP_VAR;
	op->tmp_no = ++t_cnt;
	op->op_desc = 0;
	op->reg_idx = -1;
	op->off = 0;
	op->save = false;
	return op;
}

Operand new_address(Operand p) {
	Operand op = NEW(struct Operand_);
	op->kind = ADDRESS;
	op->addr = p;
	op->reg_idx = -1;
	op->off = 0;
	op->save = false;
	return op;
}

Operand new_pointer2addr(Operand p) {
	Operand op = NEW(struct Operand_);
	op->kind = POINTER2ADDR;
	op->p2a = p;
	op->reg_idx = -1;
	op->off = 0;
	op->save = false;
	return op;
}

Operand new_lbl() {
	Operand lbl = NEW(struct Operand_);
	lbl->kind = LABEL;
	lbl->lbl_no = ++l_cnt;
	lbl->ref = 0;
	return lbl;
}

Operand get_op_const(int n) {
	Operand op = NEW(struct Operand_);
	op->kind = CONSTANT;
	op->value = n;
	op->reg_idx = -1;
	op->off = 0;
	op->save = false;
	return  op;
}

Operand get_op_zero() {
	Operand op = NEW(struct Operand_);
	op->kind = CONSTANT;
	op->value = 0;
	op->reg_idx = -1;
	op->off = 0;
	op->save = false;
	return op;
}

Operand get_op_one() {
	Operand op = NEW(struct Operand_);
	op->kind = CONSTANT;
	op->value = 1;
	op->reg_idx = -1;
	op->off = 0;
	op->save = false;
	return op;
}

void link_ics(InterCodes ics1, InterCodes ics2) {
	InterCodes last = ics1;
	assert(ics1);
	ics1 = ics1->next;
	while(ics1) {
		last = ics1;
		ics1 = ics1->next;
	}
	last->next = ics2;
}

InterCodes new_ics() {
	InterCodes ics = NEW(struct InterCodes_);
	ics->next = NULL;
	ics->isTail = false;
	ics->active_list = NULL;
	return ics;
}

InterCodes new_ics_assign(Operand left, Operand right) {
	InterCodes ics = new_ics();
	assert(left);
	ics->code.kind = ASSIGN;
	ics->code.assign.left = left;
	ics->code.assign.right = right;
	return ics;
}

InterCodes new_ics_assign3(Operand left, Operand right1, Operand right2, char op) {
	InterCodes ics = new_ics();
	ics->code.kind = ASSIGN3;
	assert(left);
	ics->code.assign3.left = left;
	ics->code.assign3.right1 = right1;
	ics->code.assign3.right2 = right2;
	ics->code.assign3.op = op;
	return ics;
}

void print_assign3(InterCodes ics) {
	print_operand(ics->code.assign3.left);
	printf(" := ");
	if(ics->code.assign3.right1->kind != POINTER)
	  print_operand(ics->code.assign3.right1);
	else {
		ics->code.assign3.right1->kind = VARIABLE;
		print_operand(ics->code.assign3.right1);
		ics->code.assign3.right1->kind = POINTER;
	}
	printf(" %c ", ics->code.assign3.op);
	print_operand(ics->code.assign3.right2);
}

InterCodes new_ics_func(char* name) {
	InterCodes ics = new_ics();
	ics->code.kind = FUNCTION;
	ics->code.func.name = name;
	return ics;
}

InterCodes new_ics_ifop(Operand t1, char* op, Operand t2, Operand true_label) {
	InterCodes ics = new_ics();
	ics->code.kind = IF_OP;
	ics->code.if_op.t1 = t1;
	ics->code.if_op.op = op;
	ics->code.if_op.t2 = t2;
	ics->code.if_op.label_true = true_label;
	true_label->ref++;
	return ics;
}

InterCodes new_ics_write(Operand t) {
	InterCodes ics = new_ics();
	ics->code.kind = WRITE;
	ics->code.write.dest = t;
	return ics;
}

InterCodes new_ics_arg(Operand arg) {
	InterCodes ics = new_ics();
	ics->code.kind = ARG;
	ics->code.arg.arg = arg;
	return ics;
}

void print_operand(Operand op);
void print_arg(InterCodes ics) {
	printf("ARG ");
	if(ics->code.arg.arg->kind != POINTER)
	  print_operand(ics->code.arg.arg);
	else {
		ics->code.arg.arg->kind = VARIABLE;
		print_operand(ics->code.arg.arg);
		ics->code.arg.arg->kind = POINTER;
	}
}

void print_ifop(InterCodes ics) {
	printf("IF ");
	print_operand(ics->code.if_op.t1);
	printf(" %s ", ics->code.if_op.op);
	print_operand(ics->code.if_op.t2);
	printf(" GOTO ");
	print_operand(ics->code.if_op.label_true);
}

InterCodes new_ics_goto(Operand lbl) {
	InterCodes ics = new_ics();
	ics->code.kind = GOTO;
	ics->code.go_to.label = lbl;
	lbl->ref++;
	return ics;
}

InterCodes new_ics_label(Operand lbl) {
	InterCodes ics = new_ics();
	ics->code.kind = LABEL_; //小心啊 哪个enum 要加下划线 已经有了LABEL
	ics->code.lbl.label = lbl;
	return ics;
}

InterCodes new_ics_param(Operand para) {
	InterCodes ics = new_ics();
	ics->code.kind = PARAM;
	ics->code.param.para = para;
	return ics;
}

void print_param(InterCodes ics) {
	printf("PARAM ");
	if(ics->code.param.para->kind != POINTER)
	  print_operand(ics->code.param.para);
	else {
		ics->code.param.para->kind = VARIABLE;
		print_operand(ics->code.param.para);
		ics->code.param.para->kind = POINTER;
	}
}

InterCodes new_ics_call(Operand place, char* name) {
	InterCodes ics = new_ics();
	ics->code.kind = CALL;
	ics->code.call.place = place;
	ics->code.call.name = name;
	return ics;
}

void print_call(InterCodes ics) {
	print_operand(ics->code.call.place);
	printf(" := ");
	printf("CALL %s", ics->code.call.name);
}

InterCodes new_ics_dec(Operand v, int len) {
	InterCodes ics = new_ics();
	ics->code.kind = DEC;
	ics->code.dec.v = v;
	ics->code.dec.len = len;
	return ics;
}

void print_dec(InterCodes ics) {
	printf("DEC "); //注意大小写啊
	print_operand(ics->code.dec.v);
	printf(" %d", ics->code.dec.len);
}

void print_operand(Operand op) {
	assert(op);
	switch(op->kind) {
		case VARIABLE: {
						   printf("v%d", op->var_no);
						   break;
					   }
		case TMP_VAR: {
						  printf("t%d", op->tmp_no);
						  break;
					  }
		case CONSTANT: {
						   printf("#%d", op->value);
						   break;
					   }
		case LABEL: {
						printf("label%d", op->lbl_no);
						break;
					}
		case ADDRESS: {
						  printf("&");
						  print_operand(op->addr);
						  break;
					  }
		case POINTER2ADDR: {
							   printf("*");
							   print_operand(op->p2a);
							   break;
						   }
	}
}

void extdeflist(Node* nd, bool isInh) { //0x1
	Log("extdeflist");
	if(!isInh) {
		Node* p = nd->leftmost;
		Node* q = p->right;

		assert(p->ic);
		/* 小心 q 可能为空 */
		if(q && q->ic) {
			link_ics(p->ic, q->ic);
		}
		nd->ic = p->ic;
	}
}

void extdef(Node* nd, bool isInh) { //0x4
	Log("EXTDEF");
	Node* p = nd->leftmost;
	Node* q = p->right;
	Node* r = q->right;
	if(!isInh) {
		nd->ic = q->ic;
		assert(q->ic);
		link_ics(q->ic, r->ic);
		//q->ic->next = r->ic;
	}
}

void specifier(Node* nd, bool isInh) { //0x8
	Log("specifier");
	if(isInh) {
		isTranslate = false;
	}
}

void vardec1(Node* nd, bool isInh) { //0xd
	Log("vardec1");
	/* 最底层产生式，不区分isInh */
	/* 还是执行一次吧 */
	if(!isInh) {
		Node* p = nd->leftmost;
		HT_Node* ph = seekHT(p->id);
		//printf("%s\n",p->id);
		assert(ph);
		if(ph->var)
		  nd->place = ph->var;
		else {
			ph->var = new_var();
			nd->place = ph->var;
		}
	}
}

void vardec2(Node* nd, bool isInh) { //0xe
	Log("vardec2");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		p->attr.type.array.length = nd->attr.type.array.length * q->d; //还好q是终结符
	}
	else {
		//int p_len;
		nd->place = p->place;
		if(p->pdt_type == 0xd) { //最“底层”了
			p->attr.type.array.width = p->attr.type.array.length;
		}
		nd->attr.type.array.width = p->attr.type.array.width / q->d;
		nd->attr.type.array.length = p->attr.type.array.length;
		//p->attr.type.array.length = 4;
		//}
		//p_len = p->attr.type.array.length;
		//nd->attr.type.array.length = p_len * q->d;
}
}

void fundec1(Node* nd, bool isInh) { //0xf
	Log("fundec1");
	if(!isInh) {
		Node* p = nd->leftmost;
		Node* q = p->right->right;
		InterCodes ics1 = new_ics_func(p->id);
		assert(q->ic);
		link_ics(ics1, q->ic);
		nd->ic = ics1;
	}
}

void fundec2(Node* nd, bool isInh) { //0x10
	Log("FUNDEC2");
	if(!isInh) {
		Node* p = nd->leftmost;
		nd->ic = NEW(struct InterCodes_);
		nd->ic->next = NULL;
		nd->ic->isTail = false;
		nd->ic->active_list = NULL;
		nd->ic->code.kind = FUNCTION;
		nd->ic->code.func.name = p->id;
	}
}

void varlist(Node* nd, bool isInh) { //0x11
	Log("varlist");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(!isInh) {
		assert(p->ic);
		link_ics(p->ic, q->ic);
		nd->ic = p->ic;
	}
}

void paramdec(Node* nd, bool isInh) { //0x13
	Log("paramdec");
	Node* p = nd->leftmost->right;
	if(!isInh) {
		InterCodes ics = new_ics_param(p->place);
		nd->ic = ics;
		if(p->attr.type.kind != ARRAY) return;
		p->place->kind = POINTER;
		HT_Node* ph = seekHT(p->attr.name);
		assert(ph);
		//struct Type_ tp = ph->type;
		assert(ph->var);
		//nd->ic = new_ics_dec(ph->var, p->attr.type.array.length);
		if(p->attr.type.kind == ARRAY) {
			HT_Node* ph = seekHT(p->attr.name);
			Type ph_type = ph->type.array.elem;
			Node* q = p->leftmost;
			struct Type_ tp = q->attr.type;
			int dim = 1;
			while(ph_type->kind == ARRAY) {
				dim++;
				ph_type = ph_type->array.elem;
			}
			//printf("dim %d\n", dim);
			int* wid = (int*)malloc(sizeof(dim * 4));
			int i = dim - 1;
			wid[i] = 4;
			i--;
			while(tp.kind == ARRAY) {
				//ph_type->array.width = tp.array.width ;
				wid[i] = tp.array.width;
				//printf("%d\n", tp.array.width);
				//ph_type = ph_type->array.elem;
				q = q->leftmost;
				tp = q->attr.type;
				i--;
			}
			assert(i == -1);
			//ph_type = ph->type.array.elem;
			ph_type = &ph->type;
			i = 0;
			while(ph_type->kind == ARRAY) {
				ph_type->array.width = wid[i];
				//printf("ph %d\n", wid[i]);
				ph_type = ph_type->array.elem;
				i++;
			}
		}
	}
}

void compst(Node* nd, bool isInh) { //0x14
	Log("COMPST");
	Node* p = nd->leftmost->right;
	Node* q;
	/* 小心 deflist 可能为空 */
	if(!isInh) {
		if(p->right->right) {
			q = p->right;
			if(p->ic) {
				link_ics(p->ic, q->ic);
				nd->ic = p->ic;
			}
			else
			  nd->ic = q->ic;
		}
		else {
			q = p;
			nd->ic = q->ic;
		}
	}
}

void stmtlist(Node* nd, bool isInh) { //0x15
	Log("stmtlist");
	Node* p = nd->leftmost;
	Node* q = p->right;
	if(!q) return;
	if(!isInh) {
		assert(p->ic);
		link_ics(p->ic, q->ic);
		/*
		   InterCodes ics = p->ic->next;
		   InterCodes last = p->ic;
		   while(ics) { //一定是收尾相接，找到尾才行，不能改头部指针
		   last = ics;
		   ics = ics->next;
		   }
		   last->next = q->ic;
		   */
	}
}


/*
   void stmt1(Node* nd, bool isInh) { //0x16
   Node* p = nd->leftmost;
   if(!isInh) {
   nd->ic = p->ic;
   }
   }
   */

void stmt1(Node* nd, bool isInh) { //0x18
	Log("stmt1");
	Node* p = nd->leftmost;
	Node* q = p->right;
	if(isInh) {
		q->place = new_tmp();
	}
	else {
		nd->ic = new_ics();
		nd->ic->code.kind = RETURN_;
		nd->ic->code.ret.val = q->place;

		assert(q->ic);
		link_ics(q->ic, nd->ic);
		//q->ic->next = nd->ic;
		nd->ic = q->ic;
	}
}

void stmt2(Node* nd, bool isInh) { //0x19
	Log("stmt2");
	Node* p = nd->leftmost->right->right;
	Node* q = p->right->right;
	if(isInh) {
		p->truelabel = new_lbl();
		p->falselabel = new_lbl();
	}
	else {
		InterCodes ics2 = new_ics_label(p->truelabel);
		InterCodes ics4 = new_ics_label(p->falselabel);
		assert(p->ic);
		link_ics(p->ic, ics2);
		link_ics(ics2, q->ic);
		assert(q->ic);
		link_ics(q->ic, ics4);
		nd->ic = p->ic;
	}
}

void stmt3(Node* nd, bool isInh) { //0x1a
	Log("stmt3");
	Node* p = nd->leftmost->right->right;
	Node* q = p->right->right;
	Node* r = q->right->right;
	if(isInh) {
		p->truelabel = new_lbl();
		p->falselabel = new_lbl();
	}
	else {
		Operand lbl3 = new_lbl();
		InterCodes ics2 = new_ics_label(p->truelabel);
		InterCodes ics4 = new_ics_goto(lbl3);
		InterCodes ics5 = new_ics_label(p->falselabel);
		InterCodes ics7 = new_ics_label(lbl3);

		link_ics(p->ic, ics2);
		link_ics(ics2, q->ic);
		link_ics(q->ic, ics4);
		link_ics(ics4, ics5);
		link_ics(ics5, r->ic);
		link_ics(r->ic, ics7);
		nd->ic = p->ic; //勿忘设置根结点
	}
}

void stmt4(Node* nd, bool isInh) { //0x1b
	Log("stmt4");
	Node* p = nd->leftmost->right->right;
	Node* q = p->right->right;
	if(isInh) {
		p->truelabel = new_lbl();
		p->falselabel = new_lbl();
	}
	else {
		Operand lbl3 = new_lbl();
		InterCodes ics1 = new_ics_label(lbl3);
		InterCodes ics3 = new_ics_label(p->truelabel);
		InterCodes ics5 = new_ics_goto(lbl3);
		InterCodes ics6 = new_ics_label(p->falselabel);

		assert(p->ic);
		assert(q->ic);
		link_ics(ics1, p->ic);
		link_ics(p->ic, ics3);
		link_ics(ics3, q->ic);
		link_ics(q->ic, ics5);
		link_ics(ics5, ics6);
		nd->ic = ics1;
	}
}

void deflist(Node* nd, bool isInh) { //0x1c
	Log("deflist");
	if(!isInh) {
		Node* p = nd->leftmost;
		Node* q = p->right;
		if(!q) return;
		//assert(p->ic);
		if(p->ic) {
			link_ics(p->ic, q->ic);
			nd->ic = p->ic;
		}
		else
		  nd->ic = q->ic;
	}
}

void def(Node* nd, bool isInh) { //0x1d
	Log("def");
	if(!isInh) {
		Node* p = nd->leftmost->right;
		nd->ic = p->ic;
	}
}

void declist(Node* nd, bool isInh) { //0x1f
	Log("declist");
	if(!isInh) {
		Node* p = nd->leftmost;
		Node* q = p->right->right;
		if(!p->ic) {
			nd->ic = q->ic;
			return;
		}
		link_ics(p->ic, q->ic);
		nd->ic = p->ic;
	}
}

void dec1(Node* nd, bool isInh) { //0x20
	Log("dec1");
	Node* p = nd->leftmost;
	if(isInh) {
		p->attr.type.array.length = 4;
	}
	else {
		if(p->attr.type.kind != ARRAY) return;
		HT_Node* ph = seekHT(p->attr.name);
		assert(ph);
		//struct Type_ tp = ph->type;
		assert(ph->var);
		nd->ic = new_ics_dec(ph->var, p->attr.type.array.length);
		if(p->attr.type.kind == ARRAY) {
			HT_Node* ph = seekHT(p->attr.name);
			Type ph_type = ph->type.array.elem;
			Node* q = p->leftmost;
			struct Type_ tp = q->attr.type;
			int dim = 1;
			while(ph_type->kind == ARRAY) {
				dim++;
				ph_type = ph_type->array.elem;
			}
			//printf("dim %d\n", dim);
			int* wid = (int*)malloc(sizeof(dim * 4));
			int i = dim - 1;
			wid[i] = 4;
			i--;
			while(tp.kind == ARRAY) {
				//ph_type->array.width = tp.array.width ;
				wid[i] = tp.array.width;
				//printf("%d\n", tp.array.width);
				//ph_type = ph_type->array.elem;
				q = q->leftmost;
				tp = q->attr.type;
				i--;
			}
			assert(i == -1);
			//ph_type = ph->type.array.elem;
			ph_type = &ph->type;
			i = 0;
			while(ph_type->kind == ARRAY) {
				ph_type->array.width = wid[i];
				//printf("ph %d\n", wid[i]);
				ph_type = ph_type->array.elem;
				i++;
			}
		}
		//inv
	}
}

void dec2(Node* nd, bool isInh) { //0x21
	Log("dec2");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		q->place = new_tmp();
	}
	else {
		Node* r = p->leftmost;
		/* VarDec -> ID */
		HT_Node* ph = seekHT(r->id);
		InterCodes ics2 = new_ics_assign(ph->var, q->place);
		InterCodes ics3 = NULL;
		//assert(nd->place);
		if(nd->place)
		  ics3 = new_ics_assign(nd->place, ph->var);

		link_ics(q->ic, ics2);
		link_ics(ics2, ics3);
		nd->ic = q->ic;
	}
}

/* 分别处理 亮点 */
InterCodes exp_cond(Node* nd) {
	InterCodes ics2 = new_ics_ifop(nd->place, "!=", get_op_const(0), nd->truelabel);
	InterCodes ics3 = new_ics_goto(nd->falselabel);
	link_ics(ics2, ics3);
	return ics2;
}

void exp1(Node* nd, bool isInh) { //0x22
	Log("exp1");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		//Operand place = (void*)malloc(sizeof(struct Operand_));
		Operand place = new_tmp();
		q->place = place;
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		/* Exp1 -> ID */
		Node* r = p->leftmost;
		Operand v;
		if(p->pdt_type == 0x31) {
			HT_Node* ph = seekHT(r->id);
			assert(ph);
			nd->ic = NEW(struct InterCodes_); //小心结尾s
			nd->ic->next = NULL;
			nd->ic->isTail = false;
			nd->ic->active_list = NULL;
			assert(nd->ic);
			nd->ic->code.kind = ASSIGN;
			if(ph->var)
			  v = ph->var;
			else {
				v = new_var();
				ph->var = v;
			}
			nd->ic->code.assign.left = v;
			nd->ic->code.assign.right = q->place;
		}
		else { //array element
			nd->ic = new_ics_assign(p->place, q->place);
			link_ics(p->ic, nd->ic); //注意左值也有code
			nd->ic = p->ic;
			v = p->place;
		}

		assert(q->ic);
		link_ics(q->ic, nd->ic);
		//q->ic->next = nd->ic;

		if(nd->place) {
			InterCodes ics3= new_ics_assign(nd->place, v);
			link_ics(nd->ic, ics3);
		}
		//printf("leave\n");
		nd->ic = q->ic; //增量啊
		if(nd->truelabel) {
			link_ics(nd->ic, exp_cond(nd));
		}
	}
}

InterCodes exp2_cond(Node* nd) {
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	InterCodes ics2 = new_ics_label(p->truelabel);
	link_ics(p->ic, ics2);
	link_ics(ics2, q->ic);
	return p->ic;
}

void exp2(Node* nd, bool isInh) { //0x23
	Log("exp2");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		if(nd->place) {
			nd->truelabel = new_lbl();
			nd->falselabel = new_lbl();
		}
		/* inherit */
		p->truelabel = new_lbl();
		p->falselabel = nd->falselabel;
		q->truelabel = nd->truelabel;
		q->falselabel = nd->falselabel;
	}
	else {
		if(nd->place) {
			nd->place->save = true;
			InterCodes ics1 = new_ics_assign(nd->place, get_op_zero());
			InterCodes ics2 = exp2_cond(nd);
			InterCodes ics3 = new_ics_label(nd->truelabel);
			InterCodes ics4 = new_ics_assign(nd->place, get_op_one());
			InterCodes ics5 = new_ics_label(nd->falselabel);

			//link and set nd->ic
			link_ics(ics1, ics2);
			link_ics(ics2, ics3);
			link_ics(ics3, ics4);
			link_ics(ics4, ics5);
			nd->ic = ics1;
		}
		else
		  nd->ic = exp2_cond(nd);

	}
}

InterCodes exp3_cond(Node* nd) {
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	InterCodes ics2 = new_ics_label(p->falselabel);
	assert(p->ic);
	link_ics(p->ic, ics2);
	link_ics(ics2, q->ic);
	return p->ic;
}

void exp3(Node* nd, bool isInh) { //0x24
	Log("exp3");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		if(nd->place) {
			nd->truelabel = new_lbl();
			nd->falselabel = new_lbl();
		}
		p->truelabel = nd->truelabel;
		p->falselabel = new_lbl();
		q->truelabel = nd->truelabel;
		q->falselabel = nd->falselabel;
	}
	else {
		if(nd->place) {
			nd->place->save = true;
			InterCodes ics1 = new_ics_assign(nd->place, get_op_zero());
			InterCodes ics2 = exp3_cond(nd);
			InterCodes ics3 = new_ics_label(nd->truelabel);
			InterCodes ics4 = new_ics_assign(nd->place, get_op_one());
			InterCodes ics5 = new_ics_label(nd->falselabel);

			link_ics(ics1, ics2);
			assert(ics2);
			link_ics(ics2, ics3);
			link_ics(ics3, ics4);
			link_ics(ics4, ics5);
			nd->ic = ics1;
		}
		else
		  nd->ic = exp3_cond(nd);
	}
}


void exp4_cond(Node* nd) {
	Node* p = nd->leftmost;
	Node* q = p->right;
	Node* r = q->right;
	InterCodes ics3 = new_ics_ifop(p->place, q->relop, r->place, nd->truelabel);
	InterCodes ics4 = new_ics_goto(nd->falselabel);
	assert(p->ic);
	HT_Node* ph;
	HT_Node* rh;
	if(p->pdt_type == 0x31 && r->pdt_type == 0x31) {
		ph = seekHT(p->attr.name);
		rh = seekHT(r->attr.name);
		ics3 = new_ics_ifop(ph->var, q->relop, rh->var, nd->truelabel);
		link_ics(ics3, ics4);
		nd->ic = ics3;
		return;
	}
	if(p->pdt_type == 0x31) {
		ph = seekHT(p->attr.name);
		ics3 = new_ics_ifop(ph->var, q->relop, r->place, nd->truelabel);
		link_ics(r->ic, ics3);
		link_ics(ics3, ics4);
		nd->ic = r->ic;
		return;
	}
	if(r->pdt_type == 0x31) {
		rh = seekHT(r->attr.name);
		ics3 = new_ics_ifop(p->place, q->relop, rh->var, nd->truelabel);
		link_ics(p->ic, ics3);
		link_ics(ics3, ics4);
		nd->ic = p->ic;
		return;
	}
	link_ics(p->ic, r->ic);
	link_ics(r->ic, ics3);
	link_ics(ics3, ics4);
	nd->ic = p->ic;
}

void exp4(Node* nd, bool isInh) { //0x25
	Log("exp4");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		//if(p->pdt_type != 0x31) //局部变量不是临时变量
		if(!p->place)
		  p->place = new_tmp();
		//if(q->pdt_type != 0x31)
		if(!q->place)
		  q->place = new_tmp();
	}
	else {
		//InterCodes ics1 = new_ics();

		if(nd->place) {
			nd->truelabel = new_lbl();
			nd->falselabel = new_lbl();
			Operand o_0 = get_op_zero();
			nd->place->save = true;
			InterCodes ics1 = new_ics_assign(nd->place, o_0);
			exp4_cond(nd);
			InterCodes ics2 = nd->ic;
			InterCodes ics3 = new_ics_label(nd->truelabel);

			Operand o_1 = NEW(struct Operand_);
			o_1->kind = CONSTANT;
			o_1->value = 1;
			InterCodes ics4 = new_ics_assign(nd->place, o_1);
			InterCodes ics5 = new_ics_label(nd->falselabel);
			link_ics(ics1, ics2);
			assert(ics2);
			link_ics(ics2, ics3);
			link_ics(ics3, ics4);
			link_ics(ics4, ics5);
			nd->ic = ics1;

		}
		else
		  exp4_cond(nd);
	}

}

void exp5(Node* nd, bool isInh) { //0x26
	Log("exp5");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		p->place = new_tmp();
		q->place = new_tmp();
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		/* 针对 inc 指令 */
		if(p->pdt_type == 0x31 && q->pdt_type == 0x32) {
			HT_Node* ph = seekHT(p->attr.name);
			nd->ic = new_ics_assign3(nd->place, ph->var, get_op_const(q->leftmost->d), '+');
			if(nd->truelabel)
			  link_ics(nd->ic, exp_cond(nd));
			return;
		}
		assert(nd->place);
		InterCodes ics3 = new_ics_assign3(nd->place, p->place, q->place, '+');
		assert(p->ic);
		link_ics(p->ic, q->ic);
		assert(q->ic);
		link_ics(q->ic, ics3);
		nd->ic = p->ic;
		if(nd->truelabel) 
		  link_ics(nd->ic, exp_cond(nd));
	}
}

void exp6(Node* nd, bool isInh) { //0x27
	Log("exp6");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		p->place = new_tmp();
		q->place = new_tmp();
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		if(p->pdt_type == 0x31 && q->pdt_type == 0x32) {
			HT_Node* ph = seekHT(p->attr.name);
			nd->ic = new_ics_assign3(nd->place, ph->var, get_op_const(q->leftmost->d), '-');
			if(nd->truelabel)
			  link_ics(nd->ic, exp_cond(nd));
			return;
		}
		assert(nd->place);
		InterCodes ics3 = new_ics_assign3(nd->place, p->place, q->place, '-');
		assert(p->ic);
		link_ics(p->ic, q->ic);
		assert(q->ic);
		link_ics(q->ic, ics3);
		nd->ic = p->ic;
		if(nd->truelabel)
		  link_ics(nd->ic, exp_cond(nd));
	}
}

void exp7(Node* nd, bool isInh) { //0x28
	Log("exp7");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		p->place = new_tmp();
		q->place = new_tmp();
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		assert(nd->place);
		InterCodes ics3 = new_ics_assign3(nd->place, p->place, q->place, '*');
		assert(p->ic);
		link_ics(p->ic, q->ic);
		assert(q->ic);
		link_ics(q->ic, ics3);
		nd->ic = p->ic;
		if(nd->truelabel)
		  link_ics(nd->ic, exp_cond(nd));
	}
}

void exp8(Node* nd, bool isInh) { //0x29
	Log("exp5");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		p->place = new_tmp();
		q->place = new_tmp();
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		assert(nd->place);
		InterCodes ics3 = new_ics_assign3(nd->place, p->place, q->place, '/');
		assert(p->ic);
		link_ics(p->ic, q->ic);
		assert(q->ic);
		link_ics(q->ic, ics3);
		nd->ic = p->ic;
		if(nd->truelabel)
		  link_ics(nd->ic, exp_cond(nd));
	}
}

void exp9(Node* nd, bool isInh) { //0x2a
	Log("exp9");
	Node* p = nd->leftmost->right;
	if(isInh) {
		/* 记得传递label */
		p->truelabel = nd->truelabel;
		p->falselabel = nd->falselabel;
		/* 要传递全呐 */
		p->place = nd->place;
		//printf("leave1");
	}
	else {
		nd->ic = p->ic;
		assert(nd->ic);
		//printf("leave2");
	}
}

void exp10(Node* nd, bool isInh) { //0x2b
	Log("exp10");
	Node* p = nd->leftmost->right;
	if(isInh) {
		p->place = new_tmp();
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		Operand o_0 = get_op_zero();
		assert(nd->place);
		InterCodes ics2 = new_ics_assign3(nd->place, o_0, p->place, '-');
		link_ics(p->ic, ics2);
		nd->ic = p->ic;
		if(nd->truelabel)
		  link_ics(nd->ic, exp_cond(nd));
	}
}

void exp11(Node* nd, bool isInh) { //0x2c
	Log("exp11");
	Node* p = nd->leftmost->right;
	if(isInh) {
		p->place = new_tmp();
		if(nd->place) {
			nd->truelabel = new_lbl();
			nd->falselabel = new_lbl();
		}
		p->truelabel = nd->falselabel;
		p->falselabel = nd->truelabel;
	}
	else {
		if(nd->place) {
			nd->place->save = true;
			InterCodes ics1 = new_ics_assign(nd->place, get_op_zero());
			//InterCodes ics2 = exp11_cond(nd);
			InterCodes ics3 = new_ics_label(nd->truelabel);
			InterCodes ics4 = new_ics_assign(nd->place, get_op_one());
			InterCodes ics5 = new_ics_label(nd->falselabel);
			//link_ics(ics1, ics2);
			link_ics(ics1, ics3);
			link_ics(ics3, ics4);
			link_ics(ics4, ics5);
			nd->ic = ics1;
		}
		else {
			nd->ic = p->ic; //test
			assert(nd->ic);
			//printf("enter\n");
		}
	}
}

void exp12(Node* nd, bool isInh) { //0x2d
	Log("exp12");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		q->arg_list = NULL;
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		HT_Node* ph = seekHT(p->id);
		//printf("%s\n",p->id);
		assert(ph);
		if(strcmp(p->id, "write") == 0) {
			//printf("enter\n");
			assert(q->arg_list);
			InterCodes ics = new_ics_write(q->arg_list->arg); //恰好是一个参数
			link_ics(q->ic, ics);
			nd->ic = q->ic;
			assert(nd->ic);
		}
		else {
			InterCodes ics2 = NULL;
			Arg_Node al = q->arg_list;
			assert(al);
			while(al) {
				InterCodes tmp = new_ics_arg(al->arg);
				if(ics2)
				  link_ics(ics2, tmp);
				else
				  ics2 = tmp;
				al = al->next;
			}
			//assert(nd->place);
			InterCodes ics3 = NULL;
			if(nd->place)
			  ics3 = new_ics_call(nd->place, p->id);
			else
			  ics3 = new_ics_call(new_tmp(), p->id); //不能丢

			assert(q->ic);
			link_ics(q->ic, ics2);
			link_ics(ics2, ics3);
			nd->ic = q->ic;
			if(nd->truelabel)
			  link_ics(nd->ic, exp_cond(nd));
		}
	}
}

void exp13(Node* nd, bool isInh) { //0x2e
	Log("exp13");
	if(isInh) {
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		Node* p = nd->leftmost;
		HT_Node* ph = seekHT(p->id);
		//HT_Node* ph = seekHT(nd->attr.name);
		assert(ph);
		//printf("%s\n", p->id);
		if(strcmp(p->id, "read") == 0) {
			//printf("enter\n");
			nd->ic = NEW(struct InterCodes_);
			nd->ic->next = NULL;
			nd->ic->isTail = false;
			nd->ic->active_list = NULL;
			nd->ic->code.kind = READ;
			nd->ic->code.read.dest = nd->place;
		}
		else {
			//assert(nd->place);
			if(nd->place)
			  nd->ic = new_ics_call(nd->place, p->id);
			else
			  nd->ic = new_ics_call(new_tmp(), p->id);
		}
		if(nd->truelabel)
		  link_ics(nd->ic, exp_cond(nd));
	}
}

void exp14(Node* nd, bool isInh) { //0x2f
	Log("exp14");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		if(!nd->place) nd->place = new_tmp();
		q->place = new_tmp();
	}
	else {
		/* 得到 width 信息 */
		nd->attr.type = *(p->attr.type.array.elem);
		int pwidth = p->attr.type.array.width;
		Operand width = get_op_const(p->attr.type.array.width);
		//print_operand(width);
		Operand tmp = new_tmp();
		InterCodes ics2 = new_ics_assign3(tmp, q->place, width, '*');
		link_ics(q->ic, ics2);

		if(p->pdt_type == 0x31) { //底层
			HT_Node* ph = seekHT(p->attr.name);
			assert(ph);
			Operand addr = NEW(struct Operand_);
			addr->kind = ADDRESS;
			addr->addr = ph->var;
			assert(ph->var);
			InterCodes ics3;
			if(ph->var->kind == POINTER) {
				//printf("enter1\n");
				if(q->pdt_type == 0x32) { //const
					if(q->leftmost->d == 0) {
						//printf("enter2\n");
						nd->ic = new_ics_assign(nd->place, ph->var);
					}
					else {
						Operand off = get_op_const(q->leftmost->d * pwidth);
						nd->ic = new_ics_assign3(nd->place, ph->var, off, '+');
					}
					if(nd->attr.type.kind == BASIC) {
						nd->place = new_pointer2addr(nd->place);
						if(nd->truelabel)
						  link_ics(nd->ic, exp_cond(nd));
					}
					return;
				}
				ph->var->kind = VARIABLE;
				ics3 = new_ics_assign3(nd->place, ph->var, tmp, '+');
				ph->var->kind = POINTER;
			}
			else {
				if(q->pdt_type == 0x32) { 
					if(q->leftmost->d == 0) {
						nd->ic = new_ics_assign(nd->place, addr);
					}
					else {
						Operand off = get_op_const(q->leftmost->d * pwidth);
						nd->ic = new_ics_assign3(nd->place, addr, off, '+');
					}
					if(nd->attr.type.kind == BASIC) {
						nd->place = new_pointer2addr(nd->place);
						if(nd->truelabel)
						  link_ics(nd->ic, exp_cond(nd));
					}
					return;
				}
				ics3 = new_ics_assign3(nd->place, addr, tmp, '+');
			}
			link_ics(ics2, ics3);
			nd->ic = q->ic;
		}
		else {
			if(q->pdt_type == 0x32) {
				if(q->leftmost->d == 0) {
					nd->ic = new_ics_assign(nd->place, p->place);
				}
				else {
					Operand off = get_op_const(q->leftmost->d * pwidth);
					nd->ic = new_ics_assign3(nd->place, p->place, off, '+');
				}
				link_ics(p->ic, nd->ic);
				nd->ic = p->ic;
			}
			else {
				link_ics(p->ic, q->ic);
				InterCodes ics3 = new_ics_assign3(nd->place, p->place, tmp, '+');
				link_ics(ics2, ics3);
				nd->ic = p->ic;
			}
		}
		if(nd->attr.type.kind == BASIC) { //最上层
			nd->place = new_pointer2addr(nd->place);
			if(nd->truelabel)
			  link_ics(nd->ic, exp_cond(nd));
		}
	}
}


void exp15(Node* nd, bool isInh) { //0x31
	Log("exp15");
	Node* p = nd->leftmost;
	if(isInh) {
		if(nd->truelabel)
		  nd->place = new_tmp();
	}
	else {
		HT_Node* ph = seekHT(p->id);
		nd->attr.type = ph->type;
		if(!ph->var) {
			ph->var = new_var();
		}
		//nd->place = ph->var; 大改
		//assert(nd->place);
		nd->ic = NULL;

		if(nd->place) 	//恒等式
		  nd->ic = new_ics_assign(nd->place, ph->var);
		if(nd->truelabel) { //标志要调用cond函数
			char* op = "!=";
			assert(nd->place);
			InterCodes ics2 = new_ics_ifop(nd->place, op, get_op_zero(), nd->truelabel);
			InterCodes ics3 = new_ics_goto(nd->falselabel);

			link_ics(nd->ic, ics2);
			link_ics(ics2, ics3);
		}
	}
}

void exp16(Node* nd, bool isInh) { //0x32
	Log("exp16");
	Node* p = nd->leftmost;
	if(!isInh) {
		if(nd->truelabel) {
			nd->place = new_tmp();
		}
		int val = p->d;
		nd->ic = new_ics();
		nd->ic->code.kind = ASSIGN;
		assert(nd->place);
		nd->ic->code.assign.left = nd->place;

		Operand op = NEW(struct Operand_);
		op->kind = CONSTANT;
		op->value = val;

		nd->ic->code.assign.right = op;
		InterCodes ics1 = nd->ic;

		if(nd->truelabel) {
			InterCodes ics2 = new_ics_ifop(nd->place, "!=", get_op_zero(), nd->truelabel);
			InterCodes ics3 = new_ics_goto(nd->falselabel);
			link_ics(ics1, ics2);
			link_ics(ics2, ics3);
			nd->ic = ics1;
		}
	}
}

void args1(Node* nd, bool isInh) { //0x34
	Log("args1");
	Node* p = nd->leftmost;
	Node* q = p->right->right;
	if(isInh) {
		p->place = new_tmp();
	}
	else {
		/* 注意顺序 */
		Operand ary = p->place;
		if(p->pdt_type == 0x31) {
			HT_Node* ph = seekHT(p->attr.name);
			assert(ph);
			if(ph->type.kind == ARRAY) {
				//printf("enter\n");
				ary = new_address(ph->var);
			}
			if(ph->var->kind == POINTER) {
				ary = ph->var;
			}
		}
		Arg_Node ag = NEW(struct Arg_Node_); //记得要new
		ag->arg = ary;
		ag->next = NULL;
		Arg_Node pre;
		Arg_Node cur = q->arg_list;
		while(cur) {
			pre = cur;
			cur = cur->next;
		}
		pre->next = ag;
		nd->arg_list = q->arg_list;
		assert(p->ic);
		link_ics(p->ic, q->ic);
		nd->ic = p->ic;
	}
}

void args2(Node* nd, bool isInh) { //0x35
	Log("args2");
	Node* p = nd->leftmost;
	if(isInh) {
		p->place = new_tmp();
	}
	else {
		nd->arg_list = NEW(struct Arg_Node_);
		nd->arg_list->next = NULL;
		nd->arg_list->arg = p->place;
		if(p->pdt_type == 0x31) {
			HT_Node* ph = seekHT(p->attr.name);
			assert(ph);
			if(ph->type.kind == ARRAY) {
				Operand ary = new_address(ph->var);
				nd->arg_list->arg = ary;
			}
			if(ph->var->kind == POINTER) {
				Operand ary = ph->var;
				nd->arg_list->arg = ph->var;
			}
		}
		nd->ic = p->ic;
	}
}

void inv_(Node* nd, bool isInh) {
	return ;
}

void print_inter_codes(Node* root) {
	InterCodes p = root->ic;
	bool isBegin = false;
	while(p) {
		//printf("%d\n", p->code.kind);
		switch(p->code.kind) {
			case ASSIGN: {	
							 Operand left = p->code.assign.left;
							 print_operand(left);
							 printf(" := ");
							 Operand right = p->code.assign.right;
							 if(right->kind != POINTER)
							   print_operand(right);
							 else {
								 right->kind = VARIABLE;
								 print_operand(right);
								 right->kind = POINTER;
							 }
							 break;
						 }
			case ASSIGN3: {
							  print_assign3(p);
							  break;
						  }
			case READ: {
						   Operand dest = p->code.read.dest;
						   printf("READ t%d", dest->tmp_no);
						   break;
					   }
			case WRITE: {
							printf("WRITE ");
							print_operand(p->code.write.dest);
							break;
						}
			case FUNCTION: {
							   if(isBegin)
								 printf("\n");
							   printf("FUNCTION %s :", p->code.func.name);
							   isBegin = true;
							   break;
						   }
			case RETURN_: {
							  printf("RETURN ");
							  print_operand(p->code.ret.val);
							  //if(p->next)
							  //printf("\n"); //视为函数总有返回语句 error 一个函数可能有多个返回语句
							  break;
						  }
			case IF_OP: {
							print_ifop(p);
							break;
						}
			case GOTO: {
						   printf("GOTO ");
						   print_operand(p->code.go_to.label);
						   break;
					   }
			case LABEL_: {
							 printf("LABEL ");
							 print_operand(p->code.lbl.label);
							 printf(" :");
							 break;
						 }
			case PARAM: {
							print_param(p);
							break;
						}
			case CALL: {
						   print_call(p);
						   break;
					   }
			case ARG: {
						  print_arg(p);
						  break;
					  }
			case DEC: {
						  print_dec(p);
						  break;
					  }
		}
		printf("\n");
		p = p->next;
	}
}

void print_single_ic(InterCodes p){
	switch(p->code.kind) {
		case ASSIGN: {	
						 Operand left = p->code.assign.left;
						 print_operand(left);
						 printf(" := ");
						 Operand right = p->code.assign.right;
						 if(right->kind != POINTER)
						   print_operand(right);
						 else {
							 right->kind = VARIABLE;
							 print_operand(right);
							 right->kind = POINTER;
						 }
						 break;
					 }
		case ASSIGN3: {
						  print_assign3(p);
						  break;
					  }
		case READ: {
					   Operand dest = p->code.read.dest;
					   printf("READ t%d", dest->tmp_no);
					   break;
				   }
		case WRITE: {
						printf("WRITE ");
						print_operand(p->code.write.dest);
						break;
					}
		case FUNCTION: {
						   printf("FUNCTION %s :", p->code.func.name);
						   break;
					   }
		case RETURN_: {
						  printf("RETURN ");
						  print_operand(p->code.ret.val);
						  //if(p->next)
						  //printf("\n"); //视为函数总有返回语句 error 一个函数可能有多个返回语句
						  break;
					  }
		case IF_OP: {
						print_ifop(p);
						break;
					}
		case GOTO: {
					   printf("GOTO ");
					   print_operand(p->code.go_to.label);
					   break;
				   }
		case LABEL_: {
						 printf("LABEL ");
						 print_operand(p->code.lbl.label);
						 printf(" :");
						 break;
					 }
		case PARAM: {
						print_param(p);
						break;
					}
		case CALL: {
					   print_call(p);
					   break;
				   }
		case ARG: {
					  print_arg(p);
					  break;
				  }
		case DEC: {
					  print_dec(p);
					  break;
				  }
	}
}
