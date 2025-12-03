#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usuario.h"
#include "disciplina.h"
#include "professor.h"
#include "aluno.h"
#include "notas.h"

// Protótipos dos menus
void menu_admin(Usuario usuario_atual);
void menu_usuarios();
void menu_disciplinas();
void menu_professor(Usuario usuario_atual);
void menu_dados_professor(Usuario usuario_atual);
void menu_disciplinas_professor(Usuario usuario_atual);
void menu_aluno(Usuario usuario_atual);

int main()
{	
	Usuario usuario_atual;
	char entrada[8];
	
	while(1) //loop da sessao
	{
        printf("\n=== SISTEMA ACADEMICO ===\n");
        printf("Pressione ENTER para Login\n");
        printf("Insira 0 para sair\n");
        printf("> ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        
        if (strcmp(entrada, "0") == 0)
        {
            printf("\nEncerrando o sistema...\n");
            break;
        }
        
		if (login(&usuario_atual))
		{
			printf("\nBem-vindo, %s!\n", usuario_atual.username);
    	
    		switch (usuario_atual.tipo)//seleciona o menu a ser exibido com base no tipo logado
    		{
    			case 1:
    				menu_admin(usuario_atual); break;
    	
    			case 2:
    				menu_professor(usuario_atual); break;
    	
    			case 3:
    				menu_aluno(usuario_atual); break;
    		
    			default:
    				printf("Tipo invalido (ATENCAO)");
		}
    	} else printf("\nFalha no login\n");
	}
	
	return 0;
}

void menu_admin(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU ADMINISTRADOR ===\n");
        printf("1 - Gerenciamento de Usuarios\n");
        printf("2 - Gerenciamento de Disciplinas\n");
        printf("3 - Alterar minha senha\n");
        printf("0 - Logout\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: menu_usuarios(); break;
            case 2: menu_disciplinas(); break;
            case 3: alterar_senha(&usuario_atual); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Opção invalida!\n");
        }

    } while (opcao != 0);
}

void menu_usuarios()
{
	char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU USUARIOS ===\n");
		printf("1 - Cadastrar Usuario\n");
        printf("2 - Editar Usuario\n");
        printf("3 - Excluir Usuario\n");
        printf("4 - Consultar Usuario\n");
        printf("0 - Voltar\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: cadastrar_usuario(); break;
            case 2: editar_usuario(); break;
            case 3: excluir_usuario(); break;
            case 4: consultar_usuario(); break;
            case 0: printf("\n"); break;
            default: printf("Opção invalida!\n");
        }

    } while (opcao != 0);
}

void menu_disciplinas()
{
	char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU DISCIPLINAS ===\n");
		printf("1 - Listar Disciplinas\n");
        printf("2 - Cadastrar Disciplina\n");
        printf("3 - Editar Disciplina\n");
        printf("4 - Excluir Disciplina\n");
        printf("0 - Voltar\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: listar_disciplinas(); break;
            case 2: cadastrar_disciplina(); break;
            case 3: editar_disciplina(); break;
            case 4: excluir_disciplina(); break;
            case 0: printf("\n"); break;
            default: printf("Opção invalida!\n");
        }

    } while (opcao != 0);
}

void menu_professor(Usuario usuario_atual)
{
	char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU PROFESSOR ===\n");
        printf("1 - Gerenciamento de Disciplinas\n");
        printf("2 - Gerenciamento de Dados Pessoais\n");
        printf("0 - Logout\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: menu_disciplinas_professor(usuario_atual); break;
            case 2: menu_dados_professor(usuario_atual); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Opção invalida!\n");
        }
    } while (opcao != 0);
}

void menu_disciplinas_professor(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU DISCIPLINAS ===\n");
        printf("1 - Listar minhas disciplinas\n");
        printf("2 - Incluir Notas\n");
        printf("3 - Editar Notas\n");
        printf("4 - Incluir Faltas\n");
        printf("5 - Editar Faltas\n");
        printf("0 - Voltar\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: listar_disciplinas_professor(usuario_atual.id); break;
            case 2: lancar_nota(); break;
            case 3: editar_nota(); break;
            case 4: lancar_falta(); break;
            case 5: editar_falta(); break;
            case 0: printf("\n"); break;
            default: printf("Opção invalida!\n");
        }
    } while (opcao != 0);
}

void menu_dados_professor(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU DADOS PESSOAIS ===\n");
        printf("1 - Exibir meus dados\n");
        printf("2 - Alterar meus dados\n");
        printf("3 - Alterar minha Senha\n");
        printf("0 - Voltar\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: consultar_professor(usuario_atual.id); break;
            case 2: editar_professor(usuario_atual.id); break;
            case 3: alterar_senha(&usuario_atual); break;
            case 0: printf("\n"); break;
            default: printf("Opção invalida!\n");
        }
    } while (opcao != 0);
}

void menu_aluno(Usuario usuario_atual)
{
	char opcao_str[8];
    int opcao;

    do {
        printf("\n=== MENU ALUNO ===\n");
        printf("1 - Consultar Frequencia\n");
        printf("2 - Consultar Notas\n");
        printf("3 - Consultar Dados Pessoais\n");
        printf("4 - Editar Dados Pessoais\n");
        printf("5 - Alterar minha Senha\n");
        printf("0 - Logout\n");
        printf("\nEscolha: ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: consultar_faltas_aluno(usuario_atual.id); break;
            case 2: consultar_notas_aluno(usuario_atual.id); break;
            case 3: consultar_aluno(usuario_atual.id); break;
            case 4: editar_aluno(usuario_atual.id); break;
            case 5: alterar_senha(&usuario_atual); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Opção invalida!\n");
        }
    } while (opcao != 0);
}