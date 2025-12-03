import tkinter as tk
from tkinter import messagebox
import acesso_aluno
import acesso_professor
import acesso_admin

# Verifica o login user user.
def fazer_login():
    
    from defs import usuarios
    
    user_digitado = entrada_user.get().strip()
    senha1 = entrada_senha.get().strip()

    try:
      
# Verifica se o usuário existe e se a senha bate
        encontrado = None
        for id_, dados in usuarios.items():
            if dados["username"] == user_digitado and dados["senha"] == senha1:
                encontrado = dados.copy()   # ← CÓPIA DOS DADOS
                encontrado["id"] = id_      # ← ADICIONA O ID
                break

# Direciona o usuario para sua tela de acordo com seu nivel de acesso          
        if encontrado:
           nivel12 = encontrado["tipo"]
           if nivel12 not in ['1', '2', '3']:
                messagebox.showerror("Erro", "Usuário sem nível de acesso.\nContate um administrador.")
                return
           else:
             # messagebox.showinfo("Login", "✅ Login bem-sucedido!")
            
              if nivel12 == '3':
                acesso_aluno.set_user(encontrado)
                janela.geometry("1000x600")
                trocar_tela(frame_aluno)


              elif nivel12 == '2':
                acesso_professor.set_user(encontrado)
                janela.geometry("1000x600")
                trocar_tela(frame_professor)

              elif nivel12 == '1':
                #janela.destroy()
                janela.geometry("1000x600")
                trocar_tela(frame_admin)

        else:
            messagebox.showerror("Erro", "❌ Usuário ou senha incorretos.")
    
    except FileNotFoundError:
        messagebox.showerror("Erro", "Arquivo não encontrado.") 
    except Exception as e:
        messagebox.showerror("Erro", f"Ocorreu um erro: {e}")
    return encontrado

janela = tk.Tk()
janela.geometry("600x400")
janela.configure(bg="#003366")

# Frames das telas
frame_login = tk.Frame(janela, bg="#003366")
frame_login.place(relwidth=1, relheight=1)

frame_aluno = tk.Frame(janela, bg="#003366")
frame_aluno.place(relwidth=1, relheight=1)

frame_professor = tk.Frame(janela, bg="#003366")
frame_professor.place(relwidth=1, relheight=1)

frame_admin = tk.Frame(janela, bg="#003366")
frame_admin.place(relwidth=1, relheight=1)

# Monta a tela do aluno dentro do frame
acesso_aluno.montar_tela(frame_aluno)
acesso_admin.montar_tela(frame_admin)
acesso_professor.montar_tela(frame_professor)


def trocar_tela(frame):
    frame.tkraise()


titulo = tk.Label(
    frame_login, 
    text="Login",
    font=("Arial Black", 30),
    fg="white", bg="#003366"
)
titulo.pack(pady=30)

tk.Label(
    frame_login,
    text="Usuário:",
    font=("Segoe UI", 14),
    fg="white", bg="#003366").pack()
entrada_user = tk.Entry(frame_login, width=30, font=("Segoe UI", 12))
entrada_user.pack(pady=5)

tk.Label(
    frame_login,
    text="Senha:",
    font=("Segoe UI", 14),
    fg="white", bg="#003366").pack()
entrada_senha = tk.Entry(frame_login, width=30, font=("Segoe UI", 12), show="*")
entrada_senha.pack(pady=5)

btn_login = tk.Button(
    frame_login,
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

trocar_tela(frame_login)
janela.mainloop()
