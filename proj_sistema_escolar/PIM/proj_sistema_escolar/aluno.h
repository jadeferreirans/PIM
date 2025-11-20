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

#define MAX_STR 100

typedef struct
{
    int id;
} Aluno;

void cadastrar_aluno(); //A FAZER