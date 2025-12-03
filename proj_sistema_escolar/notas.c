/*
===========================================
 ARQUIVO: notas.c
 RESPONSABILIDADE:
 - Registrar e modificar notas e faltas.

 O QUE VAI COLOCAR AQUI:
 - Lancamento e edicao de notas
 - Lancamento e edicao de faltas
 - Consultar notas e faltas para aluno ou professor
===========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notas.h"

//
// =====================  FUNÇÕES DE NOTAS  =====================
//

int carregar_notas(int id_disc, int id_aluno, float notas[4]) {
    FILE *f = fopen(ARQ_NOTAS, "r");
    if (!f) return 0;

    char linha[200];
    int d, a;
    float n1, n2, n3, n4;

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                   &d, &a, &n1, &n2, &n3, &n4) == 6) {

            if (d == id_disc && a == id_aluno) {
                notas[0] = n1;
                notas[1] = n2;
                notas[2] = n3;
                notas[3] = n4;
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0; 
}

void lancar_nota() {
    int id_disc, id_aluno, indice;
    float notas[4] = { -1, -1, -1, -1 };

    printf("\n=== Lancar Nota ===\n");
    printf("ID da disciplina: ");
    scanf("%d", &id_disc); getchar();

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();

    carregar_notas(id_disc, id_aluno, notas);

    printf("\nQual nota alterar? (1 a 4): ");
    scanf("%d", &indice); getchar();
    indice--;

    if (indice < 0 || indice > 3) {
        printf("Indice invalido.\n");
        return;
    }

    printf("Digite a nova nota: ");
    scanf("%f", &notas[indice]); getchar();

    char temp_path[100];
    snprintf(temp_path, sizeof(temp_path), "data/temp_notas.txt");

    FILE *orig = fopen(ARQ_NOTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    if (!temp) { printf("Erro ao abrir arquivo temporario.\n"); return; }

    char linha[200];
    int d, a;
    float n1, n2, n3, n4;
    int atualizado = 0;

    if (orig) {
        while (fgets(linha, sizeof(linha), orig)) {
            if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                       &d, &a, &n1, &n2, &n3, &n4) == 6
                && d == id_disc && a == id_aluno) {

                fprintf(temp, "%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                        id_disc, id_aluno,
                        notas[0], notas[1], notas[2], notas[3]);

                atualizado = 1;
            }
            else {
                fputs(linha, temp);
            }
        }
        fclose(orig);
    }

    if (!atualizado) {
        fprintf(temp, "%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                id_disc, id_aluno,
                notas[0], notas[1], notas[2], notas[3]);
    }

    fclose(temp);

    remove(ARQ_NOTAS);
    rename(temp_path, ARQ_NOTAS);

    printf("\nNota registrada com sucesso!\n");
}


void editar_nota() {
    int id_disc, id_aluno, indice;
    float notas[4];

    printf("\n=== Editar Nota ===\n");
    printf("ID da disciplina: ");
    scanf("%d", &id_disc); getchar();

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();

    if (!carregar_notas(id_disc, id_aluno, notas)) {
        printf("Registro nao encontrado.\n");
        return;
    }

    printf("\nNotas atuais:\n");
    for (int i = 0; i < 4; i++)
        printf("Nota %d: %.2f\n", i + 1, notas[i]);

    printf("\nQual nota deseja alterar (1 a 4)? ");
    scanf("%d", &indice); getchar();
    indice--;

    if (indice < 0 || indice > 3) {
        printf("Indice invalido.\n");
        return;
    }

    printf("Nova nota: ");
    scanf("%f", &notas[indice]); getchar();

    char temp_path[100];
    snprintf(temp_path, sizeof(temp_path), "data/temp_notas.txt");

    FILE *orig = fopen(ARQ_NOTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    char linha[200];
    int d, a;
    float n1, n2, n3, n4;

    while (fgets(linha, sizeof(linha), orig)) {
        if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                   &d, &a, &n1, &n2, &n3, &n4) == 6
            && d == id_disc && a == id_aluno) {

            fprintf(temp, "%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                    id_disc, id_aluno,
                    notas[0], notas[1], notas[2], notas[3]);
        }
        else {
            fputs(linha, temp);
        }
    }

    fclose(orig);
    fclose(temp);
    remove(ARQ_NOTAS);
    rename(temp_path, ARQ_NOTAS);

    printf("\nNota atualizada!\n");
}

void consultar_notas_aluno(int id_aluno)
{
    FILE *f = fopen(ARQ_NOTAS, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo de notas.\n");
        return;
    }

    char linha[256];
    int d, a;
    float n1, n2, n3, n4;
    int achou = 0;

    printf("\n=== MINHAS NOTAS ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                   &d, &a, &n1, &n2, &n3, &n4) == 6)
        {
            if (a == id_aluno)
            {
                achou = 1;

                printf("\nDisciplina %d:\n", d);

                printf("  Nota 1: ");
                if (n1 < 0) printf("--\n");
                else        printf("%.2f\n", n1);

                printf("  Nota 2: ");
                if (n2 < 0) printf("--\n");
                else        printf("%.2f\n", n2);

                printf("  Nota 3: ");
                if (n3 < 0) printf("--\n");
                else        printf("%.2f\n", n3);

                printf("  Nota 4: ");
                if (n4 < 0) printf("--\n");
                else        printf("%.2f\n", n4);
            }
        }
    }

    fclose(f);

    if (!achou)
    {
        printf("Nenhuma nota registrada para voce.\n");
    }
}


//
// =====================  FUNÇÕES DE FALTAS  =====================
//

int carregar_faltas(int id_disc, int id_aluno, int *faltas) {
    FILE *f = fopen(ARQ_FALTAS, "r");
    if (!f) return 0;

    char linha[200];
    int d, a, f2;

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d;%d;%d", &d, &a, &f2) == 3) {
            if (d == id_disc && a == id_aluno) {
                *faltas = f2;
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

void lancar_falta() {
    int id_disc, id_aluno, novas, faltas;

    printf("\n=== Lancar Falta ===\n");
    printf("ID da disciplina: ");
    scanf("%d", &id_disc); getchar();

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();

    printf("Quantidade de faltas a adicionar: ");
    scanf("%d", &novas); getchar();

    if (!carregar_faltas(id_disc, id_aluno, &faltas))
        faltas = 0;

    faltas += novas;

    char temp_path[100];
    snprintf(temp_path, sizeof(temp_path), "data/temp_faltas.txt");

    FILE *orig = fopen(ARQ_FALTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    char linha[200];
    int d, a, f2;
    int atualizado = 0;

    if (orig) {
        while (fgets(linha, sizeof(linha), orig)) {
            if (sscanf(linha, "%d;%d;%d", &d, &a, &f2) == 3 &&
                d == id_disc && a == id_aluno) {

                fprintf(temp, "%d;%d;%d\n", id_disc, id_aluno, faltas);
                atualizado = 1;
            }
            else fputs(linha, temp);
        }
        fclose(orig);
    }

    if (!atualizado) {
        fprintf(temp, "%d;%d;%d\n", id_disc, id_aluno, faltas);
    }

    fclose(temp);
    remove(ARQ_FALTAS);
    rename(temp_path, ARQ_FALTAS);

    printf("\nFaltas registradas!\n");
}


void editar_falta() {
    int id_disc, id_aluno, faltas;

    printf("\n=== Editar Faltas ===\n");
    printf("ID da disciplina: ");
    scanf("%d", &id_disc); getchar();

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();

    if (!carregar_faltas(id_disc, id_aluno, &faltas)) {
        printf("Registro nao encontrado.\n");
        return;
    }

    printf("Faltas atuais: %d\n", faltas);
    printf("Novo total de faltas: ");
    scanf("%d", &faltas); getchar();

    char temp_path[100];
    snprintf(temp_path, sizeof(temp_path), "data/temp_faltas.txt");

    FILE *orig = fopen(ARQ_FALTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    char linha[200];
    int d, a, f2;

    while (fgets(linha, sizeof(linha), orig)) {
        if (sscanf(linha, "%d;%d;%d", &d, &a, &f2) == 3 &&
            d == id_disc && a == id_aluno) {

            fprintf(temp, "%d;%d;%d\n", id_disc, id_aluno, faltas);
        }
        else fputs(linha, temp);
    }

    fclose(orig);
    fclose(temp);
    remove(ARQ_FALTAS);
    rename(temp_path, ARQ_FALTAS);

    printf("\nFaltas atualizadas!\n");
}

void consultar_faltas_aluno(int id_aluno)
{
    FILE *f = fopen(ARQ_FALTAS, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo de faltas.\n");
        return;
    }

    char linha[200];
    int d, a, faltas;
    int achou = 0;

    printf("\n=== MINHAS FALTAS ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%d", &d, &a, &faltas) == 3)
        {
            if (a == id_aluno)
            {
                printf("Disciplina %d: %d faltas\n", d, faltas);
                achou = 1;
            }
        }
    }

    fclose(f);

    if (!achou)
    {
        printf("Nenhuma falta registrada para voce.\n");
    }
}