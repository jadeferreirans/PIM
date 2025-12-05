/*
===========================================
 ARQUIVO: notas.h
 RESPONSABILIDADE:
 - Declarar funcoes e estruturas para
   armazenamento de notas e faltas.

 O QUE COLOCAR TER AQUI:
 - Funcoes:
   funcao pra lancar notas
   funcao pra editar notas
   funcao pra lancar faltas
   funcao pra editar faltas
   funcao pra consultar notas
   funcao pra consultar faltas
===========================================
*/

#define NOTAS_H

#define MAX_STR 100

// Caminhos dos arquivos
#define ARQ_NOTAS "data/notas.txt"
#define ARQ_FALTAS "data/faltas.txt"

// NOTAS
int carregar_notas(int id_disc, int id_aluno, float notas[4]);
void lancar_nota();
void editar_nota();
float obter_nota(int id_disciplina, int id_aluno);
void listar_notas_disciplina(int id_disciplina);
void consultar_notas_aluno(int id_aluno);

// FALTAS
int carregar_faltas(int id_disc, int id_aluno, int *faltas);
void lancar_falta();
void editar_falta();
int obter_faltas(int id_disciplina, int id_aluno);
void listar_faltas_disciplina(int id_disciplina);
void consultar_faltas_aluno(int id_aluno);