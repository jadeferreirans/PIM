#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "usuario.h"        // para MAX_STR
#include "professor.h"      // garante consistência com ID de professor

#define ARQ_DISCIPLINAS "data/disciplinas.txt"
#define MAX_ALUNOS 50

typedef struct {
    int id;
    char nome[MAX_STR];
    int id_professor;      // ID do professor responsável

    int alunos[MAX_ALUNOS];   // IDs dos alunos matriculados
    int total_alunos;
} Disciplina;


// ----------------------------------------------------
// Funções principais (CRUD)
// ----------------------------------------------------
int gerar_id_disciplina();

void cadastrar_disciplina();
void listar_disciplinas();
void editar_disciplina();
void excluir_disciplina();

void listar_disciplinas_professor(int id_professor);
void listar_disciplinas_aluno(int id_aluno);

// Função opcional, caso utilize para sobrescrever arquivo
void salvar_disciplina(Disciplina d);


#endif