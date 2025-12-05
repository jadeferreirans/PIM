/*
===========================================
 ARQUIVO: aluno.h
 RESPONSABILIDADE:
 - Definir a struct Aluno (dados academicos (exceto o que ja tem em usuarios)).

 O QUE COLOCAR AQUI:
 - struct Aluno
 - Declaracao das funcoes de aluno.c
===========================================
*/

#define ALUNO_H

#define ARQ_ALUNOS "data/alunos.txt"
#define MAX_STR 100

typedef struct {
    int id;                 
    char nome[MAX_STR];
    char cpf[MAX_STR];
    char email[MAX_STR];
    char telefone[MAX_STR];
    char curso[MAX_STR];
} Aluno;

// CRUD
void cadastrar_aluno(int id_usuario);
void editar_aluno(int id);
void excluir_aluno(int id);
void consultar_aluno(int id);

// Funções auxiliares
int carregar_aluno_por_id(int id, Aluno *a);