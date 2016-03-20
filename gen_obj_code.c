#include "gen_obj_code.h"

extern FILE* f;

void divide_basic_blocks(Node* root) {
	InterCodes p = root->ic;
	while(p) {
		int pk = p->code.kind;
		if(pk == IF_OP || pk == GOTO || pk == READ || pk == WRITE || pk == CALL) {
			p->isTail = true;
		}
		if(p->next && p->next->code.kind == LABEL_) {
			p->isTail = true;
		}
		p = p->next;
	}
}

void out_operand(Operand op) {
	switch(op->kind) {
		case VARIABLE: fprintf(f, "v%d", op->var_no); break;
		case TMP_VAR: fprintf(f, "t%d", op->tmp_no); break;
		case CONSTANT: fprintf(f, "%d", op->value); break;
		case LABEL: fprintf(f, "label%d", op->lbl_no); break;
	}
}

static inline void out_reg(int reg_idx) {
	if(reg_idx == 0) {
		fputs("$zero", f);
	}
	else if(reg_idx == 2) {
		fputs("$v0", f);
	}
	else if(reg_idx == 3) {
		fputs("$v1", f);
	}
	else if(reg_idx < 8) {
		fprintf(f, "$a%d", reg_idx - 4);
	}
	else if(reg_idx < 18) {
		fprintf(f, "$t%d", reg_idx - 8);
	}
	else if(reg_idx < 26) {
		fprintf(f, "$s%d", reg_idx - 18);
	}
	else if(reg_idx == 29) {
		fputs("$sp", f);
	}
	else if(reg_idx == 30) {
		fputs("$fp", f);
	}
	else if(reg_idx == 31) {
		fputs("$ra", f);
	}
}


static inline void out_lw(int rx, int off, int ry) {
	fputs("lw ", f);
	out_reg(rx);
	fprintf(f, ", %d(", off);
	out_reg(ry);
	fputs(")", f);
	fputs("\n", f);
}

static inline void out_sw(int ry, int off, int rx) {
	fputs("sw ", f);
	out_reg(ry);
	fprintf(f, ", %d(", off);
	out_reg(rx);
	fputs(")", f);
	fputs("\n", f);
}

static inline void out_li(int reg_idx, Operand op) {
	fputs("li ", f);
	out_reg(reg_idx);
	fputs(", ", f);
	out_operand(op);
	fputs("\n", f);
}

static inline void out_move(int l_idx, int r_idx) {
	fputs("move ", f);
	out_reg(l_idx);
	fputs(", ", f);
	out_reg(r_idx);
	fputs("\n", f);
}

static inline void out_addi(int rx, int ry, int k) {
	fputs("addi ", f);
	out_reg(rx);
	fputs(", ", f);
	out_reg(ry);
	fprintf(f, ", %d", k);
	fputs("\n", f);
}

static inline void out_add(int rx, int ry, int rz) {
	fputs("add ", f);
	out_reg(rx);
	fputs(", ", f);
	out_reg(ry);
	fputs(", ", f);
	out_reg(rz);
	fputs("\n", f);
}

static inline void out_sub(int rx, int ry, int rz) {
	fputs("sub ", f);
	out_reg(rx);
	fputs(", ", f);
	out_reg(ry);
	fputs(", ", f);
	out_reg(rz);
	fputs("\n", f);
}

static inline void out_sub_neg(int rx, int rz) {
	fputs("sub ", f);
	out_reg(rx);
	fputs(", $zero, ", f);
	out_reg(rz);
	fputs("\n", f);
}

static inline void out_mul(int rx, int ry, int rz) {
	fputs("mul ", f);
	out_reg(rx);
	fputs(", ", f);
	out_reg(ry);
	fputs(", ", f);
	out_reg(rz);
	fputs("\n", f);
}

static inline void out_div(int rx, int ry, int rz) {
	fputs("div ", f);
	out_reg(ry);
	fputs(", ", f);
	out_reg(rz);
	fputs("\nmflo ", f);
	out_reg(rx);
	fputs("\n", f);
}

static int cur_stk_off = 0;
Operand reg[32]; //init null
int cur_reg_turn = 7;
int next_reg() {
	cur_reg_turn = (cur_reg_turn - 7) % 18 + 8;
	return cur_reg_turn;
}

void spill(int r) {
	Operand op = reg[r];
	int off = op->off;
	if(0 == off) {
		cur_stk_off -= 4;
		off = op->off = cur_stk_off;
	}
	/* sp do not change now */
	op->reg_idx = -1;
	reg[r] = NULL;
	out_sw(r, off, 30);
}

/* reg_idx from 8 to 25 */
int get_reg(Operand op, bool isLoad) {
	int r = op->reg_idx;
	if(r == -1) {
		r = next_reg();
		if(reg[r]) {
			/* spill reg[r] */
			spill(r);
		}
		op->reg_idx = r;
		reg[r] = op;

		int off = op->off;
		if(isLoad && off) { //in stack
			out_lw(r, off, 30);
		}
	}
	return r;
}

void save_all_vars(bool isSaveTmp) {
	int i;
	for(i = 8; i < 26; i++) {
		if(reg[i] && isSaveTmp) spill(i);
		else if(reg[i] && reg[i]->kind == VARIABLE) spill(i);
		reg[i] = NULL;
	}
}

void out_data_codes() {
	fputs(".data\n", f);
	fputs("_prompt: .asciiz \"Enter an integer:\"\n", f);
	fputs("_ret: .asciiz \"\\n\"\n", f);
	fputs(".globl main\n", f);
}

void out_read() {
	fputs("read:\n", f);
	fputs("li $v0, 4\n", f);
	fputs("la $a0, _prompt\n", f);
	fputs("syscall\n", f);
	fputs("li $v0, 5\n", f);
	fputs("syscall\n", f);
	fputs("jr $ra\n", f);
}

void out_write() {
	fputs("\n", f);
	fputs("write:\n", f);
	fputs("li $v0, 1\n", f);
	fputs("syscall\n", f);
	fputs("li $v0, 4\n", f);
	fputs("la $a0, _ret\n", f);
	fputs("syscall\n", f);
	fputs("move $v0, $0\n", f);
	fputs("jr $ra\n", f);
}

void out_goto(InterCodes p) {
	fputs("j ", f);
	out_operand(p->code.go_to.label);
	fputs("\n", f);
}

void out_label(InterCodes p) {
	out_operand(p->code.lbl.label);
	fputs(":\n", f);
}

int param_num = 0;

void out_function(InterCodes p) {
	/* now just in main */
	fputs("\n", f);
	char* name = p->code.func.name;
	fprintf(f, "%s:\n", name);
	if(strcmp(name, "main") == 0) {
		out_move(30, 29); // mov $fp, $sp
	}
	cur_stk_off = 0; //re-init

	param_num = 0;
}

void out_param(InterCodes p) {
	param_num ++;
	int r = get_reg(p->code.param.para, false);
	out_move(r, 3 + param_num);
}

int star2reg(Operand op) {
	Operand p2a = op->p2a;
	int rr = get_reg(p2a, true);
	int rl = get_reg(new_tmp(), false);
	out_lw(rl, 0, rr);
	return rl;
}

void out_assign(InterCodes p) {
	Operand right = p->code.assign.right;
	Operand left = p->code.assign.left;
	int rx, ry;
	int kl, kr;

	/* right */
	int rk = right->kind;
	if(rk == CONSTANT) {
		kr = 1;
	}
	else if(rk == VARIABLE || rk == TMP_VAR) {
		ry = get_reg(right, true);
		kr = 2;
	}
	else if(rk == POINTER2ADDR) {
		ry = star2reg(right);
		kr = 3;
	}
	else if(rk == ADDRESS) {
		ry = get_reg(right->addr, true);
		kr = 4;
	}

	/* left */
	if(left->kind != POINTER2ADDR) {
		rx = get_reg(left, false);
		kl = 1;
	}
	else {
		rx = get_reg(left->p2a, true);
		kl = 2;
	}

	int kind = kl * 10 + kr;
	switch(kind) {
		case 11: out_li(rx, right); break;
		case 12: out_move(rx, ry); break;
		case 13: out_move(rx, ry); break;
		case 14: out_move(rx, ry); break;
		case 22: out_sw(ry, 0, rx); break;
		case 23: out_sw(ry, 0, rx); break;
		default: printf("inv assign\n");
	}
}

void out_call_read(InterCodes p) {
	cur_stk_off -= 4;
	out_sw(31, cur_stk_off, 30);
	fputs("jal read\n", f);
	out_lw(31, cur_stk_off, 30);
	cur_stk_off += 4;
	int r = get_reg(p->code.read.dest, false);
	out_move(r, 2);
}

void out_call_write(InterCodes p) {
	Operand op = p->code.write.dest;
	int r;
	if(op->kind != POINTER2ADDR) {
		r = get_reg(op, true);
	}
	else {
		r = star2reg(op);
	}
	out_move(4, r);

	save_all_vars(false);

	cur_stk_off -= 4;
	out_sw(31, cur_stk_off, 30);
	fputs("jal write\n", f);
	out_lw(31, cur_stk_off, 30);
	cur_stk_off += 4;
}

void out_if_goto(InterCodes p) {
	Operand left = p->code.if_op.t1;
	Operand right = p->code.if_op.t2;
	int rx, ry;
	/* left != CONST */
	if(left->kind != POINTER2ADDR) {
		rx = get_reg(left, true);
	}
	else {
		rx = star2reg(left);
	}
	if(right->kind == CONSTANT) {
		if(right->value == 0) {
			ry = 0;
		}
	}
	else if(right->kind != POINTER2ADDR) {
		ry = get_reg(right, true);
	}
	else {
		ry = star2reg(right);
	}

	save_all_vars(false);

	fputs("b", f);
	char* op = p->code.if_op.op;
	if(strcmp(op, ">") == 0) {
		fputs("gt", f);
	}
	else if(strcmp(op, "<") == 0) {
		fputs("lt", f);
	}
	else if(strcmp(op, "!=") == 0) {
		fputs("ne", f);
	}
	else if(strcmp(op, "==") == 0) {
		fputs("eq", f);
	}
	else if(strcmp(op, ">=") == 0) {
		fputs("ge", f);
	}
	else if(strcmp(op, "<=") == 0) {
		fputs("le", f);
	}
	fputs(" ", f);
	out_reg(rx);
	fputs(", ", f);
	out_reg(ry);
	fputs(", ", f);
	out_operand(p->code.if_op.label_true);
	fputs("\n", f);
}

void out_assign_plus(InterCodes p) {
	int rx, ry, rz;
	Operand left, right1, right2;
	left = p->code.assign3.left;
	right1 = p->code.assign3.right1;
	right2 = p->code.assign3.right2;
	rx = get_reg(left, false);

	/* right1 */
	int r1k = right1->kind;
	if(r1k == VARIABLE || r1k == TMP_VAR) {
		ry = get_reg(right1, true);
	}
	else if(r1k == ADDRESS) {
		ry = get_reg(right1->addr, true);
	}
	else if(r1k == POINTER2ADDR) {
		ry = star2reg(right1);
	}

	/* right2 */
	int r2k = right2->kind;
	if(r2k == VARIABLE || r2k == TMP_VAR) {
		rz = get_reg(right2, true);
	}
	else if(r2k == CONSTANT) {
		out_addi(rx, ry, right2->value);
		return;
	}
	else if(r2k == POINTER2ADDR) {
		rz = star2reg(right2);
	}

	out_add(rx, ry, rz);
}

void out_assign_minus(InterCodes p) {
	int rx, ry, rz;
	Operand left, right1, right2;
	left = p->code.assign3.left;
	right1 = p->code.assign3.right1;
	right2 = p->code.assign3.right2;
	rx = get_reg(left, false);

	/* right1 */
	int r1k = right1->kind;
	if(r1k == VARIABLE || r1k == TMP_VAR) {
		ry = get_reg(right1, true);
	}
	else if(r1k == CONSTANT) {
		if(right1->value == 0) {
			rz = get_reg(right2, true); // right2 is a tmp
			out_sub_neg(rx, rz);
			return;
		}
	}
	else if(r1k == POINTER2ADDR) {
		ry = star2reg(right1);
	}

	/* right2 */
	int r2k = right2->kind;
	if(r2k == VARIABLE || r2k == TMP_VAR) {
		rz = get_reg(right2, true);
	}
	else if(r2k == CONSTANT) {
		out_addi(rx, ry, -right2->value);
		return;
	}
	else if(r2k == POINTER2ADDR) {
		rz = star2reg(right2);
	}

	out_sub(rx, ry, rz);
}

void out_assign_star(InterCodes p) {
	int rx, ry, rz;
	Operand left, right1, right2;
	left = p->code.assign3.left;
	right1 = p->code.assign3.right1;
	right2 = p->code.assign3.right2;
	rx = get_reg(left, false);

	/* right1 */
	int r1k = right1->kind;
	if(r1k == VARIABLE || r1k == TMP_VAR) {
		ry = get_reg(right1, true);
	}
	else if(r1k == POINTER2ADDR) {
		ry = star2reg(right1);
	}

	/* right2 */
	int r2k = right2->kind;
	if(r2k == VARIABLE || r2k == TMP_VAR) {
		rz = get_reg(right2, true);
	}
	else if(r2k == CONSTANT) {
		rz = get_reg(new_tmp(), false);
		out_li(rz, right2);
	}
	else if(r2k == POINTER2ADDR) {
		rz = star2reg(right2);
	}

	out_mul(rx, ry, rz);
}

void out_assign_div(InterCodes p) {
	int rx, ry, rz;
	Operand left, right1, right2;
	left = p->code.assign3.left;
	right1 = p->code.assign3.right1;
	right2 = p->code.assign3.right2;
	rx = get_reg(left, false);

	/* right1 */
	int r1k = right1->kind;
	if(r1k == VARIABLE || r1k == TMP_VAR) {
		ry = get_reg(right1, true);
	}

	/* right2 */
	int r2k = right2->kind;
	if(r2k == VARIABLE || r2k == TMP_VAR) {
		rz = get_reg(right2, true);
	}

	out_div(rx, ry, rz);
}

void out_assign3(InterCodes p) {
	char op = p->code.assign3.op;
	switch(op) {
		case '+': out_assign_plus(p); break;
		case '-': out_assign_minus(p); break;
		case '*': out_assign_star(p); break;
		case '/': out_assign_div(p); break;
	}
}

int args_num = 0;

void out_arg(InterCodes p) {
	Operand arg = p->code.arg.arg;
	cur_stk_off -= 4;
	int ra;
	if(arg->kind != POINTER2ADDR) {
		ra = get_reg(arg, true);
	}
	else {
		ra = star2reg(arg);
	}
	out_sw(ra, cur_stk_off, 30);

	args_num ++;

	if(p->next->code.kind == CALL) {
		int i;
		for(i = 0; i < args_num; i++) {
			out_lw(4 + i, cur_stk_off, 30);
			cur_stk_off += 4;
		}
		args_num = 0;
	}
}

void out_call(InterCodes p) {
	cur_stk_off -= 4;
	out_sw(31, cur_stk_off, 30);

	/* $fp can be set in call T_T */
	cur_stk_off -= 4;
	out_sw(30, cur_stk_off, 30);
	out_addi(30, 30, cur_stk_off);

	fprintf(f, "jal %s\n", p->code.call.name);

	out_lw(30, 0, 30);
	cur_stk_off += 4;

	out_lw(31, cur_stk_off, 30);
	cur_stk_off += 4;

	int r = get_reg(p->code.call.place, false);
	out_move(r, 2);
}

void out_return(InterCodes p) {
	int r = get_reg(p->code.ret.val, true);
	out_move(2, r);
	fputs("jr $ra\n", f);
}

void out_dec(InterCodes p) {
	Operand op = p->code.dec.v;
	int r = get_reg(op, false);
	int len = p->code.dec.len;
	cur_stk_off -= len;
	out_addi(r, 30, cur_stk_off);
}

void out_text_codes(Node* root) {
	fputs(".text\n", f);
	divide_basic_blocks(root);
	InterCodes p = root->ic;
	out_read();
	out_write();
	while(p) {
		int pk = p->code.kind;
		if(p->isTail && pk == CALL) {
			save_all_vars(true);
		}
		else if(p->isTail && pk != IF_OP && pk != WRITE) { //if_op and write are exceptions
			save_all_vars(false);
		}
		switch(pk) {
			case GOTO: out_goto(p); break;
			case LABEL_: out_label(p); break;
			case FUNCTION: out_function(p); break;
			case ASSIGN: out_assign(p); break;
			case IF_OP: out_if_goto(p); break;
			case ASSIGN3: out_assign3(p); break;
			case READ: out_call_read(p); break;
			case WRITE: out_call_write(p); break;
			case RETURN_: out_return(p); break;
			case DEC: out_dec(p); break;
			case CALL: out_call(p); break;
			case PARAM: out_param(p); break;
			case ARG: out_arg(p); break;
			default: fputs("\n", f);
		}
		/*
		if(p->isTail && pk == CALL) {
			save_all_vars(true);
		}
		*/
		if(p->isTail) {
			save_all_vars(true); // before label
		}
		p = p->next;
	}
}

void out_obj_codes(Node* root) {
	out_data_codes();
	out_text_codes(root);
}
