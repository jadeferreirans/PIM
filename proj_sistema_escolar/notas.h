#ifndef NOTAS_H
#define NOTAS_H

#include "usuario.h"
#include "disciplina.h"

// Arquivos do sistema
#define ARQ_NOTAS  "data/notas.txt"
#define ARQ_FALTAS "data/faltas.txt"


// =======================================================
//  NOTAS
// =======================================================

int carregar_notas(int id_disc, int id_aluno, float notas[4]);

void lancar_nota(int id_professor);
void editar_nota(int id_professor);

float obter_nota(int id_disciplina, int id_aluno);

void listar_notas_disciplina(int id_disciplina);
void consultar_notas_aluno(int id_aluno);


// =======================================================
//  FALTAS
// =======================================================

int carregar_faltas(int id_disc, int id_aluno, int *faltas);

void lancar_falta(int id_professor);
void editar_falta(int id_professor);

int obter_faltas(int id_disciplina, int id_aluno);

void listar_faltas_disciplina(int id_disciplina);
void consultar_faltas_aluno(int id_aluno);


#endif