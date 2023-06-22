/*
 * parse.c - Parse source file.
 */

#include "parsetest.h"
#include "absyn.h"
#include "errormsg.h"
#include "symbol.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

// bison或者yacc生成的解析函数
extern int yyparse(void);

// 抽象语法树的根节点
extern A_exp absyn_root;

// 打印表达式
extern void pr_exp(FILE *out, A_exp v, int d);

/**
 * parse source file fname;
 * return abstract syntax data structure
 */
A_exp parse(string fname) {
    EM_reset(fname);
    /* parsing worked，yyparse是bison生成的，取决于.y文件的动作 */
    if (yyparse() == 0) {
        return absyn_root;
    } else {
        return NULL;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: a.out filename\n");
        exit(1);
    }
    pr_exp(stdout, parse(argv[1]), 0);
    printf("\n");
    return 0;
}
