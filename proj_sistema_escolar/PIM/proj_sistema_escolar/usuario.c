/*Funcoes relacionadas a usuario (login, cadastro, edicao, exclusao, consulta)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usuario.h"

#define MAX_STR 100
#define LOCAL_ARQUIVO_USUARIOS "data/usuarios.txt"

int login(Usuario *u)//funcao chamada ao iniciar o programa
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
    	sscanf(linha, "%d;%d;%[^;];%[^;];%[^\n]", &temp.id, &temp.tipo, temp.nome, temp.username, temp.senha);
    	
    	if (strcmp(username, temp.username) == 0 && strcmp(senha, temp.senha) == 0)
    	{
    		*u = temp;
    		fclose(f);
    		return 1; //Login OK
		}
	}

    fclose(f);
    return 0; // login falhou
    
}

void alterar_senha(Usuario *usuario_atual)//todos podem acessar
{
	int id_alvo;
	int status = 0;
	char entrada[MAX_STR];
	char nova_senha[MAX_STR];
	
	printf("\n=== Alterar Senha ===\n");
	
	if(usuario_atual->tipo!=1) //checa se o tipo nao eh admin
	{
		printf("Confirme sua senha atual: ");
		fgets(entrada, MAX_STR, stdin);
		entrada[strcspn(entrada, "\n")] = '\0';
		
		if (strcmp(entrada, usuario_atual->senha) != 0) {
            printf("Senha incorreta. Retornando ao Menu...\n");
            return;
        }
        
		id_alvo = usuario_atual->id;//atribui id apos senha confirmada
	}
	else //se o tipo for admin
	{
		char buffer[16];
		printf("Digite o id do usuario alvo: ");
		fgets(buffer, sizeof(buffer), stdin);
		id_alvo = atoi(buffer);
	}
    
    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "r");
    FILE *temp = fopen("temp.txt", "w");
	if(!f)printf("Erro ao abrir usuarios.txt\n");
    if(!temp) printf("Erro ao abrir temporario.\n");
    char linha[300];
    int id_temp;
    
    while(fgets(linha, sizeof(linha), f)) 
    {
    	if(sscanf(linha, "%d;", &id_temp) == 1 && id_temp == id_alvo) //verifica se a linha eh do id alvo
    	{
    		printf("\nDigite a nova senha: ");
			fgets(nova_senha, MAX_STR, stdin);
    		nova_senha[strcspn(nova_senha, "\n")] = '\0';
    		
    		Usuario tempUser;
        	sscanf(linha, "%d;%d;%[^;];%[^;];%[^\n]", &tempUser.id, &tempUser.tipo, tempUser.nome, tempUser.username, tempUser.senha);
        	strcpy(tempUser.senha, nova_senha);
        	
        	fprintf(temp, "%d;%d;%s;%s;%s\n", tempUser.id, tempUser.tipo, tempUser.nome, tempUser.username, tempUser.senha);
        	status = 1;
		}
		else fputs(linha, temp); //pula linha se nao
	}
	
	fclose(f);
    fclose(temp);

    remove(LOCAL_ARQUIVO_USUARIOS);
    rename("temp.txt", LOCAL_ARQUIVO_USUARIOS);
    
    if(status)
    {
    	printf("\nSenha alterada com sucesso!\n");
	}
	else
	{
		printf("\nID nao encontrado.\n");
	}
    
}

int gerar_id()//deve ser acessado somente pelo admin
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

void cadastrar_usuario()//deve ser acessado somente pelo admin -- ALTERAR PARA CADA TIPO DE ADICAO DEPOIS
{
    Usuario novo;

    novo.id = gerar_id(); // pega o próximo ID disponível

    printf("\n=== Cadastro de Usuario ===\n");
    
    printf("(1 = Admin, 2 = Professor, 3 = Aluno)\nSelecione o tipo do novo usuario: ");
    char buffer[8]; //char para ser recebido com fgets
	fgets(buffer, sizeof(buffer), stdin);
	novo.tipo = atoi(buffer);//converte o buffer char para inteiro
	
/*	switch novo.tipo
	{
		case 1:
			//o que for necessario para criar um admin
		case 2:
			//o que for necessario para criar um professor adicionar na struct professor
		case 3:
			//o que for necessario para criar um aluno - adicionar na struct aluno
		default:
			printf("\nERRO NO TIPO! ATENCAO\n");
	}*/

    printf("Nome: ");
    fgets(novo.nome, MAX_STR, stdin);//fgets para nao bugar o menu com /n
	novo.nome[strcspn(novo.nome, "\n")] = '\0';//marca o fim da string onde haveria a primeira quebra de linha /n

    printf("Username: ");
    fgets(novo.username, MAX_STR, stdin);
	novo.username[strcspn(novo.username, "\n")] = '\0';

    printf("Senha: ");
    fgets(novo.senha, MAX_STR, stdin);//fgets para nao bugar o menu com /n
	novo.senha[strcspn(novo.senha, "\n")] = '\0';

    FILE *f = fopen(LOCAL_ARQUIVO_USUARIOS, "a");
    fprintf(f, "%d;%d;%s;%s;%s\n", novo.id, novo.tipo, novo.nome, novo.username, novo.senha);
    fclose(f);

    printf("\nUsuario cadastrado com sucesso! (ID: %d)\n", novo.id);
}