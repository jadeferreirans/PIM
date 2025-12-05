#ifndef USUARIO_H
#define USUARIO_H

#define MAX_STR 100

typedef struct {
    int id;
    int tipo; // 1 - admin; 2 - professor; 3 - aluno
    char username[MAX_STR];
    char senha[MAX_STR];
} Usuario;

/*
 Funções do módulo usuario.c
*/

int login(Usuario *u); // chamada ao iniciar o programa
void alterar_senha(Usuario *usuario_atual);

int gerar_id(); 
void cadastrar_usuario_old();
void cadastrar_usuario();
void editar_usuario();
void excluir_usuario();
void consultar_usuario();

#endif