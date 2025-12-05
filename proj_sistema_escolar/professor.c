#include "professor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//
// ==================================================
//  CADASTRAR PROFESSOR
// ==================================================
//

void cadastrar_professor(int id_usuario)
{
    Professor p;
    p.id = id_usuario;

    printf("\n=== Cadastro de Dados do Professor ===\n");

    printf("Nome completo: ");
    fgets(p.nome, MAX_STR, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(p.cpf, MAX_STR, stdin);
    p.cpf[strcspn(p.cpf, "\n")] = '\0';

    printf("Email: ");
    fgets(p.email, MAX_STR, stdin);
    p.email[strcspn(p.email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(p.telefone, MAX_STR, stdin);
    p.telefone[strcspn(p.telefone, "\n")] = '\0';

    FILE *f = fopen(ARQ_PROFESSORES, "a");
    if (!f)
    {
        printf("Erro ao abrir arquivo de professores.\n");
        return;
    }

    fprintf(f, "%d;%s;%s;%s;%s\n",
            p.id, p.nome, p.cpf, p.email, p.telefone);

    fclose(f);

    printf("\nProfessor cadastrado com sucesso!\n");
}



//
// ==================================================
//  CONSULTAR PROFESSOR
// ==================================================
//

void consultar_professor(int id)
{
    FILE *f = fopen(ARQ_PROFESSORES, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo de professores.\n");
        return;
    }

    char linha[512];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        Professor p;

        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^\n]",
                   &p.id, p.nome, p.cpf, p.email, p.telefone) != 5)
            continue;

        if (p.id == id)
        {
            encontrado = 1;

            printf("\n=== Dados do Professor ===\n");
            printf("ID: %d\n", p.id);
            printf("Nome: %s\n", p.nome);
            printf("CPF: %s\n", p.cpf);
            printf("Email: %s\n", p.email);
            printf("Telefone: %s\n", p.telefone);
            printf("=========================\n");

            break;
        }
    }

    fclose(f);

    if (!encontrado)
        printf("Nenhum professor com ID %d encontrado.\n", id);
}



//
// ==================================================
//  LISTAR PROFESSORES
// ==================================================
//

void listar_professores()
{
    FILE *f = fopen(ARQ_PROFESSORES, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo de professores.\n");
        return;
    }

    char linha[256];
    Professor p;

    printf("\n=== LISTA DE PROFESSORES ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^\n]",
                   &p.id, p.nome, p.cpf, p.email, p.telefone) != 5)
            continue;

        printf("ID %-4d | %-20s | %s\n", p.id, p.nome, p.email);
    }

    fclose(f);
}



//
// ==================================================
//  EXCLUIR PROFESSOR
// ==================================================
//

void excluir_professor(int id)
{
    int encontrado = 0;
    char linha[512];

    FILE *fp = fopen(ARQ_PROFESSORES, "r");
    FILE *tempP = fopen("temp_prof.txt", "w");

    if (!fp || !tempP)
    {
        printf("Erro abrindo arquivos de professores.\n");
        if (fp) fclose(fp);
        if (tempP) fclose(tempP);
        return;
    }

    while (fgets(linha, sizeof(linha), fp))
    {
        Professor p;

        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^\n]",
                   &p.id, p.nome, p.cpf, p.email, p.telefone) != 5)
            continue;

        if (p.id == id)
        {
            encontrado = 1;
            printf("Professor encontrado: %s\n", p.nome);
            printf("Removendo registro de professores...\n");
            continue; // NÃO grava no arquivo temporário
        }

        fputs(linha, tempP);
    }

    fclose(fp);
    fclose(tempP);

    if (!encontrado)
    {
        printf("Nenhum professor com ID %d encontrado.\n", id);
        remove("temp_prof.txt");
        return;
    }

    remove(ARQ_PROFESSORES);
    rename("temp_prof.txt", ARQ_PROFESSORES);

    printf("\nProfessor excluido com sucesso!\n");
}



//
// ==================================================
//  EDITAR PROFESSOR
// ==================================================
//

void editar_professor(int id)
{
    FILE *f = fopen(ARQ_PROFESSORES, "r");
    FILE *temp = fopen("temp_prof.txt", "w");

    if (!f || !temp)
    {
        printf("Erro ao abrir arquivos de professores.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char linha[512];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        Professor p;
        char input[MAX_STR];

        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^\n]",
                   &p.id, p.nome, p.cpf, p.email, p.telefone) != 5)
        {
            fputs(linha, temp);
            continue;
        }

        if (p.id == id)
        {
            encontrado = 1;

            printf("\n=== Editando Professor (ID %d) ===\n", p.id);
            printf("Pressione ENTER para manter o valor atual.\n\n");

            // Nome
            printf("Nome atual: %s\nNovo nome: ", p.nome);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(p.nome, input);

            // CPF
            printf("CPF atual: %s\nNovo CPF: ", p.cpf);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(p.cpf, input);

            // Email
            printf("Email atual: %s\nNovo email: ", p.email);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(p.email, input);

            // Telefone
            printf("Telefone atual: %s\nNovo telefone: ", p.telefone);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(p.telefone, input);

            fprintf(temp, "%d;%s;%s;%s;%s\n",
                    p.id, p.nome, p.cpf, p.email, p.telefone);
        }
        else
        {
            fputs(linha, temp);
        }
    }

    fclose(f);
    fclose(temp);

    if (!encontrado)
    {
        printf("Nenhum professor com ID %d encontrado.\n", id);
        remove("temp_prof.txt");
        return;
    }

    remove(ARQ_PROFESSORES);
    rename("temp_prof.txt", ARQ_PROFESSORES);

    printf("\nProfessor atualizado com sucesso!\n");
}
