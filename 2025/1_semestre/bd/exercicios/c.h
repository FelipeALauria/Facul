#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct {
    char *nome;
    int idade;
    char *cpf;
    char *doenca;
    int numero_conveio;
    int numero_sala_encaminhamento;
    char *sintomas;  
} paciente;

typedef struct {
    char *nome;
    int numero_sala;
    int crm;
    char *especialidade;
} medico;

typedef struct {
    char *nome;
    int numero_sala;
    int corem;
} enfermeiro;

typedef struct{
    struct paciente *paciente;
    struct enfermeiro *enfermeiro;
} triagem;

typedef struct {
    struct paciente *paciente;
    struct medico *medico;
    char *data_consulta;
    char *hora_consulta;
    char *observacoes;
    int numero_sala_consulta;
    char *receita_medica;
    int exame;
} consulta;

typedef struct {
    struct paciente *paciente;
    struct enfermeiro *enfermeiro;
    char *data_exame;
    char *resultado_exame;
} exame;

typedef struct {
    struct paciente *paciente;
    int posicao;
} fila_triagem;

typedef struct {
    struct paciente *paciente;
    struct triagem *triagem;
    int posicao;
} fila_consulta;

typedef struct {
    struct paciente *paciente;
    int posicao;
} fila_exame;

typedef struct {
    struct medico *medico;
    int ocupado;
} lista_enfermeiros;

typedef struct {
    struct medico *medico;
    int ocupado;
} lista_medicos;

bool cadastrar_paciente(paciente *, char*, int, char*, char*, int, int, char*);
bool cadastrar_medico(medico *, char*, int, int, char*);
bool cadastrar_enfermeiro(enfermeiro *, char*, int, int);
triagem *realizar_triagem(paciente *, enfermeiro *);
consulta *realizar_consulta(triagem, medico *);
exame *realizar_exame(consulta, enfermeiro *);
bool cria_lista_medicos(lista_medicos *, int);
bool cria_lista_enfermeiros(lista_enfermeiros *, int);
bool adicionar_paciente_fila_triagem(fila_triagem *, paciente *);
bool adicionar_paciente_fila_consulta(fila_consulta *, paciente *, triagem *);
