import tkinter as tk

def tela_admin():
    janela = tk.Tk()
    janela.title("Tela do Aluno")
    janela.geometry("1024x768")
    janela.configure(bg="#003366")

    tk.Label(janela, text="Bem-vindo, ADMIN!", font=("Arial Black", 24), fg="white", bg="#003366").pack(pady=50)

    janela.mainloop()