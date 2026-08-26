%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token VAR LONG LONGLONG RETURN
%token MAIS MENOS MULT DIV
%token EQUALS MENOR MAIOR ATRIBUICAO
%token ABREPAR FECHAPAR ABRECH FECHACH PTVIRG
%token IF WHILE ELSE
%token LONG_T LONG_LONG_T

%start S

%%

S : Prog ;

Prog : ListaDecl ListaCmd ;

ListaDecl : Decl ListaDecl
          | /* vazio */ ;

Decl : Tipo VAR PTVIRG ;

Tipo : LONG_T
     | LONG_LONG_T ;

ListaCmd : Cmd ListaCmd
         | /* vazio */ ;

Cmd : CmdAtrib
    | CmdIf
    | CmdWhile ;

CmdAtrib : VAR ATRIBUICAO Expr PTVIRG ;

CmdIf : IF ABREPAR Expr FECHAPAR ABRECH ListaCmd FECHACH
      | IF ABREPAR Expr FECHAPAR ABRECH ListaCmd FECHACH ELSE ABRECH ListaCmd FECHACH ;

CmdWhile : WHILE ABREPAR Expr FECHAPAR ABRECH ListaCmd FECHACH ;

Expr : Expr MAIS Termo
     | Expr MENOS Termo
     | Termo ;

Termo : Termo MULT Fator
      | Termo DIV Fator
      | Fator ;

Fator : VAR
      | LONG
      | LONGLONG
      | ABREPAR Expr FECHAPAR ;

%%

void yyerror(const char *s) {
    printf("Erro sintático: %s\n", s);
}
int main(){
    return yyparse();
}