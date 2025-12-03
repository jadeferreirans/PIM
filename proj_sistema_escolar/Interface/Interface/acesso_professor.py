import tkinter as tk

usuario_logado = None

def set_user(user):
    """Recebe o usuário logado do main."""
    global usuario_logado
    usuario_logado = user
    

def montar_tela(frame):
    # Limpa o frame antes de montar (opcional, mas recomendado)
    for widget in frame.winfo_children():
        widget.destroy()

    tk.Label(
        frame,
        text="Área do Professor",
        font=("Arial Black", 18 ),
        fg="white",
        bg="#003366"
    ).pack(pady=30)

    tk.Button(
        frame,
        text="Consultar Dados",
        command=lambda: montar_tela_dados1(frame),
        bg="#0055AA",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=22,
        height=2
    ).pack(pady=10)
        
    tk.Button(
        frame,
        text="Ver notas e faltas dos alunos",
        command=lambda: montar_tela_notas(frame),
        bg="#0055AA",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=22,
        height=2
    ).pack(pady=10)

    tk.Button(
        frame,
        text="Relatorio",
        command=lambda: montar_tela_relatorio(frame),
        bg="#0055AA",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=22,
        height=2
    ).pack(pady=10)
    
    
def montar_tela_notas(frame):
    from defs import notas  # importa o dicionário de notas

    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    tk.Label(
        frame,
        text="Notas dos Alunos",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=20)

    for id_aluno, valores in notas.items():
        texto = (
            f"ID: {id_aluno}  |  "
            f"A: {valores.get('A', '-')}, "
            f"B: {valores.get('B', '-')}, "
            f"C: {valores.get('C', '-')}, "
            f"D: {valores.get('D', '-')}"
        )

        tk.Label(
            frame,
            text=texto,
            font=("Segoe UI", 14),
            fg="white",
            bg="#003366"
        ).pack(pady=5)

    tk.Button(
        frame,
        text="Voltar",
        command=lambda: montar_tela(frame),
        bg="#AA0000",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=12,
        height=2
    ).pack(pady=20)


    
def montar_tela_dados1(frame):
    
    for widget in frame.winfo_children():
         widget.destroy()

    frame.configure(bg="#003366")

    tk.Label(
        frame,
        text="Seus dados",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=30)

    tk.Label(frame, text=f"Nome: {usuario_logado['nome']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)
    tk.Label(frame, text=f"Usuário: {usuario_logado['username']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)
    tk.Label(frame, text=f"RA: {usuario_logado['id']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)

    tk.Button(
        frame,
        text="Voltar",
        command=lambda: montar_tela(frame),
        bg="#AA0000",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=12,
        height=2
    ).pack(pady=10)   
        
def montar_tela_relatorio(frame):

    for widget in frame.winfo_children():
         widget.destroy()
 
    frame.configure(bg="#003366")

    tk.Label(
        frame,
        text="Suas notas",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=30)
      
    tk.Button(
        frame,
        text="Voltar",
        command=lambda: montar_tela(frame),
        bg="#AA0000",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=12,
        height=2
    ).pack(pady=10)    