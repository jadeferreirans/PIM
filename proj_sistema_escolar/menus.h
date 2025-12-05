#ifndef MENUS_H
#define MENUS_H

#include "usuario.h"

// Menus principais
void menu_admin(Usuario usuario_atual);
void menu_professor(Usuario usuario_atual);
void menu_aluno(Usuario usuario_atual);
void menu_login();

// Submenus
void menu_usuarios_admin(Usuario usuario_atual);
void menu_disciplinas_admin(Usuario usuario_atual);
void menu_disciplinas_professor(Usuario usuario_atual);
void menu_dados_professor(Usuario usuario_atual);

// Auxiliares
void limpar_tela();
void pausar();

#endif