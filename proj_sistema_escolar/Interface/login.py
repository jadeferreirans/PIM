import tkinter as tk
from tkinter import messagebox
import pandas as pd
import acesso_aluno
import acesso_professor
import acesso_admin
import os

print(" Diretório atual:", os.getcwd())
print(" Arquivos aqui:", os.listdir())

# Verifica o login user user.
def fazer_login():
    user_digitado = entrada_user.get().strip()
    senha1 = entrada_senha.get().strip()

    try:
        caminho_arq = "c:\\Users\\guile\\Desktop\\PIM-1\\proj_sistema_escolar\\data\\usuarios.txt"

       
        with open(caminho_arq, "r", encoding="utf-8") as f:
            partes = f.read().strip().split(";")

        usuarios = {}

        for i in range(0, len(partes), 5):
            id, tipo, nome, username, senha = partes[i:i+5]
            usuarios[id] = {
               "tipo": tipo,
               "nome": nome,
               "username": username,
               "senha": senha
    }
        # Verifica se o usuário existe e se a senha bate
        encontrado = None
        for id_, dados in usuarios.items():
           if dados["username"] == user_digitado and dados["senha"] == senha1:
             encontrado = dados
             break
          
        if encontrado:
           nivel12 = encontrado["tipo"]
           if nivel12 not in ['1', '2', '3']:
                messagebox.showerror("Erro", "Usuário sem nível de acesso.\nContate um administrador.")
                return
           else:
              messagebox.showinfo("Login", "✅ Login bem-sucedido!")
            
              if nivel12 == '3':
                 janela.destroy()
                 acesso_aluno.tela_aluno()

              elif nivel12 == '2':
                janela.destroy()
                acesso_professor.tela_prof()

              elif nivel12 == '1':
                janela.destroy()
                acesso_admin.tela_admin()

        else:
            messagebox.showerror("Erro", "❌ Usuário ou senha incorretos.")
    
    except FileNotFoundError:
        messagebox.showerror("Erro", "Arquivo não encontrado.")
    except Exception as e:
        messagebox.showerror("Erro", f"Ocorreu um erro: {e}")

    
janela = tk.Tk()
janela.title("Tela de Login")
janela.geometry("600x400")
janela.configure(bg="#003366")

titulo = tk.Label(janela, text="Login", font=("Arial Black", 30), fg="white", bg="#003366")
titulo.pack(pady=30)

tk.Label(janela, text="Usuário:", font=("Segoe UI", 14), fg="white", bg="#003366").pack()
entrada_user = tk.Entry(janela, width=30, font=("Segoe UI", 12))
entrada_user.pack(pady=5)

tk.Label(janela, text="Senha:", font=("Segoe UI", 14), fg="white", bg="#003366").pack()
entrada_senha = tk.Entry(janela, width=30, font=("Segoe UI", 12), show="*")
entrada_senha.pack(pady=5)

btn_login = tk.Button(
    janela,
    text="Entrar",
    command=fazer_login,
    bg="#0055AA",
    fg="white",
    activebackground="#0077CC",
    font=("Segoe UI", 12, "bold"),
    width=20,
    height=2
)
btn_login.pack(pady=30)


janela.mainloop()
