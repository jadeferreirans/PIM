#include "menus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disciplina.h"
#include "professor.h"
#include "aluno.h"
#include "notas.h"

//
// ==================================================
//  FUNCOES AUXILIARES
// ==================================================
//

void limpar_tela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar()
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

//
// ==================================================
//  MENU ADMINISTRADOR
// ==================================================
//

void menu_admin(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU ADMINISTRADOR ======\n");
        printf("[1] - Gerenciamento de Usuarios\n");
        printf("[2] - Gerenciamento de Disciplinas\n");
        printf("[3] - Alterar minha Senha\n");
        printf("[0] - Logout\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: limpar_tela(); menu_usuarios_admin(usuario_atual); break;
            case 2: limpar_tela(); menu_disciplinas_admin(usuario_atual); break;
            case 3: alterar_senha(&usuario_atual); pausar(); break;
            case 0: limpar_tela(); break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}

//
// ==================================================
//  MENU USUARIOS (ADMIN)
// ==================================================
//

void menu_usuarios_admin(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU USUARIOS ======\n");
        printf("[1] - Cadastrar Usuario\n");
        printf("[2] - Editar Usuario\n");
        printf("[3] - Excluir Usuario\n");
        printf("[4] - Consultar Usuario\n");
        printf("[0] - Voltar\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: cadastrar_usuario(); pausar(); break;
            case 2: editar_usuario(); pausar(); break;
            case 3: excluir_usuario(); pausar(); break;
            case 4: consultar_usuario(); pausar(); break;
            case 0: limpar_tela(); break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}

//
// ==================================================
//  MENU DISCIPLINAS (ADMIN)
// ==================================================
//

void menu_disciplinas_admin(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU DISCIPLINAS ======\n");
        printf("[1] - Listar Disciplinas\n");
        printf("[2] - Cadastrar Disciplina\n");
        printf("[3] - Editar Disciplina\n");
        printf("[4] - Excluir Disciplina\n");
        printf("[0] - Voltar\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: listar_disciplinas(); pausar(); break;
            case 2: cadastrar_disciplina(); pausar(); break;
            case 3: editar_disciplina(); pausar(); break;
            case 4: excluir_disciplina(); pausar(); break;
            case 0: limpar_tela(); break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}

//
// ==================================================
//  MENU PRINCIPAL DO PROFESSOR
// ==================================================
//

void menu_professor(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU PROFESSOR ======\n");
        printf("[1] - Gerenciamento de Disciplinas\n");
        printf("[2] - Gerenciamento de Dados Pessoais\n");
        printf("[0] - Logout\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: menu_disciplinas_professor(usuario_atual); break;
            case 2: menu_dados_professor(usuario_atual); break;
            case 0: limpar_tela(); break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}

//
// ==================================================
//  MENU DISCIPLINAS (PROFESSOR)
// ==================================================
//

void menu_disciplinas_professor(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU DISCIPLINAS DO PROFESSOR ======\n");
        printf("[1] - Listar minhas disciplinas\n");
        printf("[2] - Lancar Notas\n");
        printf("[3] - Editar Notas\n");
        printf("[4] - Lancar Faltas\n");
        printf("[5] - Editar Faltas\n");
        printf("[0] - Voltar\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: listar_disciplinas_professor(usuario_atual.id); pausar(); break;
            case 2: lancar_nota(usuario_atual.id); pausar(); break;
            case 3: editar_nota(usuario_atual.id); pausar(); break;
            case 4: lancar_falta(usuario_atual.id); pausar(); break;
            case 5: editar_falta(usuario_atual.id); pausar(); break;
            case 0: break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}

//
// ==================================================
//  MENU DADOS DO PROFESSOR
// ==================================================
//

void menu_dados_professor(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU DADOS DO PROFESSOR ======\n");
        printf("[1] - Exibir meus dados\n");
        printf("[2] - Alterar meus dados\n");
        printf("[3] - Alterar minha Senha\n");
        printf("[0] - Voltar\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
            case 1: consultar_professor(usuario_atual.id); pausar(); break;
            case 2: editar_professor(usuario_atual.id); pausar(); break;
            case 3: alterar_senha(&usuario_atual); pausar(); break;
            case 0: break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}

//
// ==================================================
//  MENU DO ALUNO
// ==================================================
//

void menu_aluno(Usuario usuario_atual)
{
    char opcao_str[8];
    int opcao;

    do {
        limpar_tela();
        printf("Logado como: %s (ID %d)\n\n", usuario_atual.username, usuario_atual.id);

        printf("====== MENU ALUNO ======\n");
        printf("[1] - Consultar Minhas Disciplinas\n");
        printf("[2] - Consultar Frequencia\n");
        printf("[3] - Consultar Notas\n");
        printf("[4] - Consultar Dados Pessoais\n");
        printf("[5] - Editar Dados Pessoais\n");
        printf("[6] - Alterar minha Senha\n");
        printf("[0] - Logout\n");
        printf("\n> ");

        fgets(opcao_str, sizeof(opcao_str), stdin);
        opcao = atoi(opcao_str);

        switch(opcao)
        {
        	case 1: listar_disciplinas_aluno(usuario_atual.id); pausar(); break;
            case 2: consultar_faltas_aluno(usuario_atual.id); pausar(); break;
            case 3: consultar_notas_aluno(usuario_atual.id); pausar(); break;
            case 4: consultar_aluno(usuario_atual.id); pausar(); break;
            case 5: editar_aluno(usuario_atual.id); pausar(); break;
            case 6: alterar_senha(&usuario_atual); pausar(); break;
            case 0: limpar_tela(); break;
            default: printf("Opcao invalida!\n"); pausar();
        }

    } while (opcao != 0);
}


//
// ==================================================
//  MENU INICIAL
// ==================================================
//
void menu_login()
{
    limpar_tela();

    printf("============================================\n");
    printf("              SISTEMA ACADEMICO             \n");
    printf("============================================\n\n");
    printf("Bem Vindo!\n\n");
	printf("%-10s - Login\n", "[ENTER]");
	printf("%-10s - Sair\n",  "[0]");
    printf("\n--------------------------------------------\n");
    printf("> ");
}