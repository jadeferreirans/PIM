import tkinter as tk

def montar_tela(frame):
    # Limpa o frame antes de montar (opcional, mas recomendado)
    for widget in frame.winfo_children():
        widget.destroy()

    tk.Label(
        frame,
        text="Área do Aluno",
        font=("Arial Black", 26),
        fg="white",
        bg="#003366"
    ).pack(pady=40)

    tk.Button(
        frame,
        text="Ver Notas",
        font=("Arial", 14),
        width=20,
        height=2
    ).pack(pady=10)

    tk.Button(
        frame,
        text="Ver Faltas",
        font=("Arial", 14),
        width=20,
        height=2
    ).pack(pady=10)

    tk.Button(
        frame,
        text="Disciplinas",
        font=("Arial", 14),
        width=20,
        height=2
    ).pack(pady=10)
