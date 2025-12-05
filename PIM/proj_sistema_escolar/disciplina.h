/*
===========================================
 ARQUIVO: disciplina.h
 RESPONSABILIDADE:
 - Definir estrutura de disciplinas.

 O QUE COLOCAR AQUI:
 - struct Disciplina (id_disciplina, nome, id_professor)
 - Prototipos para disciplina.c

 Cada disciplina deve ser atribuida a um professor.
===========================================
*/
#define DISCIPLINA_H

#define MAX_STR 100
#define MAX_ALUNOS 50

typedef struct {
    int id;
    char nome[MAX_STR];
    int id_professor;  // ID do professor responsável

    int alunos[MAX_ALUNOS]; // IDs dos alunos matriculados
    int total_alunos;
} Disciplina;

int gerar_id_disciplina();

void cadastrar_disciplina();
void listar_disciplinas();
void excluir_disciplina();
void editar_disciplina();
void salvar_disciplina(Disciplina d);
void listar_disciplinas_professor(int id_professor);