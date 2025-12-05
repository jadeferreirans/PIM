#define USUARIO_H

#define MAX_STR 100

typedef struct {
    int id;
    int tipo; //1 - admin; 2 - professor;  3 - aluno;
    char username[100];
    char senha[100];
} Usuario;

/*Funcoes que serao implementadas no usuario.c
Funcoes relacionadas a usuario (login, cadastro, edicao, exclusao, consulta)*/

int login(Usuario *u); //funcao chamada ao iniciar o programa
void alterar_senha(Usuario *usuario_atual);

int gerar_id(); //deve ser acessado somente pelo admin
void cadastrar_usuario_old(); //deve ser acessado somente pelo admin
void cadastrar_usuario();
void editar_usuario();
void excluir_usuario();
void consultar_usuario();

