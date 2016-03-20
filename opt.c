#include "opt.h"

extern Node* root;
extern int l_cnt;

void inverse_op(char** op) {
	if(strcmp(*op, "<") == 0) *op = ">=";
	else if(strcmp(*op, ">") == 0) *op = "<=";
	else if(strcmp(*op, "<=") == 0) *op = ">";
	else if(strcmp(*op, ">=") == 0) *op = "<";
	else if(strcmp(*op, "==") == 0) *op = "!=";
	else *op = "==";
}

void dec_label() {
	int i;
	InterCodes ic;
	for(i = 1; i <= l_cnt; i++) {
		ic = root->ic;
		InterCodes prev;
		InterCodes prevprev;
		Operand next_lbl;
		//int next_lbl;
		while(ic) {
			if(ic->code.kind == LABEL_ && ic->code.lbl.label->lbl_no == i && ic->next && ic->next->code.kind == LABEL_) {
				//next_lbl = ic->next->code.lbl.label->lbl_no;
				next_lbl = ic->next->code.lbl.label;
				ic = ic->next;
				break;
			}
			if(ic->code.kind == LABEL_ && ic->code.lbl.label->lbl_no == i && ic->next && ic->next->code.kind == GOTO) {
				//next_lbl = ic->next->code.go_to.label->lbl_no;
				next_lbl = ic->next->code.lbl.label;
				ic = ic->next;
				break;
			}
			prevprev = prev;
			prev = ic;
			ic = ic->next;
		}
		if(ic) { //找到两个连续的label
			InterCodes redu = prev->next;
			prev->next = ic; //指针指得谁弄清楚啊
			free(redu);
			InterCodes target = root->ic;
			while(target) {
				if(target->code.kind == GOTO && target->code.go_to.label->lbl_no == i) {
					//target->code.go_to.label->lbl_no = next_lbl;
					target->code.go_to.label = next_lbl;
					next_lbl->ref++; //引用计数要更新，小心啊
				}
				else if(target->code.kind == IF_OP && target->code.if_op.label_true->lbl_no == i) {
					//target->code.if_op.label_true->lbl_no = next_lbl;
					target->code.if_op.label_true = next_lbl;
					next_lbl->ref++;
				}
				target = target->next;
			}
		}
	}

	
	ic = root->ic;
	while(ic) {
		InterCodes ic2 = ic->next;
		if(!ic2) break;
		InterCodes ic3 = ic2->next;
		if(!ic3) break;
		if(ic->code.kind == IF_OP && ic2->code.kind == GOTO && ic3->code.kind == LABEL_) {
			Operand lbl_1 = ic->code.if_op.label_true;
			Operand lbl_2 = ic2->code.go_to.label;
			Operand lbl_3 = ic3->code.lbl.label;
			if(lbl_1->lbl_no == lbl_3->lbl_no) {
				//printf("%s\n", ic->code.if_op.op);
				inverse_op(&ic->code.if_op.op);
				//printf("%s\n", ic->code.if_op.op);
				ic->code.if_op.label_true = lbl_2;
				lbl_1->ref--;
				ic->next = ic3;
				free(ic2);
				if(lbl_1->ref == 0) {
					free(lbl_1);
					InterCodes ic4 = ic3->next;
					ic->next = ic4;
					free(ic3);
				}

			}
		}
		ic = ic->next;
	}
	
}

