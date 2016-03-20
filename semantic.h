#include "node.h"

#define HT_SIZE 0x3fff //哈希表大小
#define FT_SIZE 56 //函数指针表大小

typedef void (*sem_helper)(Node* nd);

int hash_pjw(char* name);
void init_HT();

void inv(Node* nd);

void ExtDecList(Node* nd);
void Specifier1(Node* nd);
void Specifier2(Node* nd);
void StructSpecifier1(Node* nd);
void StructSpecifier2(Node* nd);
void OptTag(Node* nd);
void Tag(Node* nd);
void VarDec1(Node* nd);
void VarDec2(Node* nd);
void FunDec1(Node* nd);
void FunDec2(Node* nd);
void VarList1(Node* nd);
void VarList2(Node* nd);
void ParamDec(Node* nd);
void Stmt1(Node* nd);
void DefList(Node* nd);
void Def(Node* nd);
void DecList1(Node* nd);
void DecList2(Node* nd);
void Dec(Node* nd);
void Exp1(Node* nd);
void Exp2(Node* nd);
void Exp3(Node* nd);
void Exp4(Node* nd);
void Exp5(Node* nd);
void Exp6(Node* nd);
void Exp7(Node* nd);
void Exp8(Node* nd);
void Exp9(Node* nd);
void Exp10(Node* nd);
void Exp11(Node* nd);
void Exp12(Node* nd);
void Args(Node* nd);
