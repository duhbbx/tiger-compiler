#include "symbol.h"
#include "table.h"
#include "util.h"
#include <stdio.h>
#include <string.h>


/**
 * 符号表用链表来记录
 */
struct S_symbol_ {
    string name;
    S_symbol next;
};


/**
 * 创建一个符号 
 */
static S_symbol mksymbol(string name, S_symbol next) {
    S_symbol s = checked_malloc(sizeof(*s));
    s->name = name;
    s->next = next;
    return s;
}

#define SIZE 109 /* should be prime */

/**
 * 哈希表
 */
static S_symbol hashtable[SIZE];

/**
 * 计算字符串的哈希值
 */
static unsigned int hash(char *s0) {
    unsigned int h = 0;
    char *s;
    for (s = s0; *s; s++)
        h = h * 65599 + *s;
    return h;
}

/**
 * 判断两个字符串是否相等
 */
static int streq(string a, string b) { return !strcmp(a, b); }


/**
 * 根据名字从符号表中获取符号
 */
S_symbol S_Symbol(string name) {
    int index = hash(name) % SIZE;
    S_symbol syms = hashtable[index], sym;
    for (sym = syms; sym; sym = sym->next)
        if (streq(sym->name, name))
            return sym;
    sym = mksymbol(name, syms);
    hashtable[index] = sym;
    return sym;
}

string S_name(S_symbol sym) { return sym->name; }

S_table S_empty(void) { return TAB_empty(); }

void S_enter(S_table t, S_symbol sym, void *value) { TAB_enter(t, sym, value); }

void *S_look(S_table t, S_symbol sym) { return TAB_look(t, sym); }

static struct S_symbol_ marksym = {"<mark>", 0};

void S_beginScope(S_table t) { S_enter(t, &marksym, NULL); }

void S_endScope(S_table t) {
    S_symbol s;
    do
        s = TAB_pop(t);
    while (s != &marksym);
}

void S_dump(S_table t, void (*show)(S_symbol sym, void *binding)) {
    TAB_dump(t, (void (*)(void *, void *))show);
}
