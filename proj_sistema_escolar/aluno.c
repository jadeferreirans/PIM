#include "aluno.h"
#include "notas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ==================================================
//  Carregar aluno por ID
// ==================================================
//

int carregar_aluno_por_id(int id, Aluno *a)
{
    FILE *f = fopen(ARQ_ALUNOS, "r");
    if (!f) return 0;

    char linha[512];
    Aluno temp;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%[^\n]",
                   &temp.id,
                   temp.nome,
                   temp.cpf,
                   temp.email,
                   temp.telefone,
                   temp.curso) == 6)
        {
            if (temp.id == id)
            {
                *a = temp;
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

//
// ==================================================
//  CADASTRAR ALUNO
// ==================================================
//

void cadastrar_aluno(int id_usuario)
{
    FILE *f = fopen(ARQ_ALUNOS, "a");
    if (!f)
    {
        printf("Erro ao abrir alunos.txt\n");
        return;
    }

    Aluno a;
    a.id = id_usuario;

    printf("\n=== Cadastro de Dados do Aluno ===\n");

    printf("Nome completo: ");
    fgets(a.nome, MAX_STR, stdin);
    a.nome[strcspn(a.nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(a.cpf, MAX_STR, stdin);
    a.cpf[strcspn(a.cpf, "\n")] = '\0';

    printf("Email: ");
    fgets(a.email, MAX_STR, stdin);
    a.email[strcspn(a.email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(a.telefone, MAX_STR, stdin);
    a.telefone[strcspn(a.telefone, "\n")] = '\0';

    printf("Curso: ");
    fgets(a.curso, MAX_STR, stdin);
    a.curso[strcspn(a.curso, "\n")] = '\0';

    fprintf(f, "%d;%s;%s;%s;%s;%s\n",
            a.id, a.nome, a.cpf, a.email, a.telefone, a.curso);

    fclose(f);

    printf("\nAluno cadastrado com sucesso! (ID %d)\n", a.id);
}

//
// ==================================================
//  EDITAR ALUNO
// ==================================================
//

void editar_aluno(int id)
{
    printf("\n=== Editar Aluno ===\n");

    FILE *f = fopen(ARQ_ALUNOS, "r");
    FILE *temp = fopen("temp_alunos.txt", "w");

    if (!f || !temp)
    {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    char linha[512];
    Aluno a;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%[^\n]",
                   &a.id, a.nome, a.cpf, a.email, a.telefone, a.curso) != 6)
            continue;

        if (a.id == id)
        {
            encontrado = 1;

            printf("\nPressione ENTER para manter o valor atual.\n");

            char input[MAX_STR];

            // NOME
            printf("Nome atual: %s\nNovo nome: ", a.nome);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(a.nome, input);

            // CPF
            printf("CPF atual: %s\nNovo CPF: ", a.cpf);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(a.cpf, input);

            // EMAIL
            printf("Email atual: %s\nNovo email: ", a.email);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(a.email, input);

            // TELEFONE
            printf("Telefone atual: %s\nNovo telefone: ", a.telefone);
            fgets(input, MAX_STR, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strcpy(a.telefone, input);

            fprintf(temp, "%d;%s;%s;%s;%s;%s\n",
                    a.id, a.nome, a.cpf, a.email, a.telefone, a.curso);
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
        printf("\nAluno nao encontrado.\n");
        remove("temp_alunos.txt");
        return;
    }

    remove(ARQ_ALUNOS);
    rename("temp_alunos.txt", ARQ_ALUNOS);

    printf("\nAluno atualizado com sucesso!\n");
}

//
// ==================================================
//  EXCLUIR ALUNO
// ==================================================
//

void excluir_aluno(int id)
{
    char linha[1024];
    int encontrado = 0;

    printf("\n=== Exclusao Completa do Aluno ===\n");
    printf("ID alvo: %d\n", id);

    // ----------------------------------------------
    // 1) Remover do alunos.txt
    // ----------------------------------------------
    {
        FILE *fa = fopen(ARQ_ALUNOS, "r");
        FILE *tempA = fopen("data/temp_alunos.txt", "w");

        if (!fa || !tempA)
        {
            printf("Erro ao abrir arquivos de alunos!\n");
            if (fa) fclose(fa);
            if (tempA) fclose(tempA);
            return;
        }

        while (fgets(linha, sizeof(linha), fa))
        {
            int id_linha;
            if (sscanf(linha, "%d;", &id_linha) == 1 && id_linha == id)
            {
                encontrado = 1;
                printf("Aluno encontrado e removido de alunos.txt\n");
                continue;
            }
            fputs(linha, tempA);
        }

        fclose(fa);
        fclose(tempA);

        if (!encontrado)
        {
            printf("Nenhum aluno com ID %d encontrado no arquivo.\n", id);
            remove("data/temp_alunos.txt");
            return;
        }

        remove(ARQ_ALUNOS);
        rename("data/temp_alunos.txt", ARQ_ALUNOS);
    }

    // ----------------------------------------------
    // 2) Remover notas do aluno
    // ----------------------------------------------
    // (idem ao seu código – apenas organizado)

    // NOTAS
    {
        FILE *fn = fopen(ARQ_NOTAS, "r");
        FILE *tempN = fopen("data/temp_notas.txt", "w");

        if (fn && tempN)
        {
            while (fgets(linha, sizeof(linha), fn))
            {
                int id_disc, id_aluno;
                if (sscanf(linha, "%d;%d;", &id_disc, &id_aluno) == 2 &&
                    id_aluno == id)
                    continue;

                fputs(linha, tempN);
            }

            fclose(fn);
            fclose(tempN);

            remove(ARQ_NOTAS);
            rename("data/temp_notas.txt", ARQ_NOTAS);
        }
        else
        {
            if (fn) fclose(fn);
            if (tempN) fclose(tempN);
        }
    }

    // ----------------------------------------------
    // 3) Remover faltas do aluno
    // ----------------------------------------------
    {
        FILE *ff = fopen(ARQ_FALTAS, "r");
        FILE *tempF = fopen("data/temp_faltas.txt", "w");

        if (ff && tempF)
        {
            while (fgets(linha, sizeof(linha), ff))
            {
                int id_disc, id_aluno;
                if (sscanf(linha, "%d;%d;", &id_disc, &id_aluno) == 2 &&
                    id_aluno == id)
                    continue;

                fputs(linha, tempF);
            }

            fclose(ff);
            fclose(tempF);

            remove(ARQ_FALTAS);
            rename("data/temp_faltas.txt", ARQ_FALTAS);
        }
        else
        {
            if (ff) fclose(ff);
            if (tempF) fclose(tempF);
        }
    }

    // ----------------------------------------------
    // 4) Remover aluno das disciplinas
    // ----------------------------------------------
    {
        FILE *fd = fopen(ARQ_DISCIPLINAS, "r");
        FILE *tempD = fopen("data/temp_disc.txt", "w");

        if (fd && tempD)
        {
            while (fgets(linha, sizeof(linha), fd))
            {
                char linha_copy[1024];
                strncpy(linha_copy, linha, sizeof(linha_copy));
                linha_copy[sizeof(linha_copy) - 1] = '\0';

                char *tok = strtok(linha_copy, ";\n");
                if (!tok) { fputs(linha, tempD); continue; }

                int id_disc = atoi(tok);

                // nome da disciplina
                tok = strtok(NULL, ";\n");
                if (!tok) { fputs(linha, tempD); continue; }
                char nome_disc[256];
                strncpy(nome_disc, tok, sizeof(nome_disc));

                // id do professor
                tok = strtok(NULL, ";\n");
                if (!tok) { fputs(linha, tempD); continue; }
                int id_prof = atoi(tok);

                // total de alunos
                tok = strtok(NULL, ";\n");
                if (!tok) { fputs(linha, tempD); continue; }
                int total_original = atoi(tok);

                // lista de alunos (pode ser NULL)
                tok = strtok(NULL, ";\n");

                char nova_lista[1024] = "";
                int novo_total = 0;

                if (tok && strlen(tok) > 0)
                {
                    char *sub = strtok(tok, ",");
                    int first = 1;

                    while (sub)
                    {
                        int aluno_id = atoi(sub);

                        if (aluno_id != id)
                        {
                            if (!first) strcat(nova_lista, ",");
                            strcat(nova_lista, sub);
                            first = 0;
                            novo_total++;
                        }

                        sub = strtok(NULL, ",");
                    }
                }

                // grava linha corrigida no arquivo temp
                if (novo_total > 0)
                    fprintf(tempD, "%d;%s;%d;%d;%s\n",
                            id_disc, nome_disc, id_prof, novo_total, nova_lista);
                else
                    fprintf(tempD, "%d;%s;%d;0;\n",
                            id_disc, nome_disc, id_prof);
            }

            fclose(fd);
            fclose(tempD);

            remove(ARQ_DISCIPLINAS);
            rename("data/temp_disc.txt", ARQ_DISCIPLINAS);
        }
        else
        {
            if (fd) fclose(fd);
            if (tempD) fclose(tempD);
        }
    }

    printf("\nAluno excluido COMPLETAMENTE do sistema!\n");
}

//
// ==================================================
//  CONSULTAR ALUNO
// ==================================================
//

void consultar_aluno(int id)
{
    Aluno a;
    if (!carregar_aluno_por_id(id, &a))
    {
        printf("\nAluno nao encontrado.\n");
        return;
    }

    printf("\n=== Dados do Aluno ===\n");
    printf("ID: %d\n", a.id);
    printf("Nome: %s\n", a.nome);
    printf("CPF: %s\n", a.cpf);
    printf("Email: %s\n", a.email);
    printf("Telefone: %s\n", a.telefone);
    printf("Curso: %s\n", a.curso);
    printf("=========================\n");
}