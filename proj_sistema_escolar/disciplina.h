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

typedef struct
{
    int id_disciplina;
    int id_professor;
} Professor;