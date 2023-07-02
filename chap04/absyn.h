/*
 * absyn.h - Abstract Syntax Header (Chapter 4)
 *
 * All types and functions declared in this header file begin with "A_"
 * Linked list types end with "..list"
 */

/* Type Definitions */

#ifndef _AB_SYN_H_
#define _AB_SYN_H_

#include "symbol.h"
#include "util.h"

typedef int A_pos;

typedef struct A_var_ *A_var;
typedef struct A_exp_ *A_exp;
typedef struct A_dec_ *A_dec;
typedef struct A_ty_ *A_ty;

typedef struct A_decList_ *A_decList;
typedef struct A_expList_ *A_expList;
typedef struct A_field_ *A_field;
typedef struct A_fieldList_ *A_fieldList;
typedef struct A_fundec_ *A_fundec;
typedef struct A_fundecList_ *A_fundecList;
typedef struct A_namety_ *A_namety;
typedef struct A_nametyList_ *A_nametyList;
typedef struct A_efield_ *A_efield;
typedef struct A_efieldList_ *A_efieldList;

/**
 * 操作符的枚举
 */
typedef enum {
    A_plusOp,   // 加
    A_minusOp,  // 减
    A_timesOp,  // 乘
    A_divideOp, // 除
    A_eqOp,     // 相等
    A_neqOp,    // 不相等
    A_ltOp,     // 小于
    A_leOp,     // 小于等于
    A_gtOp,     // 大于
    A_geOp      // 大于等于
} A_oper;

struct A_var_ {

    // 枚举可以嵌入在struct中吗？
    // 变量的类型
    enum { A_simpleVar, A_fieldVar, A_subscriptVar } kind;


    // 变量的位置，A_pos是int类型，为啥不提示行号和列号？
    A_pos pos;


    // 联合
    union {

        // 简单
        S_symbol simple;

        // 字段
        struct {
            A_var var;
            S_symbol sym;
        } field;

        // 下标
        struct {
            A_var var;
            A_exp exp;
        } subscript;
    } u;
};

/**
 * 表达式 
 */
struct A_exp_ {


    // 表达式的类型
    enum {
        A_varExp,
        A_nilExp,
        A_intExp,
        A_stringExp,
        A_callExp,
        A_opExp,
        A_recordExp,
        A_seqExp,
        A_assignExp,
        A_ifExp,
        A_whileExp,
        A_forExp,
        A_breakExp,
        A_letExp,
        A_arrayExp
    } kind;

    // 位置
    A_pos pos;


    // 联合
    union {

        // 指向变量的指针
        A_var var;


        /* nil; - needs only the pos */
        int intt;
        
        
        // 字符串
        string stringg;

        // 函数调用
        struct {
            S_symbol func;
            A_expList args;
        } call;


        // 操作符
        struct {
            A_oper oper;
            A_exp left;
            A_exp right;
        } op;

        // 记录
        struct {
            S_symbol typ;
            A_efieldList fields;
        } record;

        // 多个表达式
        A_expList seq;


        // 赋值
        struct {
            A_var var;
            A_exp exp;
        } assign;

        // if语句
        struct {
            A_exp test, then, elsee;
        } iff; /* elsee is optional */

        // while语句
        struct {
            A_exp test, body;
        } whilee;

        // for循环语句
        struct {
            S_symbol var;
            A_exp lo, hi, body;
            bool escape;
        } forr;
        /* breakk; - need only the pos */

        // let语句
        struct {
            A_decList decs;
            A_exp body;
        } let;

        // 数组
        struct {
            S_symbol typ;
            A_exp size, init;
        } array;
    } u;
};


// 定义语句
struct A_dec_ {

    // 定义的类型
    enum { A_functionDec, A_varDec, A_typeDec } kind;


    // 位置
    A_pos pos;


    // 联合
    union {

        // 函数定义
        A_fundecList function;
        /* escape may change after the initial declaration */

        // 变量
        struct {
            S_symbol var;
            S_symbol typ;
            A_exp init;
            bool escape;
        } var;

        // 类型定义
        A_nametyList type;
    } u;
};

// 类型
struct A_ty_ {

    // 有哪几种类型
    enum { A_nameTy, A_recordTy, A_arrayTy } kind;

    // 位置
    A_pos pos;

    // 实际的类型名称
    union {
        S_symbol name;
        A_fieldList record;
        S_symbol array;
    } u;
};

/* Linked lists and nodes of lists */


// 字段类型
struct A_field_ {

    // 名称和类型
    S_symbol name, typ;

    // 位置
    A_pos pos;

    // 是否逃逸
    bool escape;
};

// 字段列表
struct A_fieldList_ {
    A_field head;
    A_fieldList tail;
};

// 表达式列表
struct A_expList_ {

    // 头部
    A_exp head;

    尾部
    A_expList tail;
};

// 函数定义
struct A_fundec_ {

    // 位置
    A_pos pos;

    // 符号
    S_symbol name;

    // 参数字段的列表
    A_fieldList params;


    // 结果
    S_symbol result;

    // 函数体
    A_exp body;
};


// 函数定义的列表
struct A_fundecList_ {
    A_fundec head;
    A_fundecList tail;
};

// 声明列表
struct A_decList_ {
    A_dec head;
    A_decList tail;
};

// 命名类型
struct A_namety_ {
    S_symbol name;
    A_ty ty;
};

// 命名类型的列表
struct A_nametyList_ {
    A_namety head;
    A_nametyList tail;
};

// 表达式字段？
struct A_efield_ {
    S_symbol name;
    A_exp exp;
};


// 表达式字段列表
struct A_efieldList_ {
    A_efield head;
    A_efieldList tail;
};

/* Function Prototypes */
A_var A_SimpleVar(A_pos pos, S_symbol sym);
A_var A_FieldVar(A_pos pos, A_var var, S_symbol sym);
A_var A_SubscriptVar(A_pos pos, A_var var, A_exp exp);
A_exp A_VarExp(A_pos pos, A_var var);
A_exp A_NilExp(A_pos pos);
A_exp A_IntExp(A_pos pos, int i);
A_exp A_StringExp(A_pos pos, string s);
A_exp A_CallExp(A_pos pos, S_symbol func, A_expList args);
A_exp A_OpExp(A_pos pos, A_oper oper, A_exp left, A_exp right);
A_exp A_RecordExp(A_pos pos, S_symbol typ, A_efieldList fields);
A_exp A_SeqExp(A_pos pos, A_expList seq);
A_exp A_AssignExp(A_pos pos, A_var var, A_exp exp);
A_exp A_IfExp(A_pos pos, A_exp test, A_exp then, A_exp elsee);
A_exp A_WhileExp(A_pos pos, A_exp test, A_exp body);
A_exp A_ForExp(A_pos pos, S_symbol var, A_exp lo, A_exp hi, A_exp body);
A_exp A_BreakExp(A_pos pos);
A_exp A_LetExp(A_pos pos, A_decList decs, A_exp body);
A_exp A_ArrayExp(A_pos pos, S_symbol typ, A_exp size, A_exp init);
A_dec A_FunctionDec(A_pos pos, A_fundecList function);
A_dec A_VarDec(A_pos pos, S_symbol var, S_symbol typ, A_exp init);
A_dec A_TypeDec(A_pos pos, A_nametyList type);
A_ty A_NameTy(A_pos pos, S_symbol name);
A_ty A_RecordTy(A_pos pos, A_fieldList record);
A_ty A_ArrayTy(A_pos pos, S_symbol array);
A_field A_Field(A_pos pos, S_symbol name, S_symbol typ);
A_fieldList A_FieldList(A_field head, A_fieldList tail);
A_expList A_ExpList(A_exp head, A_expList tail);
A_fundec A_Fundec(A_pos pos, S_symbol name, A_fieldList params, S_symbol result,
                  A_exp body);
A_fundecList A_FundecList(A_fundec head, A_fundecList tail);
A_decList A_DecList(A_dec head, A_decList tail);
A_namety A_Namety(S_symbol name, A_ty ty);
A_nametyList A_NametyList(A_namety head, A_nametyList tail);
A_efield A_Efield(S_symbol name, A_exp exp);
A_efieldList A_EfieldList(A_efield head, A_efieldList tail);

#endif