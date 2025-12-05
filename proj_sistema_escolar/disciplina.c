#include "disciplina.h"
#include "notas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ==================================================
//  GERAR NOVO ID DE DISCIPLINA
// ==================================================
//

int gerar_id_disciplina()
{
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    if (!f) return 1;

    int maior = 0, id;
    char linha[300];

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;", &id) == 1)
        {
            if (id > maior) maior = id;
        }
    }

    fclose(f);
    return maior + 1;
}

//
// ==================================================
//  SALVAR DISCIPLINA
// ==================================================
//

void salvar_disciplina(Disciplina d)
{
    FILE *f = fopen(ARQ_DISCIPLINAS, "a");
    if (!f)
    {
        printf("Erro ao abrir arquivo de disciplinas.\n");
        return;
    }

    fprintf(f, "%d;%s;%d;%d;",
            d.id, d.nome, d.id_professor, d.total_alunos);

    for (int i = 0; i < d.total_alunos; i++)
    {
        fprintf(f, "%d", d.alunos[i]);
        if (i < d.total_alunos - 1)
            fprintf(f, ",");
    }

    fprintf(f, "\n");
    fclose(f);
}

//
// ==================================================
//  CADASTRAR DISCIPLINA
// ==================================================
//

void cadastrar_disciplina()
{
    Disciplina d;
    d.id = gerar_id_disciplina();
    d.total_alunos = 0;

    printf("\n=== Cadastro de Disciplina ===\n");

    printf("Nome da disciplina: ");
    fgets(d.nome, MAX_STR, stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0';

    printf("ID do professor responsavel: ");
    char buffer[32];
    fgets(buffer, sizeof(buffer), stdin);
    d.id_professor = atoi(buffer);

    printf("Quantos alunos deseja matricular agora? (0 a %d): ", MAX_ALUNOS);
    fgets(buffer, sizeof(buffer), stdin);
    int qtd = atoi(buffer);

    if (qtd < 0) qtd = 0;
    if (qtd > MAX_ALUNOS) qtd = MAX_ALUNOS;

    d.total_alunos = qtd;

    for (int i = 0; i < qtd; i++)
    {
        printf("ID do aluno %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        d.alunos[i] = atoi(buffer);
    }

    salvar_disciplina(d);

    printf("\nDisciplina cadastrada com sucesso! (ID: %d)\n", d.id);
}

//
// ==================================================
//  LISTAR TODAS AS DISCIPLINAS
// ==================================================
//

void listar_disciplinas()
{
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    if (!f)
    {
        printf("Nenhuma disciplina encontrada.\n");
        return;
    }

    char linha[512];
    printf("\n=== LISTA DE DISCIPLINAS ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        Disciplina d;
        char alunos_raw[200] = "";

        sscanf(linha, "%d;%[^;];%d;%d;%[^\n]",
               &d.id, d.nome, &d.id_professor,
               &d.total_alunos, alunos_raw);

        printf("\nID: %d\nNome: %s\nProfessor ID: %d\nAlunos: %s\n",
               d.id, d.nome, d.id_professor,
               d.total_alunos > 0 ? alunos_raw : "(nenhum)");
    }

    fclose(f);
}

//
// ==================================================
//  EXCLUIR DISCIPLINA
// ==================================================
//

void excluir_disciplina()
{
    int id_alvo;
    char buffer[32];
    int encontrada = 0;

    printf("\n=== EXCLUIR DISCIPLINA ===\n");
    listar_disciplinas();

    printf("\nDigite o ID da disciplina que deseja excluir: ");
    fgets(buffer, sizeof(buffer), stdin);
    id_alvo = atoi(buffer);

    // ---------------------------------------
    // CONFIRMAÇÃO
    // ---------------------------------------
    printf("\nTem certeza que deseja excluir a disciplina %d? (s/n): ", id_alvo);
    fgets(buffer, sizeof(buffer), stdin);

    if (buffer[0] != 's' && buffer[0] != 'S')
    {
        printf("\nOperacao cancelada.\n");
        return;
    }

    // ---------------------------------------
    // 1) Remover da lista de disciplinas
    // ---------------------------------------
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    FILE *temp = fopen("temp_disc.txt", "w");

    if (!f || !temp)
    {
        printf("Erro ao abrir arquivos.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char linha[512];
    int id_lido;

    while (fgets(linha, sizeof(linha), f))
    {
        if (sscanf(linha, "%d;", &id_lido) == 1 && id_lido == id_alvo)
        {
            encontrada = 1;
            continue; // não grava → exclui
        }

        fputs(linha, temp);
    }

    fclose(f);
    fclose(temp);

    remove(ARQ_DISCIPLINAS);
    rename("temp_disc.txt", ARQ_DISCIPLINAS);


    // ---------------------------------------
    // 2) Remover notas relacionadas
    // ---------------------------------------
    FILE *fn = fopen(ARQ_NOTAS, "r");
    FILE *tempN = fopen("data/temp_notas.txt", "w");

    if (fn && tempN)
    {
        int disc, aluno;
        float n1, n2, n3, n4;

        while (fgets(linha, sizeof(linha), fn))
        {
            if (sscanf(linha, "%d;%d;%f;%f;%f;%f", 
                       &disc, &aluno, &n1, &n2, &n3, &n4) == 6)
            {
                if (disc == id_alvo)
                    continue; // pula, exclui notas
            }

            fputs(linha, tempN);
        }

        fclose(fn);
        fclose(tempN);

        remove(ARQ_NOTAS);
        rename("data/temp_notas.txt", ARQ_NOTAS);
    }


    // ---------------------------------------
    // 3) Remover faltas relacionadas
    // ---------------------------------------
    FILE *ff = fopen(ARQ_FALTAS, "r");
    FILE *tempF = fopen("data/temp_faltas.txt", "w");

    if (ff && tempF)
    {
        int disc, aluno, faltas;

        while (fgets(linha, sizeof(linha), ff))
        {
            if (sscanf(linha, "%d;%d;%d", &disc, &aluno, &faltas) == 3)
            {
                if (disc == id_alvo)
                    continue; // exclui faltas
            }

            fputs(linha, tempF);
        }

        fclose(ff);
        fclose(tempF);

        remove(ARQ_FALTAS);
        rename("data/temp_faltas.txt", ARQ_FALTAS);
    }


    // ---------------------------------------
    // FINALIZAÇÃO
    // ---------------------------------------
    if (encontrada)
        printf("\nDisciplina %d removida COMPLETAMENTE do sistema!\n", id_alvo);
    else
        printf("\nDisciplina com ID %d nao encontrada.\n", id_alvo);
}

//
// ==================================================
//  EDITAR DISCIPLINA
// ==================================================
//

void editar_disciplina()
{
    int id_alvo;
    char buffer[128];
    int encontrada = 0;

    printf("\n=== Editar Disciplina ===\n");
    listar_disciplinas();
    printf("\nDigite o ID da disciplina que deseja editar: ");
    fgets(buffer, sizeof(buffer), stdin);
    id_alvo = atoi(buffer);

    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    FILE *temp = fopen("temp_disc.txt", "w");

    if (!f || !temp)
    {
        printf("Erro ao abrir arquivos.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char linha[512];

    while (fgets(linha, sizeof(linha), f))
    {
        Disciplina d;
        memset(&d, 0, sizeof(Disciplina));  // garante dados limpos
        char alunos_raw[256] = "";

        // Lê corretamente TODOS os campos, inclusive lista de alunos
        if (sscanf(linha, "%d;%[^;];%d;%d;%[^\n]",
                   &d.id, d.nome, &d.id_professor, &d.total_alunos, alunos_raw) < 4)
        {
            fputs(linha, temp); 
            continue;
        }

        // se não for a disciplina alvo → copia
        if (d.id != id_alvo)
        {
            fputs(linha, temp);
            continue;
        }

        encontrada = 1;

        // converter lista de alunos
        d.total_alunos = 0;
        if (strlen(alunos_raw) > 0)
        {
            char *tok = strtok(alunos_raw, ",");
            while (tok != NULL && d.total_alunos < MAX_ALUNOS)
            {
                d.alunos[d.total_alunos++] = atoi(tok);
                tok = strtok(NULL, ",");
            }
        }

        // ---- EXIBIR DADOS ----
        printf("\nDisciplina encontrada!\n");
        printf("Nome atual: %s\n", d.nome);
        printf("Professor atual (ID): %d\n", d.id_professor);
        printf("Total de alunos: %d\n", d.total_alunos);

        // ----------- EDITAR NOME -----------
        printf("\nNovo nome (ENTER para manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0)
            strcpy(d.nome, buffer);

        // ----------- EDITAR PROFESSOR -----------
        printf("Novo ID do professor (ENTER para manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) > 0) // só altera se usuário digitou algo
            d.id_professor = atoi(buffer);

        // ----------- EDITAR ALUNOS -----------
        printf("Deseja redefinir totalmente os alunos? (s/n): ");
        fgets(buffer, sizeof(buffer), stdin);

        if (buffer[0] == 's' || buffer[0] == 'S')
        {
            printf("Novo total de alunos (0 a %d): ", MAX_ALUNOS);
            fgets(buffer, sizeof(buffer), stdin);

            int novo_total = atoi(buffer);
            if (novo_total < 0) novo_total = 0;
            if (novo_total > MAX_ALUNOS) novo_total = MAX_ALUNOS;

            d.total_alunos = novo_total;

            for (int i = 0; i < d.total_alunos; i++)
            {
                printf("ID do aluno %d: ", i + 1);
                fgets(buffer, sizeof(buffer), stdin);
                d.alunos[i] = atoi(buffer);
            }
        }

        // ----------- GRAVAR NO TEMP -----------

        fprintf(temp, "%d;%s;%d;%d;",
                d.id, d.nome, d.id_professor, d.total_alunos);

        for (int i = 0; i < d.total_alunos; i++)
        {
            fprintf(temp, "%d", d.alunos[i]);
            if (i < d.total_alunos - 1)
                fprintf(temp, ",");
        }

        fprintf(temp, "\n");
    }

    fclose(f);
    fclose(temp);

    remove(ARQ_DISCIPLINAS);
    rename("temp_disc.txt", ARQ_DISCIPLINAS);

    if (encontrada)
        printf("\nDisciplina atualizada com sucesso!\n");
    else
        printf("\nDisciplina com ID %d nao encontrada.\n", id_alvo);
}

//
// ==================================================
//  LISTAR DISCIPLINAS DE UM PROFESSOR
// ==================================================
//

void listar_disciplinas_professor(int id_professor)
{
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo de disciplinas.\n");
        return;
    }

    char linha[512];
    int achou = 0;

    printf("\n=== MINHAS DISCIPLINAS ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        char temp[512];
        strcpy(temp, linha);

        char *token;

        token = strtok(temp, ";");
        if (!token) continue;
        int id_disc = atoi(token);

        token = strtok(NULL, ";");
        if (!token) continue;
        char nome[MAX_STR];
        strcpy(nome, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        int prof_id = atoi(token);

        token = strtok(NULL, ";");
        if (!token) continue;
        int qtd = atoi(token);

        if (prof_id != id_professor)
            continue;

        printf("Disciplina %d: %s (Alunos matriculados: %d)\n",
               id_disc, nome, qtd);

        achou = 1;
    }

    fclose(f);

    if (!achou)
        printf("Voce nao leciona nenhuma disciplina.\n");
}


//
// ==================================================
//  LISTAR DISCIPLINAS DE UM ALUNO
// ==================================================
//
void listar_disciplinas_aluno(int id_aluno)
{
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo de disciplinas.\n");
        return;
    }

    char linha[512];
    int encontrou = 0;

    printf("\n=== MINHAS DISCIPLINAS ===\n");

    while (fgets(linha, sizeof(linha), f))
    {
        char copy[512];
        strncpy(copy, linha, sizeof(copy));
        copy[sizeof(copy) - 1] = '\0';

        char *tok = strtok(copy, ";\n");
        if (!tok) continue;
        int id_disc = atoi(tok);

        tok = strtok(NULL, ";\n");
        if (!tok) continue;
        char nome_disc[200];
        strncpy(nome_disc, tok, sizeof(nome_disc));
        nome_disc[sizeof(nome_disc) - 1] = '\0';

        tok = strtok(NULL, ";\n");
        if (!tok) continue;
        int id_prof = atoi(tok);

        tok = strtok(NULL, ";\n");
        if (!tok) continue;
        int total_alunos = atoi(tok);

        tok = strtok(NULL, ";\n");

        int esta_matriculado = 0;

        if (tok && strlen(tok) > 0)
        {
            char *sub = strtok(tok, ",");
            while (sub)
            {
                if (atoi(sub) == id_aluno)
                {
                    esta_matriculado = 1;
                    break;
                }
                sub = strtok(NULL, ",");
            }
        }

        // Se ele está nesta disciplina
        if (esta_matriculado)
        {
            printf("(%d) - %s\n", id_disc, nome_disc);
            encontrou = 1;
        }
    }

    fclose(f);

    if (!encontrou)
        printf("Voce ainda nao esta matriculado em nenhuma disciplina.\n");
}