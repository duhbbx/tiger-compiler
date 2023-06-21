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

extern int yyparse(void);
extern A_exp absyn_root;
extern void pr_exp(FILE *out, A_exp v, int d);

/* parse source file fname;
   return abstract syntax data structure */
A_exp parse(string fname) {
    EM_reset(fname);
    if (yyparse() == 0) /* parsing worked */
        return absyn_root;
    else
        return NULL;
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
