//Arquivo de interface (cabeçalho)

//Tipo No
typedef struct no No;
//----------------------------------


//Protótipo das funções (operações)
//----------------------------------
No *criavazia (void);

No *cria (char c, No *esq, No *dir);

No *libera (No *t);

int vazia (No *t);

int pertence (No *t, char c);

void imprime (No *t);
//----------------------------------

