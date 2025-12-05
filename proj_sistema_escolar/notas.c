#include "notas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ==================================================
//  CARREGAR NOTAS DE UM ALUNO
// ==================================================
//

int carregar_notas(int id_disc, int id_aluno, float notas[4])
{
    FILE *f = fopen(ARQ_NOTAS, "r");
    if (!f) return 0;

    char linha[200];
    int d, a;
    float n1, n2, n3, n4;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                   &d, &a, &n1, &n2, &n3, &n4) == 6)
        {
            if (d == id_disc && a == id_aluno)
            {
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

//
// ==================================================
//  LANÇAR NOTA
// ==================================================
//

void lancar_nota(int id_professor)
{
    int id_disc, id_aluno, indice;
    float notas[4] = { -1, -1, -1, -1 };

    printf("\n=== Lancar Nota ===\n");
    listar_disciplinas_professor(id_professor);
    printf("\n[0] Para Cancelar a qualquer momento\n");
    printf("\nID da disciplina: ");
    scanf("%d", &id_disc); getchar();
    if(id_disc == 0) return;

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();
    if(id_aluno == 0) return;

    carregar_notas(id_disc, id_aluno, notas);

    printf("\nQual nota deseja alterar? (1 a 4): ");
    scanf("%d", &indice); getchar();
    if(indice == 0) return;
    indice--;

    if (indice < 0 || indice > 3)
    {
        printf("Indice invalido.\n");
        return;
    }

    printf("Digite a nova nota: ");
    scanf("%f", &notas[indice]); getchar();

    char temp_path[] = "data/temp_notas.txt";

    FILE *orig = fopen(ARQ_NOTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    if (!temp)
    {
        printf("Erro ao abrir arquivo temporario.\n");
        return;
    }

    char linha[200];
    int d, a;
    float n1, n2, n3, n4;
    int atualizado = 0;

    if (orig)
    {
        while (fgets(linha, sizeof(linha), orig))
        {
            if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                       &d, &a, &n1, &n2, &n3, &n4) == 6 &&
                d == id_disc && a == id_aluno)
            {
                fprintf(temp, "%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                        d, a, notas[0], notas[1], notas[2], notas[3]);
                atualizado = 1;
            }
            else
            {
                fputs(linha, temp);
            }
        }
        fclose(orig);
    }

    if (!atualizado)
    {
        fprintf(temp, "%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                id_disc, id_aluno,
                notas[0], notas[1], notas[2], notas[3]);
    }

    fclose(temp);

    remove(ARQ_NOTAS);
    rename(temp_path, ARQ_NOTAS);

    printf("\nNota registrada com sucesso!\n");
}

//
// ==================================================
//  EDITAR NOTA
// ==================================================
//

void editar_nota(int id_professor)
{
    int id_disc, id_aluno, indice;
    float notas[4];

    printf("\n=== Editar Nota ===\n");
    listar_disciplinas_professor(id_professor);
    printf("\n[0] Para Cancelar a qualquer momento\n");
    printf("\nID da disciplina: ");
    scanf("%d", &id_disc); getchar();
    if(id_disc == 0) return;

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();
    if(id_aluno == 0) return;

    if (!carregar_notas(id_disc, id_aluno, notas))
    {
        printf("Registro nao encontrado.\n");
        return;
    }

    printf("\nNotas atuais:\n");
    for (int i = 0; i < 4; i++)
        printf("Nota %d: %.2f\n", i + 1, notas[i]);

    printf("\nQual nota alterar (1 a 4)? ");
    scanf("%d", &indice); getchar();

    indice--;
    if (indice < 0 || indice > 3)
    {
        printf("Indice invalido.\n");
        return;
    }

    printf("Nova nota: ");
    scanf("%f", &notas[indice]); getchar();

    char temp_path[] = "data/temp_notas.txt";

    FILE *orig = fopen(ARQ_NOTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    if (!orig || !temp)
    {
        printf("Erro ao abrir arquivos.\n");
        if (orig) fclose(orig);
        if (temp) fclose(temp);
        return;
    }

    char linha[200];
    int d, a;
    float n1, n2, n3, n4;

    while (fgets(linha, sizeof(linha), orig))
    {
        if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                   &d, &a, &n1, &n2, &n3, &n4) == 6 &&
            d == id_disc && a == id_aluno)
        {
            fprintf(temp, "%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                    d, a, notas[0], notas[1], notas[2], notas[3]);
        }
        else
        {
            fputs(linha, temp);
        }
    }

    fclose(orig);
    fclose(temp);

    remove(ARQ_NOTAS);
    rename(temp_path, ARQ_NOTAS);

    printf("\nNota atualizada!\n");
}

//
// ==================================================
//  CONSULTAR NOTAS DO ALUNO
// ==================================================
//

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
    int encontrou = 0;

    printf("\n=== MINHAS NOTAS ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%f;%f;%f;%f",
                   &d, &a, &n1, &n2, &n3, &n4) == 6 &&
            a == id_aluno)
        {
            encontrou = 1;

            printf("\nDisciplina %d:\n", d);

            printf("  Nota 1: %s%.2f\n",  n1 < 0 ? "-- " : "", n1 >= 0 ? n1 : 0);
            printf("  Nota 2: %s%.2f\n",  n2 < 0 ? "-- " : "", n2 >= 0 ? n2 : 0);
            printf("  Nota 3: %s%.2f\n",  n3 < 0 ? "-- " : "", n3 >= 0 ? n3 : 0);
            printf("  Nota 4: %s%.2f\n",  n4 < 0 ? "-- " : "", n4 >= 0 ? n4 : 0);
        }
    }

    fclose(f);

    if (!encontrou)
        printf("Nenhuma nota registrada para voce.\n");
}

//
// ==================================================
//  CARREGAR FALTAS
// ==================================================
//

int carregar_faltas(int id_disc, int id_aluno, int *faltas)
{
    FILE *f = fopen(ARQ_FALTAS, "r");
    if (!f) return 0;

    char linha[200];
    int d, a, f2;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;%d;%d", &d, &a, &f2) == 3 &&
            d == id_disc && a == id_aluno)
        {
            *faltas = f2;
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

//
// ==================================================
//  LANÇAR FALTA
// ==================================================
//

void lancar_falta(int id_professor)
{
    int id_disc, id_aluno, novas, faltas;

    printf("\n=== Lancar Falta ===\n");
    listar_disciplinas_professor(id_professor);
    printf("\n[0] Para Cancelar a qualquer momento\n");
    printf("\nID da disciplina: ");
    scanf("%d", &id_disc); getchar();
    if(id_disc == 0) return;

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();
    if(id_aluno == 0) return;

    printf("Quantidade de faltas a adicionar: ");
    scanf("%d", &novas); getchar();

    if (!carregar_faltas(id_disc, id_aluno, &faltas))
        faltas = 0;

    faltas += novas;

    char temp_path[] = "data/temp_faltas.txt";

    FILE *orig = fopen(ARQ_FALTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    if (!temp)
    {
        printf("Erro ao abrir arquivo temporario.\n");
        return;
    }

    char linha[200];
    int d, a, f2;
    int atualizado = 0;

    if (orig)
    {
        while (fgets(linha, sizeof(linha), orig))
        {
            if (sscanf(linha, "%d;%d;%d", &d, &a, &f2) == 3 &&
                d == id_disc && a == id_aluno)
            {
                fprintf(temp, "%d;%d;%d\n", id_disc, id_aluno, faltas);
                atualizado = 1;
            }
            else fputs(linha, temp);
        }
        fclose(orig);
    }

    if (!atualizado)
    {
        fprintf(temp, "%d;%d;%d\n", id_disc, id_aluno, faltas);
    }

    fclose(temp);

    remove(ARQ_FALTAS);
    rename(temp_path, ARQ_FALTAS);

    printf("\nFaltas registradas!\n");
}

//
// ==================================================
//  EDITAR FALTAS
// ==================================================
//

void editar_falta(int id_professor)
{
    int id_disc, id_aluno, faltas;

    printf("\n=== Editar Faltas ===\n");
    listar_disciplinas_professor(id_professor);
    printf("\n[0] Para Cancelar a qualquer momento\n");
    printf("\nID da disciplina: ");;
    scanf("%d", &id_disc); getchar();
    if(id_disc == 0) return;

    printf("ID do aluno: ");
    scanf("%d", &id_aluno); getchar();
    if(id_aluno == 0) return;

    if (!carregar_faltas(id_disc, id_aluno, &faltas))
    {
        printf("Registro nao encontrado.\n");
        return;
    }

    printf("Faltas atuais: %d\n", faltas);
    printf("Novo total de faltas: ");
    scanf("%d", &faltas); getchar();

    char temp_path[] = "data/temp_faltas.txt";

    FILE *orig = fopen(ARQ_FALTAS, "r");
    FILE *temp = fopen(temp_path, "w");

    if (!orig || !temp)
    {
        printf("Erro ao abrir arquivos.\n");
        if (orig) fclose(orig);
        if (temp) fclose(temp);
        return;
    }

    char linha[200];
    int d, a, f2;

    while (fgets(linha, sizeof(linha), orig))
    {
        if (sscanf(linha, "%d;%d;%d", &d, &a, &f2) == 3 &&
            d == id_disc && a == id_aluno)
        {
            fprintf(temp, "%d;%d;%d\n", d, a, faltas);
        }
        else
        {
            fputs(linha, temp);
        }
    }

    fclose(orig);
    fclose(temp);

    remove(ARQ_FALTAS);
    rename(temp_path, ARQ_FALTAS);

    printf("\nFaltas atualizadas!\n");
}

//
// ==================================================
//  CONSULTAR FALTAS DO ALUNO
// ==================================================
//

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
        if (sscanf(linha, "%d;%d;%d", &d, &a, &faltas) == 3 &&
            a == id_aluno)
        {
            printf("Disciplina %d: %d faltas\n", d, faltas);
            achou = 1;
        }
    }

    fclose(f);

    if (!achou)
        printf("Nenhuma falta registrada para voce.\n");
}