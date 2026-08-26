%option noyywrap
%option yylineno
%{
#include <stdio.h>
void print(char*);
%}

/* Linha de Comentário */
COMENT     "~"([^~]|\n)*"~"

/* Definições */
RETURN      "return"
LETTER      [a-z]
DIGIT       [0-9]
LONG        -?{DIGIT}+
LONGLONG    -?{DIGIT}+\.{DIGIT}+
ESCAPE      \\.
PAPO        \"([^"\\\n]|{ESCAPE})*\"
VAR         [a-z][a-z0-9]+
FUNC        [F][B][a-z]+
NEWLINE     (\r\n|\r|\n)

/* Operadores */
MAIS        \+
MENOS       \-
MULT        \*
DIV         \/
EQUALS      ==
MENOR       \<
MAIOR       \>
ATRIBUICAO  <-

/* Pontuação */
VIRG        \,
PT          \.
PTVIRG      \;
ABREPAR     \(
FECHAPAR    \)
ABRECH      \{
FECHACH     \}
ABRECOL     \[
FECHACOL    \]

%%       

{COMENT}            { /* ignora comentário */ }
"long"            { printf("Palavra reservada LONG: %s (linha %d)\n", yytext, yylineno); }
"longlong"        { printf("Palavra reservada LONGLONG: %s (linha %d)\n", yytext, yylineno); }
"papo"            { printf("Palavra reservada PAPO: %s (linha %d)\n", yytext, yylineno); }
"return"          { printf("Palavra reservada RETURN: %s (linha %d)\n", yytext, yylineno); }
{LETTER}          { printf("LETRA: %s (linha %d)\n", yytext, yylineno); }
{DIGIT}           { printf("DIGITO: %s (linha %d)\n", yytext, yylineno); }
{LONG}            { printf("NUMERO INTEIRO: %s (linha %d)\n", yytext, yylineno); }
{LONGLONG}        { printf("NUMERO DECIMAL: %s (linha %d)\n", yytext, yylineno); }
{PAPO}            { printf("STRING: %s (linha %d)\n", yytext, yylineno); }
{VAR}             { printf("VARIAVEL: %s (linha %d)\n", yytext, yylineno); }
{FUNC}            { printf("FUNCAO: %s (linha %d)\n", yytext, yylineno); }
{MAIS}                { print("MAIS"); }
{MENOS}               { print("MENOS"); }
{MULT}                { print("MULTIPLICACAO"); }
{DIV}                 { print("DIVISAO"); }
{EQUALS}              { print("EQUALS"); }
{MENOR}               { print("MENOR"); }
{MAIOR}               { print("MAIOR"); }
{ATRIBUICAO}          { print("ATRIBUICAO"); }
{VIRG}            { print("VIRGULA"); }
{PT}              { print("PONTO"); }
{PTVIRG}          { print("PONTO E VIRGULA"); }
{ABREPAR}         { print("ABRE PARENTESES"); }
{FECHAPAR}        { print("FECHA PARENTESES"); }
{ABRECH}          { print("ABRE CHAVES"); }
{FECHACH}         { print("FECHA CHAVES"); }
{ABRECOL}         { print("ABRE COLCHETE"); }
{FECHACOL}        { print("FECHA COLCHETE"); }
{NEWLINE}           { printf("NOVA LINHA (linha %d)\n", yylineno); }
[ \t]               { /* ignorar espaços e tabs */ }
[ \t\r]+            { /* ignorar */ }
\"([^\"\n]*)\n      {fprintf(stderr, "ERRO LÉXICO: string não fechada (linha %d)\n", yylineno);}
.                   { printf("ERRO: caractere nao reconhecido %s (linha %d)\n", yytext, yylineno); }

%%

/* teste */
void print(char* token) {
printf("%s\t=>\t%s\n", token, yytext);
}

int main() {
    yylex();
    return 0;
}