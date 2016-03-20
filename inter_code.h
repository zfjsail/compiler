#include "semantic.h"

typedef void (*trans_helper)(Node* nd, bool isInh);

void prepare_rw();
void trans_traversal(Node* root);

void inv_(Node* nd, bool isInh);
void extdeflist(Node* nd, bool isInh);
void extdef(Node* nd, bool isInh);
void specifier(Node* nd, bool isInh);
void fundec1(Node* nd, bool isInh);
void fundec2(Node* nd, bool isInh);
void varlist(Node* nd, bool isInh);
void vardec1(Node* nd, bool isInh);
void vardec2(Node* nd, bool isInh);
void paramdec(Node* nd, bool isInh);
void compst(Node* nd, bool isInh);
void stmtlist(Node* nd, bool isInh);
void stmt1(Node* nd, bool isInh);
void stmt2(Node* nd, bool isInh);
void stmt3(Node* nd, bool isInh);
void stmt4(Node* nd, bool isInh);
void deflist(Node* nd, bool isInh);
void def(Node* nd, bool isInh);
void declist(Node* nd, bool isInh);
void dec1(Node* nd, bool isInh);
void dec2(Node* nd, bool isInh);
void exp1(Node* nd, bool isInh);
void exp2(Node* nd, bool isInh);
void exp3(Node* nd, bool isInh);
void exp4(Node* nd, bool isInh);
void exp5(Node* nd, bool isInh);
void exp6(Node* nd, bool isInh);
void exp7(Node* nd, bool isInh);
void exp8(Node* nd, bool isInh);
void exp9(Node* nd, bool isInh);
void exp10(Node* nd, bool isInh);
void exp11(Node* nd, bool isInh);
void exp12(Node* nd, bool isInh);
void exp13(Node* nd, bool isInh);
void exp14(Node* nd, bool isInh);
void exp15(Node* nd, bool isInh);
void exp16(Node* nd, bool isInh);
void args1(Node* nd, bool isInh);
void args2(Node* nd, bool isInh);
