#ifndef ALUNO_H
#define ALUNO_H

#include "usuario.h"   // garante acesso ao ID do usuário, se necessário

#define ARQ_ALUNOS "data/alunos.txt"

typedef struct {
    int id;                  // mesmo ID do usuario
    char nome[MAX_STR];
    char cpf[MAX_STR];
    char email[MAX_STR];
    char telefone[MAX_STR];
    char curso[MAX_STR];
} Aluno;


// ----------------------------------------------------
// CRUD
// ----------------------------------------------------
void cadastrar_aluno(int id_usuario);
void editar_aluno(int id);
void excluir_aluno(int id);
void consultar_aluno(int id);


// ----------------------------------------------------
// Funções auxiliares
// ----------------------------------------------------
int carregar_aluno_por_id(int id, Aluno *a);


#endif