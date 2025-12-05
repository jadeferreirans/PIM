#include "usuario.h"
#include "menus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Usuario usuario_atual;
    char entrada[8];

    while (1)
    {
    	menu_login();

        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strcmp(entrada, "0") == 0)
        {
            printf("\nEncerrando o sistema...\n");
            break;
        }

        if (login(&usuario_atual))
        {
        	limpar_tela();

            switch (usuario_atual.tipo)
            {
                case 1:
                    menu_admin(usuario_atual);
                    break;

                case 2:
                    menu_professor(usuario_atual);
                    break;

                case 3:
                    menu_aluno(usuario_atual);
                    break;

                default:
                    printf("Tipo de usuario invalido!\n");
            }
        }
        else
        {
            printf("\nFalha no login. Tente novamente.\n");
            pausar();
        }
    }

    return 0;
}