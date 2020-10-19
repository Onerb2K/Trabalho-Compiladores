/* codegen.c */

#include "output.h"

#include "codegen.h"

#include "input.h"

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

void expression()

{

                signedFactor();

                while (isAddOp(look)) {

                               switch (look) {

                                 case '+':

                                               add();

                                               break;

                                 case '-':

                                               subtract();

                                               break;

                               }

                }

}

/* carrega uma constante no registrador primário */

void asmLoadConstant(char *s)

{

                emit("MOV AX, %s", s);

}
/* carrega uma variável no registrador primário */

void asmLoadVariable(char *s)

{

                emit("MOV AX, [%s]", s);

}

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

/* analisa e traduz uma operação de subtração */

void subtract()

{

                match('-');

                asmPush();

                factor();

                asmPopSub();

}

/* analisa e traduz uma operação de soma */

void add()

{

                match('+');

                asmPush();

                factor();

                asmPopAdd();

}

/* analisa e traduz uma expressão */

void expression()

{

                signedFactor();

                while (isAddOp(look)) {

                               switch (look) {

                                 case '+':

                                               add();

                                               break;

                                 case '-':

                                               subtract();

                                               break;

                               }

                }

}