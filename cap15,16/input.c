/* arquivo input.c */

#include <stdio.h>
#include "input.h"

#include "output.h"
#include "input.h"

char look; /* caracter "lookahead */

/* lê próximo caracter da entrada */

void nextChar()

{

                look = getchar();
}

/* inicializa o módulo de entrada */

void initInput()

{

                nextChar();

}
