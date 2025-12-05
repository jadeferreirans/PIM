/*
===========================================
 ARQUIVO: disciplina.c
 RESPONSABILIDADE:
 - Manipular disciplinas e vinculo com professores.

 O QUE COLOCAR AQUI:
 - funcao pra cadastrar disciplina
 - funcao pra listar disciplinas
 - sei la o que mais
===========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disciplina.h"

#define ARQ_DISCIPLINAS "data/disciplinas.txt"

//-----------------------------------------
// GERAR NOVO ID
//-----------------------------------------
int gerar_id_disciplina() {
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    if (!f) return 1;

    int maior = 0, id;
    char linha[300];

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d;", &id) == 1)
            if (id > maior) maior = id;
    }

    fclose(f);
    return maior + 1;
}

//-----------------------------------------
// SALVAR DISCIPLINA
//-----------------------------------------
void salvar_disciplina(Disciplina d) {
    FILE *f = fopen(ARQ_DISCIPLINAS, "a");

    fprintf(f, "%d;%s;%d;%d;", 
        d.id, d.nome, d.id_professor, d.total_alunos
    );

    for (int i = 0; i < d.total_alunos; i++) {
        fprintf(f, "%d", d.alunos[i]);
        if (i < d.total_alunos - 1) fprintf(f, ",");
    }

    fprintf(f, "\n");
    fclose(f);
}

//-----------------------------------------
// CADASTRAR DISCIPLINA
//-----------------------------------------
void cadastrar_disciplina() {
    Disciplina d;
    d.id = gerar_id_disciplina();
    d.total_alunos = 0;

    printf("\n=== Cadastro de Disciplina ===\n");

    // Nome
    printf("Nome da disciplina: ");
    fgets(d.nome, MAX_STR, stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0';

    // Professor
    printf("ID do professor responsável: ");
    char buffer[16];
    fgets(buffer, sizeof(buffer), stdin);
    d.id_professor = atoi(buffer);

    // Quantidade inicial de alunos
    int qtd;
    printf("Quantos alunos deseja matricular agora? (0 a %d): ", MAX_ALUNOS);
    fgets(buffer, sizeof(buffer), stdin);
    qtd = atoi(buffer);

    if (qtd < 0) qtd = 0;
    if (qtd > MAX_ALUNOS) qtd = MAX_ALUNOS;

    d.total_alunos = qtd;

    for (int i = 0; i < qtd; i++) {
        printf("ID do aluno %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        d.alunos[i] = atoi(buffer);
    }

    // Salvar no arquivo
    salvar_disciplina(d);

    printf("\nDisciplina cadastrada com sucesso! (ID: %d)\n", d.id);
}

//-----------------------------------------
// LISTAR DISCIPLINAS
//-----------------------------------------
void listar_disciplinas() {
    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    if (!f) {
        printf("Nenhuma disciplina encontrada.\n");
        return;
    }

    char linha[400];
    printf("\n=== LISTA DE DISCIPLINAS ===\n");

    while (fgets(linha, sizeof(linha), f)) {
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

void excluir_disciplina() {
    int id_alvo;
    char buffer[32];
    int encontrado = 0;

    printf("\n=== Excluir Disciplina ===\n");
    printf("Digite o ID da disciplina a excluir: ");
    fgets(buffer, sizeof(buffer), stdin);
    id_alvo = atoi(buffer);

    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) {
        printf("Erro ao abrir arquivos.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char linha[512];
    int id_lido;

    while (fgets(linha, sizeof(linha), f)) {

        // pega apenas o ID da disciplina
        if (sscanf(linha, "%d;", &id_lido) == 1 && id_lido == id_alvo) {
            // Encontrou a disciplina — NÃO copiará para o temp
            encontrado = 1;
            continue;
        }

        // Se não é a disciplina alvo, copiar normalmente
        fputs(linha, temp);
    }

    fclose(f);
    fclose(temp);

    remove(ARQ_DISCIPLINAS);
    rename("temp.txt", ARQ_DISCIPLINAS);

    if (encontrado)
        printf("\nDisciplina removida com sucesso!\n");
    else
        printf("\nDisciplina com ID %d não encontrada.\n", id_alvo);
}

void editar_disciplina() {
    int id_alvo;
    char buffer[64];
    int encontrada = 0;

    printf("\n=== Editar Disciplina ===\n");
    printf("Digite o ID da disciplina: ");
    fgets(buffer, sizeof(buffer), stdin);
    id_alvo = atoi(buffer);

    FILE *f = fopen(ARQ_DISCIPLINAS, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) {
        printf("Erro ao abrir arquivos.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char linha[512];
    int id_lido;

    while (fgets(linha, sizeof(linha), f)) {

        Disciplina d;

        // Leitura da linha completa
        // Primeiro pega dados antes da lista de alunos
        if (sscanf(linha, "%d;%[^;];%d;%d;", 
                   &d.id, d.nome, &d.id_professor, &d.total_alunos) != 4) {
            fputs(linha, temp);
            continue;
        }

        // Checar ID
        if (d.id != id_alvo) {
            // copiar sem alterar
            fputs(linha, temp);
            continue;
        }

        encontrada = 1;
        printf("\nDisciplina encontrada!\n");
        printf("Nome atual: %s\n", d.nome);
        printf("Professor atual (ID): %d\n", d.id_professor);
        printf("Total de alunos: %d\n", d.total_alunos);

        // --- EDITAR NOME ---
        printf("\nNovo nome (ENTER para manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0)
            strcpy(d.nome, buffer);

        // --- EDITAR PROFESSOR ---
        printf("Novo ID do professor (0 para manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        int novo_prof = atoi(buffer);
        if (novo_prof != 0)
            d.id_professor = novo_prof;

        // --- EDITAR ALUNOS ---
        printf("Deseja redefinir totalmente os alunos? (s/n): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (buffer[0] == 's' || buffer[0] == 'S') {

            printf("Novo total de alunos (0 a %d): ", MAX_ALUNOS);
            fgets(buffer, sizeof(buffer), stdin);
            d.total_alunos = atoi(buffer);

            if (d.total_alunos < 0) d.total_alunos = 0;
            if (d.total_alunos > MAX_ALUNOS) d.total_alunos = MAX_ALUNOS;

            for (int i = 0; i < d.total_alunos; i++) {
                printf("ID do aluno %d: ", i + 1);
                fgets(buffer, sizeof(buffer), stdin);
                d.alunos[i] = atoi(buffer);
            }
        }

        // --- GRAVAR EDIÇÃO ---
        fprintf(temp, "%d;%s;%d;%d;", 
                d.id, d.nome, d.id_professor, d.total_alunos);

        for (int i = 0; i < d.total_alunos; i++) {
            fprintf(temp, "%d", d.alunos[i]);
            if (i < d.total_alunos - 1)
                fprintf(temp, ",");
        }
        fprintf(temp, "\n");
    }

    fclose(f);
    fclose(temp);

    remove(ARQ_DISCIPLINAS);
    rename("temp.txt", ARQ_DISCIPLINAS);

    if (encontrada)
        printf("\nDisciplina atualizada com sucesso!\n");
    else
        printf("\nDisciplina com o ID informado não foi encontrada.\n");
}

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

        // -------------------------
        // Campo 1: ID da disciplina
        // -------------------------
        token = strtok(temp, ";");
        if (!token) continue;
        int id_disc = atoi(token);

        // -------------------------
        // Campo 2: Nome da disciplina
        // -------------------------
        token = strtok(NULL, ";");
        if (!token) continue;
        char nome[MAX_STR];
        strcpy(nome, token);

        // -------------------------
        // Campo 3: ID do professor
        // -------------------------
        token = strtok(NULL, ";");
        if (!token) continue;
        int prof_id = atoi(token);

        // -------------------------
        // Campo 4: Quantidade de alunos
        // -------------------------
        token = strtok(NULL, ";");
        if (!token) continue;
        int qtd = atoi(token);

        // Se NÃO for o professor da disciplina, ignora
        if (prof_id != id_professor)
            continue;

        // -------------------------
        // Exibir disciplina
        // -------------------------
        printf("Disciplina %d: %s (Alunos matriculados: %d)\n",
               id_disc, nome, qtd);

        achou = 1;
    }

    fclose(f);

    if (!achou)
        printf("Voce nao leciona nenhuma disciplina.\n");
}