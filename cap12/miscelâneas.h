#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SYMTBL_SZ 30

/* protótipos */


long getnum();
char loadnum(long val);;
void asm_convert(char src, char dst);
char loadvar(char name);
void asm_loadconst(long val, char type);
char term();
char unop();
void asm_push(char type);
char subtract(char type);
char add(char type);
void asm_pop(char type);
void asm_swap(char type);
char asm_sametype(char t1, char t2, int ord_matters);
char asm_popsub(char t1, char t2);
char asm_popadd(char t1, char t2);
char divide(char type);
char multiply(char type);
char factor();
char asm_popmul(char t1, char t2);
char asm_popdiv(char t1, char t2);
void init();
void nextchar();
void error(char *s);
void fatal(char *s);
void expected(char *s);
void dumptable();
int isaddop(char c);
int ismulop(char c);
int isorop(char c);
int isrelop(char c);
void skipwhite();
void newline();
void match(char c);
char getname();
void addsymbol(char name, char type);
void checkdup(char name);
void duplicated(char name);
char intable(char name);
char symtype(char name);
void topdecls();
void decl();
void asm_allocvar(char name, char type);
void unrecognized(char name);
void alloc(char name, char type);
void asm_loadvar(char name, char type);
int isvartype(char c);
void notvar(char name);
char vartype(char name);
void asm_storevar(char name, char type);
void storevar(char name, char srctype);
void block();
void assignment();
char expression();

