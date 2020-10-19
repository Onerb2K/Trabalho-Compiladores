/* parser.c */

#include "scanner.h"

#include "codegen.h"

#include "parser.h"
#include "input.h"

/* analisa e traduz uma expressão */

/* analisa e traduz uma operação de soma */

/* coloca registrador primário na pilha */

void asmPush()

{

                emit("PUSH AX");

}

/* adiciona topo da pilha a reg. primário */

void asmPopAdd()

{

                emit("POP BX");

                emit("ADD AX, BX");

}

/* subtrari do topo da pilha o reg. primário */

void asmPopSub()

{

                emit("POP BX");

                emit("SUB AX, BX");

                asmNegate();

}

void add()

{

                match('+');

                asmPush();

                factor();

                asmPopAdd();

}

/* analisa e traduz uma operação de subtração */

void subtract()

{

                match('-');

                asmPush();

                factor();

                asmPopSub();

}

/* reconhece um operador multiplicativo */

int isMulOp(char c)

{

                return (c == '*' || c == '/' || c == '&');

}

/* analisa e traduz uma operação AND */

void boolAnd()

{

                match('&');

                asmPush();

                factor();

                asmPopAnd();

}

/* aplica AND com topo da pilha a reg. primário */

void asmPopAnd()

{

                emit("POP BX");

                emit("AND AX, BX");

}

/* analisa e traduz um fator com NOT opcional */

void notFactor()

{

                if (look == '!') {

                               match('!');

                               factor();

                               asmNot();

                } else

                               factor();

}

/* aplica NOT a reg. primário */

void asmNot()

{

        emit("NOT AX");

}


/* analisa e traduz um termo */

void term()

{

                factor();

                while (isMulOp(look)) {

                               switch (look) {

                                 case '*':

                                               multiply();

                                               break;

                                 case '/':

                                               divide();

                                               break;

                                 case '&':

                                               boolAnd();

                                               break;

                               }

                }

}

/* adiciona topo da pilha a reg. primário */

void asmPopMul()

{

                emit("POP BX");

                emit("IMUL BX");

}

/* subtrari do topo da pilha o reg. primário */

void asmPopDiv()

{

                emit("POP BX");

                emit("XCHG AX, BX");

                emit("CWD");

                emit("IDIV BX");

}

/* analisa e traduz um termo com um sinal opcional */

void signedTerm()

{

                char sign = look;

                if (isAddOp(look))

                               nextChar();

                term();

                if (sign == '-')

                               asmNegate();

}

/* reconhece um operador aditivo */

int isAddOp(char c)

{

                return (c == '+' || c == '-' || c == '|' || c == '~');

}

/* analisa e traduz uma operação OU booleana */

void boolOr()

{

                match('|');

                asmPush();

                term();

                asmPopOr();

}

/* aplica OU com topo da pilha a reg. primário */

void asmPopOr()

{

                emit("POP BX");

                emit("OR AX, BX");

}

/* aplica OU-exclusivo com topo da pilha a reg. primário */

void asmPopXor()

{

                emit("POP BX");

                emit("XOR AX, BX");

}

/* analisa e traduz uma operação OU-exclusivo booleana */

void boolXor()

{

                match('~');

                asmPush();

                term();

                asmPopXor();

}

/* analisa e traduz uma expressão */

void expression()

{

                signedTerm();

                while (isAddOp(look)) {

                               switch (look) {

                                 case '+':

                                               add();

                                               break;

                                 case '-':

                                               subtract();

                                               break;

                                 case '|':

                                               boolOr();

                                               break;

                                 case '~':

                                               boolXor();

                                               break;

                               }

                }

}

void asmNegate()

{

                emit("NEG AX");

}

void signedFactor()

{

                char sign = look;

                if (isAddOp(look))

                               nextChar();

                factor();

                if (sign == '-')

                               asmNegate();

}

/* armazena valor do registrador primário em variável */

void asmStoreVariable(char *name)

{

                emit("MOV [%s], AX", name);

}

/* analisa e traduz um comando de atribuição */

void assignment()

{

                char name[MAXNAME+1];

                getName(name);

                match('=');

                expression();

                asmStoreVariable(name);

}

/* analisa e traduz um fator matemático */

void factor()

{

                char name[MAXNAME+1], num[MAXNUM+1];

                if (look == '(') {

                               match('(');

                               expression();

                               match(')');

        } else if (isdigit(look)) {

                getNum(num);

                asmLoadConstant(num);

        } else if (isalpha(look)) {

                getName(name);

                asmLoadVariable(name);

        } else

                error("Unrecognized character: '%c'", look);

}