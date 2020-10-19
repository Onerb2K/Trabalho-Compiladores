Funcionalidade dos arquivos do compilador:
Berço.c: Ele é o programa que tem a estrutura base para a construção das fases do compilador de diferentes formas, e é utilizado em diversos capítulos como programa de base para a inserção das rotinas que serão utilizadas.
Expressões.c: É o programa que é produzido no capítulo 2 e 3 com base no berço para a introdução do uso das expressões aritméticas no compilador.
Interpretador.c: É um programa que demonstra como funciona um interpretador funcional em prática para comparar as diferenças entre um compilador e interpretador.
Estruturas_de_controle.c: É  um programa que demonstra a análise e tradução de construções de controle, como comandos IF, WHILE, entre outros no compilador.
Expressões_booleanas.c: É um programa que demonstra o funcionamento das expressões booleanas em um compilador e que também inclui o uso das expressões aritméticas simultaneamente.
Bool.h: biblioteca com as rotinas utilizadas pelo programa main, expressões booleanas.
AnáliseLéxica.c: é um programa que demonstra a fase de análise léxica no compilador. Com o uso de um analisador léxico funcional.
TopDown.c: é o programa que demonstra o processo de compilação top-down em prática, comparado com a maioria que anteriormente estava sendo feito em bottom-up.
Small.c: é introduzido um compilador em Small C onde os comandos do pré-processador são sempre processados pelo próprio compilador.
Tiny.c: É um programa que representa um subjconjunto da linguagem KISS numa abordagem top-down.
AnáliseLéxica2: é um programa onde são feitas melhorias no analisador léxico do compilador, e é introduzido o ;.
Miscelâneas.c: Neste programa são inseridas funções comuns que outras linguagens populares possuem, como o ;, comentários, embelezamento de código etc.
Miscelâneas.h: É a bliblioteca com as funções do programa main, miscelâneas.c.
Procedimentos.c: Esse programa traz a possibilidade de utilizar mais procedimentos na programação, como a passagem de parâmetros, e trata a passagem por referência e por valor.
ProcedimentosRef.c: É feita uma cópia do programa de procedimentos para demonstrar apenas a passagem por referência e variáveis locais.
Tipos.c: é um programa que demonstra o funcionamento dos tipos de dados simples e pré definidos em um compilador com tokens de um caracter.
Teste.c: É o programa principal onde são testados os módulos demonstrados no capítulo 15 e 16
Errors.c: É o módulo responsável pelos erros.
Errors.h: Biblioteca com as rotinas de errors.c.
Codegen.c: Módulo com o código responsável pelas rotinas de geração de código assembly.
Codegen.h: Biblioteca com as rotinas de codegen.c.
Parser.c: É o módulo com o código da implementação da sintaxe da linguagem.
Parser.h: Biblioteca com as rotinas de parser.c.
Output.c: Módulo com as rotinas que produzem a geração da saída.
Output.h: Biblioteca com as rotinas de output.c.
Input.c: Módulo que trata da entrada do compilador.
Input.h: Biblioteca com as funções de input.c
Scanner1.c: Rotinas do analisador léxico com apenas um caracter.
Scanner1.h: Biblioteca com as funções de scanner1.c.
Scanner.c: Rotinas do analisador léxico multi-caracter.
Scanner.h: Biblioteca com as funções de scanner.c.


