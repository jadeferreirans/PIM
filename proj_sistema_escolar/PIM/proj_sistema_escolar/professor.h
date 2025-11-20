/*
===========================================
 ARQUIVO: professor.h
 RESPONSABILIDADE:
 - Definir a struct Professor (dados academicos (exceto o que ja tem em usuarios)).

 O QUE COLOCAR AQUI:
 - struct Professor
 - Declaracao das funcoes de professor.c
===========================================
*/

#define PROFESSOR_H

#define MAX_STR 100

typedef struct
{
    int id;
} Professor;

void cadastrar_professor(); //A FAZER