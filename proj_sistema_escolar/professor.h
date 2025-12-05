#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "usuario.h"   // garante acesso ao MAX_STR e ao ID do usuário

#define ARQ_PROFESSORES "data/professores.txt"

typedef struct {
    int id;                 // mesmo ID do usuário
    char nome[MAX_STR];
    char cpf[MAX_STR];
    char email[MAX_STR];
    char telefone[MAX_STR];
} Professor;


// ----------------------------------------------------
// CRUD
// ----------------------------------------------------
void cadastrar_professor(int id_usuario);
void consultar_professor(int id);
void listar_professores();
void editar_professor(int id);
void excluir_professor(int id);

#endif