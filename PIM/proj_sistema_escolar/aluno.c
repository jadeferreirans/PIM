/*
===========================================
 ARQUIVO: aluno.c
 RESPONSABILIDADE:
 - Manipular dados academicos do aluno.

 O QUE COLOCAR AQUI:
 - funcao pra cadastrar aluno
 - funcao pra listar dados aluno
===========================================
*/

#define MAX_STR 100
#define ARQUIVO_ALUNOS "data/alunos.txt"

#define ARQ_ALUNOS       "data/alunos.txt"
#define ARQ_NOTAS        "data/notas.txt"
#define ARQ_FALTAS       "data/faltas.txt"
#define ARQ_DISCIPLINAS  "data/disciplinas.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

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

    printf("\n=== Exclusão Completa do Aluno ===\n");
    printf("ID alvo: %d\n", id);

    // 1) Remover do alunos.txt
    {
        FILE *fa = fopen(ARQ_ALUNOS, "r");
        char temp_path[256];
        snprintf(temp_path, sizeof(temp_path), "data/temp_alunos.txt");
        FILE *tempA = fopen(temp_path, "w");

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
            // formato: id;nome;cpf;email;telefone;curso
            if (sscanf(linha, "%d;", &id_linha) == 1 && id_linha == id)
            {
                encontrado = 1;
                printf("Aluno encontrado: linha removida de alunos.txt\n");
                continue; // pula gravação
            }
            fputs(linha, tempA);
        }

        fclose(fa);
        fclose(tempA);

        if (!encontrado)
        {
            printf("Nenhum aluno com ID %d encontrado em alunos.txt\n", id);
            remove(temp_path);
            return;
        }

        remove(ARQ_ALUNOS);
        rename(temp_path, ARQ_ALUNOS);
    }

    // 2) Remover de notas.txt (formato: id_disciplina;id_aluno;nota1;...)
    {
        char temp_path[256];
        snprintf(temp_path, sizeof(temp_path), "data/temp_notas.txt");

        FILE *fn = fopen(ARQ_NOTAS, "r");
        FILE *tempN = fopen(temp_path, "w");

        if (fn && tempN)
        {
            while (fgets(linha, sizeof(linha), fn))
            {
                int id_disc, id_aluno;
                // tenta ler os dois primeiros inteiros
                if (sscanf(linha, "%d;%d;", &id_disc, &id_aluno) == 2)
                {
                    if (id_aluno == id)
                    {
                        // pula
                        continue;
                    }
                }
                // caso a linha esteja num formato inesperado, mantemos ela
                fputs(linha, tempN);
            }
            fclose(fn);
            fclose(tempN);

            remove(ARQ_NOTAS);
            rename(temp_path, ARQ_NOTAS);
            printf("Removidas notas (se existiam) do aluno %d em notas.txt\n", id);
        }
        else
        {
            if (fn) fclose(fn);
            if (tempN) fclose(tempN);
            // Não fatal: pode não existir arquivo de notas ainda
        }
    }

    // 3) Remover de faltas.txt (formato: id_disciplina;id_aluno;faltas)
    {
        char temp_path[256];
        snprintf(temp_path, sizeof(temp_path), "data/temp_faltas.txt");

        FILE *ff = fopen(ARQ_FALTAS, "r");
        FILE *tempF = fopen(temp_path, "w");

        if (ff && tempF)
        {
            while (fgets(linha, sizeof(linha), ff))
            {
                int id_disc, id_aluno;
                if (sscanf(linha, "%d;%d;", &id_disc, &id_aluno) == 2)
                {
                    if (id_aluno == id)
                    {
                        continue; // pula
                    }
                }
                fputs(linha, tempF);
            }
            fclose(ff);
            fclose(tempF);

            remove(ARQ_FALTAS);
            rename(temp_path, ARQ_FALTAS);
            printf("Removidas faltas (se existiam) do aluno %d em faltas.txt\n", id);
        }
        else
        {
            if (ff) fclose(ff);
            if (tempF) fclose(tempF);
        }
    }

    // 4) Remover aluno das disciplinas
    // formato esperado das linhas (exemplo): id_disc;id_prof;nome;1,2,3,4
    {
        char temp_path[256];
        snprintf(temp_path, sizeof(temp_path), "data/temp_disc.txt");

        FILE *fd = fopen(ARQ_DISCIPLINAS, "r");
        FILE *tempD = fopen(temp_path, "w");

        if (fd && tempD)
        {
            while (fgets(linha, sizeof(linha), fd))
            {
                // copiar linha para manipulacao
                char linha_copy[1024];
                strncpy(linha_copy, linha, sizeof(linha_copy));
                linha_copy[sizeof(linha_copy)-1] = '\0';

                // separar por ';' usando strtok (mais tolerante)
                char *tok;
                tok = strtok(linha_copy, ";\n");
                if (!tok) {
                    // linha malformada, copia direta
                    fputs(linha, tempD);
                    continue;
                }
                int id_disc = atoi(tok);

                tok = strtok(NULL, ";\n");
                if (!tok) { fputs(linha, tempD); continue; }
                int id_prof = atoi(tok);

                tok = strtok(NULL, ";\n");
                if (!tok) { fputs(linha, tempD); continue; }
                char nome_disc[256];
                strncpy(nome_disc, tok, sizeof(nome_disc));
                nome_disc[sizeof(nome_disc)-1] = '\0';

                tok = strtok(NULL, ";\n"); // lista de alunos (pode ser NULL)
                char nova_lista[1024] = "";
                if (tok && strlen(tok) > 0)
                {
                    // tok contém "1,2,3" por exemplo
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
                        }
                        sub = strtok(NULL, ",");
                    }
                }

                // escrever a linha reconstruída
                if (strlen(nova_lista) > 0)
                    fprintf(tempD, "%d;%d;%s;%s\n", id_disc, id_prof, nome_disc, nova_lista);
                else
                    // se não sobrou aluno, grava sem o campo de lista (ou com vazio)
                    fprintf(tempD, "%d;%d;%s;\n", id_disc, id_prof, nome_disc);
            }

            fclose(fd);
            fclose(tempD);

            remove(ARQ_DISCIPLINAS);
            rename(temp_path, ARQ_DISCIPLINAS);
            printf("Removido aluno %d das listas de disciplinas (se estava matriculado).\n", id);
        }
        else
        {
            if (fd) fclose(fd);
            if (tempD) fclose(tempD);
        }
    }

    printf("\nAluno excluído COMPLETAMENTE do sistema!\n");
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