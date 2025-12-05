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

#define MAX_STR 100
#define ARQ_PROFESSORES "data/professores.txt"

typedef struct {
    int id;                 // Igual ao id do usuário
    char nome[MAX_STR];
    char cpf[MAX_STR];
    char email[MAX_STR];
    char telefone[MAX_STR];
} Professor;

void cadastrar_professor(int id_usuario);
void consultar_professor(int id);
void listar_professores();
void editar_professor(int id);
void excluir_professor(int id);