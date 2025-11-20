#define USUARIO_H

#define MAX_STR 100

typedef struct
{
	int id;
	int tipo; // 1 = Admin; 2 = Professor; 3 = Aluno; 
	char nome[MAX_STR];
	char username[MAX_STR];
	char senha[MAX_STR];
} Usuario;

/*Funcoes que serao implementadas no usuario.c
Funcoes relacionadas a usuario (login, cadastro, edicao, exclusao, consulta)*/

int login(Usuario *u); //funcao chamada ao iniciar o programa
void alterar_senha(Usuario *usuario_atual);

int gerar_id(); //deve ser acessado somente pelo admin
void cadastrar_usuario(); //deve ser acessado somente pelo admin

