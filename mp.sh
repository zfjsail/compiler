flex lexical.l
bison -d syntax.y
gcc main.c syntax.tab.c semantic.c inter_code.c gen_obj_code.c -lfl -ly -w -o parser
#./parser ../Test/3_3.cmm > ics.ir
./parser ../Test/d2.cmm out.s
cp ./parser ../Test
#spim -file out.s
