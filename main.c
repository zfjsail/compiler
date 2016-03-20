#include "gen_obj_code.h"

extern Node* root;
extern lexright;
extern synright;
extern isTranslate;
int ano_num; //统计匿名结构体的数量
int enable_debug = 0;
int print_ic  = 0;
int t_cnt = 0; //临时变量
int v_cnt = 0; //变量
int l_cnt = 0; //label
FILE* f = NULL;
int main(int argc, char** argv) {
	if(argc <= 1) return 1;
	FILE* ff = fopen(argv[1], "r");
	if(!ff) {
		perror(argv[1]);
		return 1;
	}
	yyrestart(ff);
	if(argc == 4 && strcmp(argv[3],"-d") == 0){
		enable_debug = 1;
	}
	if(argc == 4 && strcmp(argv[3],"-ic") == 0){
		print_ic = 1;
	}
	if(!yyparse() && lexright && synright) {
		root->attr.blg_name = NULL;
		ano_num = 0;
		//traversal(root, 0); //语法分析中的遍历函数
		init_HT(); //初始化哈希表
		prepare_rw();
		sem_traversal(root); //语义分析遍历语法树
		trans_traversal(root);
		if(isTranslate) {
			//print_inter_codes(root);
			//dec_label();
			if(enable_debug){
				print_inter_codes(root);
				//out_obj_codes(stdout, root);
			}
			else{
				//print_inter_codes(root);
				f = fopen(argv[2], "wa+");
				out_obj_codes(root);
				fclose(f);
			}
		}
		else
		    printf("Cannot translate: Code contains variable or parameters of structure type.\n");
	}
	return 0;
}
