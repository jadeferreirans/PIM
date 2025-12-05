/*Funcoes relacionadas a usuario (login, cadastro, edicao, exclusao, consulta)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usuario.h"
#include "aluno.h"
#include "professor.h"

#define MAX_STR 100
#define LOCAL_ARQUIVO_USUARIOS "data/usuarios.txt"

int login(Usuario *u)
{
    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    if(!f)
    {
        printf("Erro: usuario.txt nao encontrado\n");
        return 0;
    }

    char username[MAX_STR], senha[MAX_STR];

    printf("\n=== LOGIN ===\n");

    printf("Username: ");
    fgets(username, MAX_STR, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha, MAX_STR, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    Usuario temp;
    char linha[300];

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%[^;];%[^;\n]",
                   &temp.id, &temp.tipo, temp.username, temp.senha) == 4)
        {
            if(strcmp(username, temp.username) == 0 &&
               strcmp(senha, temp.senha) == 0)
            {
                *u = temp;
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

void alterar_senha(Usuario *usuario_atual)
{
    char entrada[MAX_STR], nova_senha[MAX_STR];

    printf("\n=== Alterar Senha ===\n");

    printf("Confirme sua senha atual: ");
    fgets(entrada, MAX_STR, stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    if(strcmp(entrada, usuario_atual->senha) != 0)
    {
        printf("Senha incorreta.\n");
        return;
    }

    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    FILE *temp = fopen("temp.txt", "w");

    if(!f || !temp)
    {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    printf("Digite a nova senha: ");
    fgets(nova_senha, MAX_STR, stdin);
    nova_senha[strcspn(nova_senha, "\n")] = '\0';

    char linha[300];
    Usuario u;

    while (fgets(linha, sizeof(linha), f))
    {
        sscanf(linha, "%d;%d;%[^;];%[^;\n]",
               &u.id, &u.tipo, u.username, u.senha);

        if(u.id == usuario_atual->id)
        {
            strcpy(u.senha, nova_senha);
            fprintf(temp, "%d;%d;%s;%s\n",
                u.id, u.tipo, u.username, u.senha);
        }
        else
        {
            fputs(linha, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(LOCAL_ARQUIVO_USUARIOS);
    rename("temp.txt", LOCAL_ARQUIVO_USUARIOS);

    strcpy(usuario_atual->senha, nova_senha);
    printf("\nSenha alterada com sucesso!\n");
}

int gerar_id()//deve ser acessado somente pelo admin ADICIONAR FORMATACAO NO ID!!!!!
{
	FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    int id, maior_id = 0;
    char linha[300];
    
    if(!f)
	{
    	printf("Erro: usuario.txt nao encontrado no gerar id\n");
        return 0;
	}

    while(fgets(linha, sizeof(linha), f))
	{
    	sscanf(linha, "%d;", &id);
    	if(id > maior_id)
    	{
    		maior_id = id;
		}
	}
	
    fclose(f);
    return maior_id + 1;
}

void cadastrar_usuario()
{
    Usuario novo;
    novo.id = gerar_id();

    printf("\n=== Cadastro de Usuario ===\n");
    printf("(1 = Admin, 2 = Professor, 3 = Aluno)\nTipo: ");

    char buffer[8];
    fgets(buffer, sizeof(buffer), stdin);
    novo.tipo = atoi(buffer);

    if(novo.tipo < 1 || novo.tipo > 3)
    {
        printf("Tipo invalido!\n");
        return;
    }

    // ==== USERNAME ====
    printf("Defina o username: ");
    fgets(novo.username, MAX_STR, stdin);
    novo.username[strcspn(novo.username, "\n")] = '\0';

    // ==== SENHA ====
    printf("Defina a senha: ");
    fgets(novo.senha, MAX_STR, stdin);
    novo.senha[strcspn(novo.senha, "\n")] = '\0';

    // ---- SALVAR apenas dados de login ----
    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "a");
    if(!f)
    {
        printf("Erro ao abrir usuarios.txt!\n");
        return;
    }

    fprintf(f, "%d;%d;%s;%s\n",
            novo.id, novo.tipo, novo.username, novo.senha);

    fclose(f);

    printf("\nUsuario criado com sucesso! (ID: %d)\n", novo.id);

    // ---- CHAMAR MÓDULO ESPECÍFICO ----
    switch(novo.tipo)
    {
        /*case 1:
            cadastrar_admin(novo.id);
            break;*/

        case 2:
            cadastrar_professor(novo.id);
            break;

        case 3:
            cadastrar_aluno(novo.id);
            break;
    }
}

void editar_usuario()
{
    int id_alvo;
    char buffer[32];

    printf("\n=== Editar Usuario ===\n");
    printf("Digite o ID do usuario: ");

    fgets(buffer, sizeof(buffer), stdin);
    id_alvo = atoi(buffer);

    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    FILE *temp = fopen("temp.txt", "w");

    if(!f || !temp)
    {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    char linha[300];
    int encontrado = 0;
    Usuario u;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%[^;];%[^;\n]",
                   &u.id, &u.tipo, u.username, u.senha) != 4)
            continue;

        if (u.id == id_alvo)
        {
            encontrado = 1;

            printf("\n--- Editando Usuario (ID %d) ---\n", u.id);
            printf("Pressione ENTER para manter o valor atual.\n\n");

            char input[MAX_STR];

            // ------------------ USERNAME ------------------
            printf("Username atual: %s\nNovo username: ", u.username);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if(strlen(input) > 0)
                strcpy(u.username, input);

            // ------------------- SENHA --------------------
            printf("Senha atual: %s\nNova senha: ", u.senha);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if(strlen(input) > 0)
                strcpy(u.senha, input);

            fprintf(temp, "%d;%d;%s;%s\n",
                    u.id, u.tipo, u.username, u.senha);
        }
        else
        {
            fputs(linha, temp);
        }
    }

    fclose(f);
    fclose(temp);

    if(!encontrado)
    {
        printf("\nUsuario com ID %d nao encontrado!\n", id_alvo);
        remove("temp.txt");
        return;
    }

    remove(LOCAL_ARQUIVO_USUARIOS);
    rename("temp.txt", LOCAL_ARQUIVO_USUARIOS);

    printf("\nUsuario atualizado com sucesso!\n");
}

void excluir_usuario()
{
    int alvo_id;
    char buffer[32];

    printf("\n=== Excluir Usuario ===\n");
    printf("Digite o ID do usuario que deseja excluir: ");

    fgets(buffer, sizeof(buffer), stdin);
    alvo_id = atoi(buffer);

    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    FILE *temp = fopen("temp.txt", "w");

    if(!f || !temp)
    {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    char linha[300];
    Usuario u;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%[^;];%[^;\n]",
                   &u.id, &u.tipo, u.username, u.senha) != 4)
            continue;

        if (u.id == alvo_id)
        {
            encontrado = 1;

            printf("\nUsuario encontrado: %s (ID %d)\n", u.username, u.id);
            printf("Tem certeza que deseja excluir? (s/n): ");

            char resp[8];
            fgets(resp, sizeof(resp), stdin);

            if (resp[0] != 's' && resp[0] != 'S')
            {
                printf("Operacao cancelada.\n");
                fclose(f);
                fclose(temp);
                remove("temp.txt");
                return;
            }

            // Não grava → exclui
            continue;
        }

        fputs(linha, temp);
    }

    fclose(f);
    fclose(temp);

    if(!encontrado)
    {
        printf("\nNenhum usuario com ID %d encontrado.\n", alvo_id);
        remove("temp.txt");
        return;
    }

    remove(LOCAL_ARQUIVO_USUARIOS);
    rename("temp.txt", LOCAL_ARQUIVO_USUARIOS);
    
    switch(u.tipo)
    {
    	case 2:
    		excluir_professor(alvo_id); break;
    	
    	case 3:
    		excluir_aluno(alvo_id); break;
	}

    printf("\nUsuario excluido com sucesso!\n");
}

void consultar_usuario()
{
    int alvo_id;
    char buffer[32];

    printf("\n=== Consultar Usuario ===\n");
    printf("Digite o ID do usuario: ");

    fgets(buffer, sizeof(buffer), stdin);
    alvo_id = atoi(buffer);

    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    if(!f)
    {
        printf("Erro ao abrir arquivo de usuarios.\n");
        return;
    }

    char linha[300];
    Usuario u;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%[^;];%[^;\n]",
                   &u.id, &u.tipo, u.username, u.senha) != 4)
            continue;

        if (u.id == alvo_id)
        {
            encontrado = 1;

            printf("\n=== Dados do Usuario ===\n");
            printf("ID: %d\n", u.id);

            switch(u.tipo)
            {
                case 1: printf("Tipo: Administrador\n"); break;
                case 2: printf("Tipo: Professor\n"); break;
                case 3: printf("Tipo: Aluno\n"); break;
            }

            printf("Username: %s\n", u.username);
            printf("Senha: %s\n", u.senha);

            printf("\n* Dados pessoais estao no modulo especifico. *\n");
            printf("=========================\n");

            break;
        }
    }

    fclose(f);

    if(!encontrado)
        printf("\nNenhum usuario com ID %d encontrado.\n", alvo_id);
}


