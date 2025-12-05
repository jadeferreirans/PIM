import tkinter as tk
from tkinter import messagebox
import acesso_aluno
import acesso_professor
import acesso_admin
from defs import usuarios

usuario_logado = None  # usuário logado

# Função para trocar de tela
def trocar_tela(frame):
    frame.tkraise()

# Função de logout
def logout():
    global usuario_logado
    usuario_logado = None
    trocar_tela(frame_login)

# Função de login
def fazer_login():
    global usuario_logado
    user_digitado = entrada_user.get().strip()
    senha1 = entrada_senha.get().strip()

    encontrado = None
    for id_, dados in usuarios.items():
        if dados["nome"].strip().lower() == user_digitado.lower() and dados["senha"] == senha1:
            encontrado = dados.copy()
            encontrado["id"] = id_
            break

    if encontrado:
        usuario_logado = encontrado
        nivel12 = encontrado["tipo"]
        
        if nivel12 == '3':  # Aluno
            acesso_aluno.set_user(encontrado)
            acesso_aluno.set_logout(logout)
            acesso_aluno.montar_tela(frame_aluno)
            trocar_tela(frame_aluno)

        elif nivel12 == '2':  # Professor
            acesso_professor.set_user(encontrado)
            acesso_professor.set_logout(logout)
            acesso_professor.montar_tela(frame_professor)
            trocar_tela(frame_professor)

        elif nivel12 == '1':  # Admin
            acesso_admin.montar_tela(frame_admin)
            trocar_tela(frame_admin)
    else:
        messagebox.showerror("Erro", "❌ Usuário ou senha incorretos.")

# Janela principal
janela = tk.Tk()
janela.geometry("1000x600")
janela.title("Sistema Escolar")
janela.configure(bg="#003366")

# Frames
frame_login = tk.Frame(janela, bg="#003366")
frame_login.place(relwidth=1, relheight=1)

frame_aluno = tk.Frame(janela, bg="#003366")
frame_aluno.place(relwidth=1, relheight=1)

frame_professor = tk.Frame(janela, bg="#003366")
frame_professor.place(relwidth=1, relheight=1)

frame_admin = tk.Frame(janela, bg="#003366")
frame_admin.place(relwidth=1, relheight=1)

# Monta telas (aluno/professor/admin)
acesso_aluno.montar_tela(frame_aluno)
acesso_professor.montar_tela(frame_professor)
acesso_admin.montar_tela(frame_admin)

# Tela de login
tk.Label(frame_login, text="Login", font=("Arial Black", 30), fg="white", bg="#003366").pack(pady=30)
tk.Label(frame_login, text="Usuário:", font=("Segoe UI", 14), fg="white", bg="#003366").pack()
entrada_user = tk.Entry(frame_login, width=30, font=("Segoe UI", 12))
entrada_user.pack(pady=5)
tk.Label(frame_login, text="Senha:", font=("Segoe UI", 14), fg="white", bg="#003366").pack()
entrada_senha = tk.Entry(frame_login, width=30, font=("Segoe UI", 12), show="*")
entrada_senha.pack(pady=5)

tk.Button(frame_login, text="Entrar", command=fazer_login,
          bg="#0055AA", fg="white", font=("Segoe UI", 12, "bold"), width=20, height=2).pack(pady=30)

# Inicializa mostrando login
trocar_tela(frame_login)
janela.mainloop()
