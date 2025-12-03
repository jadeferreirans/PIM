import tkinter as tk
from defs import pegar_notas, notas as db_notas, faltas as db_faltas

usuario_logado = None

def set_user(user):
    """Recebe o usuário logado do main."""
    global usuario_logado
    usuario_logado = user


# Tela Principal
def montar_tela(frame):

    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    tk.Label(
        frame,
        text="Área do Aluno",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=40)

    tk.Button(
        frame,
        text="Consultar seus dados",
        command=lambda: montar_tela_dados(frame),
        bg="#0055AA",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=22,
        height=2
    ).pack(pady=10)

    tk.Button(
        frame,
        text="Ver faltas",
        command=lambda: montar_tela_faltas(frame),
        bg="#0055AA",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=22,
        height=2
    ).pack(pady=10)

    tk.Button(
        frame,
        text="Ver notas",
        command=lambda: montar_tela_notas(frame),
        bg="#0055AA",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=22,
        height=2
    ).pack(pady=10)



# Tela dados
def montar_tela_dados(frame):

    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    user = usuario_logado

    tk.Label(
        frame,
        text="Seus dados",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=30)

    tk.Label(frame, text=f"Nome: {user['nome']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)
    tk.Label(frame, text=f"Usuário: {user['username']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)
    tk.Label(frame, text=f"RA: {user["id"]}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)

    tk.Button(
        frame,
        text="Voltar",
        command=lambda: montar_tela(frame),
        bg="#AA0000",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=12,
        height=2
    ).pack(pady=100)


# Tela Faltas
def montar_tela_faltas(frame):

    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    aluno_id = usuario_logado["id"]

    tk.Label(
        frame,
        text="Suas faltas",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=30)

    if aluno_id in db_faltas:
        falt = db_faltas[aluno_id]
        texto = (
            f"A: {falt['A']}\n"
            f"B: {falt['B']}\n"
            f"C: {falt['C']}\n"
            f"D: {falt['D']}"
        )
    else:
        texto = "Nenhuma falta registrada."

    tk.Label(
        frame,
        text=texto,
        font=("Segoe UI", 16),
        fg="white",
        bg="#003366"
    ).pack(pady=20)

    tk.Button(
        frame,
        text="Voltar",
        command=lambda: montar_tela(frame),
        bg="#AA0000",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=12,
        height=2
    ).pack(pady=100)



# Tela Notas
def montar_tela_notas(frame):

    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    aluno_id = usuario_logado["id"]

    tk.Label(
        frame,
        text="Suas notas",
        font=("Arial Black", 22),
        fg="white",
        bg="#003366"
    ).pack(pady=30)

    notas_texto = pegar_notas(aluno_id)

    tk.Label(
        frame,
        text=notas_texto,
        font=("Segoe UI", 16),
        fg="white",
        bg="#003366"
    ).pack(pady=20)

    tk.Button(
        frame,
        text="Voltar",
        command=lambda: montar_tela(frame),
        bg="#AA0000",
        fg="white",
        font=("Segoe UI", 12, "bold"),
        width=12,
        height=2
    ).pack(pady=100)
