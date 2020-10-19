#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

char look; /* O caracter lido "antecipadamente" (lookahead) */
char cur_class; /* classe atual lida por getclass */
char cur_sign;
char cur_type;

/* protótipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);

int main()

{

                init();

 

        while (look != EOF) {

                getclass();

                gettype();

                topdecl();

        }

 

                return 0;

}

/* inicialização do compilador */
void init()
{
    nextChar();
}

/* lê próximo caracter da entrada */
void nextChar()
{
    look = getchar();
}

/* exibe uma mensagem de erro formatada */
void error(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
}

/* exibe uma mensagem de erro formatada e sai */
void fatal(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);

    exit(1);
}

/* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputs(" expected!\n", stderr);

    exit(1);
}

/* verifica se entrada combina com o esperado */
void match(char c)
{
    if (look != c)
        expected("'%c'", c);
    nextChar();
}

/* recebe o nome de um identificador */
char getName()
{
    char name;

    if (!isalpha(look))
        expected("Name");
    name = toupper(look);
    nextChar();

    return name;
}

/* recebe um número inteiro */
char getNum()
{
    char num;

    if (!isdigit(look))
        expected("Integer");
    num = look;
    nextChar();

    return num;
}

/* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...)
{
    va_list args;

    putchar('\t');

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putchar('\n');
}


void getclass()

{

                if (look == 'a' || look == 'x' || look == 's') {

                                cur_class = look;

                                nextChar();

                                return 0;

                } else

                                cur_class = 'a';

}

void gettype()

{

                cur_type = ' ';

                if (look == 'u') {

                               cur_sign = 'u';

                               cur_type = 'i';

                               nextChar();

                } else {

                               cur_sign = 's';

                }

                if (look == 'i' || look == 'l' || look == 'c') {

                               cur_type = look;

                               nextChar();

                }

}

void topdecl()

{

        char name;

 

        name = getName();

        if (look == '(')

                dofunc(name);

        else

                dodata(name);

}

void dofunc(char name)

{

                match('(');

                match(')');

                match('{');

                match('}');

                if (cur_type == ' ')

                               cur_type = 'i';

                printf("Class: %c, Sign: %c, Type: %c, Function: %c\n",

                               cur_class, cur_sign, cur_type, name);

}

void dodata(char name)

{

                if (cur_type == ' ')

                               expected("Type declaration");

                for (;;) {

                               printf("Class: %c, Sign: %c, Type: %c, Data: %c\n",

                                               cur_class, cur_sign, cur_type, name);

                               if (look != ',')

                                               break;

                               match(',');

                               name = getName();

                }

                match(';');

}