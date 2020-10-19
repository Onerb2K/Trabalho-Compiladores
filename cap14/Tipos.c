#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define SYMTBL_SZ 26

char symtbl[SYMTBL_SZ]; /* tabela de símbolos */

char look; /* O caracter lido "antecipadamente" (lookahead) */

/* protótipos */

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

char getnum();
void topdecls();
void unrecognized(char name);
void asm_allocvar(char name, char type);
void alloc(char name, char type);
void decl();

/* avisa a respeito de uma palavra-chave desconhecida */

void unrecognized(char name)

{

        fprintf(stderr, "Error: Unrecognized keyword %c\n", name);

        exit(1);

}

/* gera código para carregar variável de acordo com o tipo */

void asm_loadvar(char name, char type)

{

                switch (type) {

                  case 'b':

                                printf("\tmov al, %c\n", name);

                                printf("\tcbw\n");

                                printf("\tcwd\n");

                                break;

                  case 'w':

                                printf("\tmov ax, %c\n", name);

                                printf("\tcwd\n");

                                break;

                  case 'l':

                               printf("\tmov dx, word ptr [%c+2]\n", name);

                               printf("\tmov ax, word ptr [%c]\n", name);

                }

}

/* converte tipo origem para destino */

void asm_convert(char src, char dst)

{

                if (src == dst)

                               return;

                if (src == 'b')

                               printf("\tcbw\n");

                if (dst == 'l')

                               printf("\tcwd\n");

}



/* gera código para armazenamento de variável */

void asm_allocvar(char name, char type)

{

        int btype; /* tamanho em bytes */

        switch (type) {

          case 'b':

          case 'w':

                btype = type;

                break;

          case 'l':

                btype = 'd';

                break;

        }

        printf("%c d%c 0\n", name, btype);

}

/* aloca espaço de armazenamento para variável */

void alloc(char name, char type)

{

        addsymbol(name, type);

        asm_allocvar(name, type);

}

/* reconhece um tipo de variável válido */

int isvartype(char c)

{

                return (c == 'b' || c == 'w' || c == 'l');

}

/* avisa a respeito de um identificador que não é variável */

void notvar(char name)

{

                fprintf(stderr, "Error: %c is not a variable\n", name);

                exit(1);

}

/* retorna o tipo de um identificador */

char symtype(char name)

{

        return symtbl[name - 'A'];

}

/* pega o tipo da variável da tabela de símbolos */

char vartype(char name)

{

                char type;

                type = symtype(name);

                if (!isvartype(type))

                               notvar(name);

                return type;

}

/* carrega variável */

void loadvar(char name)

{

        asm_loadvar(name, vartype(name));

}

/* analisa e traduz uma expressão */

void expression()

{

                loadvar(getname());

}

/* analisa e traduz uma atribuição */

void assignment()

{

                char name;

                name = getname();

                match('=');

                expression();

                storevar(name);

}

/* analisa traduz um bloco de comandos */

void block()

{

                while (look != '.') {

                               assignment();

                               newline();

                }

}

/* gera código para armazenar variável de acordo com o tipo */

void asm_storevar(char name, char type)

{

                switch (type) {

                  case 'b':

                                printf("\tmov %c, al\n", name);

                                break;

                  case 'w':

                                printf("\tmov %c, ax\n", name);

                                break;

                  case 'l':

                               printf("\tmov word ptr [%c+2], dx\n", name);

                               printf("\tmov word ptr [%c], ax\n", name);

                }

}

/* armazena variável */

void storevar(char name)

{

        asm_storevar(name, vartype(name));

}

/* analiza e traduz a declaração de uma variável */

void decl()

{

        char type = look;

        nextchar();

        alloc(getname(), type);

}

/* analiza e traduz as declarações globais */

void topdecls()

{

        while (look != '.') {

                switch (look) {

                  case 'B':

                  case 'w':

                  case 'l':

                        decl();

                        break;

                  default:

                        unrecognized(look);

                        break;

                }

                newline();

        }

}

/* PROGRAMA PRINCIPAL */

int main()

{

                init();

        topdecls();

                match('B');

                newline();

                block();

        dumptable();

                return 0;

}

/* inicialização do compilador */

void init()

{

        int i;

        for (i = 0; i < SYMTBL_SZ; i++)

                symtbl[i] = '?';

        nextchar();

        skipwhite();

}

/* lê próximo caracter da entrada em lookahead */

void nextchar()

{

                look = getchar();

}

/* imprime mensagem de erro sem sair */

void error(char *s)

{

                fprintf(stderr, "Error: %s\n", s);

}

/* imprime mensagem de erro e sai */

void fatal(char *s)

{

                error(s);

                exit(1);

}

/* mensagem de erro para string esperada */

void expected(char *s)

{

                fprintf(stderr, "Error: %s expected\n", s);

                exit(1);

}


/* verifica se "name" consta na tabela de símbolos */

char intable(char name)

{

        return (symtbl[name - 'A'] != '?');

}

/* avisa a respeito de um identificador desconhecido */

void duplicated(char name)

{

                fprintf(stderr, "Error: Duplicated identifier %c\n", name);

                exit(1);

}

/* verifica se um identificador já foi declarado */

void checkdup(char name)

{

        if (intable(name))

                duplicated(name);

}

/* adiciona novo identificador à tabela de símbolos */

void addsymbol(char name, char type)

{

                checkdup(name);

        symtbl[name - 'A'] = type;

}

/* exibe a tabela de símbolos */

void dumptable()

{
        addsymbol('A', 'a');

                addsymbol('F', 'p');

                addsymbol('K', 'x');

        int i;

                printf("Symbol table dump:\n");

        for (i = 0; i < SYMTBL_SZ; i++)

                if (symtbl[i] != '?')

                               printf("%c = %c\n", i + 'A', symtbl[i]);

}

/* testa operadores de adição */

int isaddop(char c)

{

                return (c == '+' || c == '-');

}

/* testa operadores de multiplicação */

int ismulop(char c)

{

                return (c == '*' || c == '/');

}

/* testa operadores OU */

int isorop(char c)

{

                return (c == '|' || c == '~');

}

/* testa operadores relacionais */

int isrelop(char c)

{

                return (strchr("=#<>", c) != NULL);

}

/* pula caracteres em branco */

void skipwhite()

{

                while (look == ' ' || look == '\t')

                               nextchar();

}

/* reconhece uma quebra de linha */

void newline()

{

        if (look == '\n')

                nextchar();

}

/* verifica se look combina com caracter esperado */

void match(char c)

{

                char s[2];

                if (look == c)

                               nextchar();

                else {

                               s[0] = c; /* uma conversao rápida (e feia) */

                               s[1] = '\0'; /* de um caracter em string */

                               expected(s);

                }

        skipwhite();

}

/* analisa e traduz um nome (identificador ou palavra-chave) */

char getname()

{

                char name;

                if (!isalpha(look))

                               expected("Name");

                name = toupper(look);

                nextchar();

        skipwhite();

                return name;

}

/* analisa e traduz um número inteiro */

char getnum()

{

                char num;

                if (!isdigit(look))

                               expected("Integer");

                num = look;

                nextchar();

        skipwhite();

        return num;

}