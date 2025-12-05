from defs import dados_al, dados_prof, notas, faltas, disciplinas
import tkinter as tk
from tkinter import ttk

def montar_tela(frame):
    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    tk.Label(frame, text="Painel do Administrador", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=10)

    tk.Label(frame, text="Digite o ID:", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=2)
    entry_id = tk.Entry(frame, font=("Segoe UI", 12))
    entry_id.pack(pady=5)

    # Escolha do tipo de busca
    tk.Label(frame, text="Tipo de usuário:", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=0)
    tipo_var = tk.StringVar(value="Aluno")
    tipo_menu = ttk.Combobox(frame, textvariable=tipo_var, values=["Aluno", "Professor"], state="readonly", font=("Segoe UI", 11))
    tipo_menu.pack(pady=3)

    resultado_frame = tk.Frame(frame, bg="#003366")
    resultado_frame.pack(pady=7)

    def consultar():
        for widget in resultado_frame.winfo_children():
            widget.destroy()

        id_usuario = entry_id.get().strip()
        tipo = tipo_var.get()

        if tipo == "Aluno":
            aluno = dados_al.get(id_usuario)
            if not aluno:
                tk.Label(resultado_frame, text="Aluno não encontrado.", font=("Segoe UI", 16), fg="white", bg="#003366").pack()
                return

            # Dados do aluno
            tk.Label(resultado_frame, text=f"Nome Completo: {aluno['Nome Completo']}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)
            tk.Label(resultado_frame, text=f"ID: {id_usuario}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)
            tk.Label(resultado_frame, text=f"Email: {aluno['Email']}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)
            tk.Label(resultado_frame, text=f"Curso: {aluno['Curso']}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)

            # Notas e faltas
            for disc in disciplinas.get(id_usuario, []):
                disc_id = disc.get("ID")
                notas_aluno = notas.get(id_usuario, {}).get(disc_id, [])
                faltas_aluno = faltas.get(id_usuario, {}).get(disc_id, 0)
                tk.Label(resultado_frame,
                         text=f"{disc['Nome da Diciplina']} - Notas: {' - '.join(str(n) for n in notas_aluno)} | Faltas: {faltas_aluno}",
                         font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)

        elif tipo == "Professor":
            prof = dados_prof.get(id_usuario)
            if not prof:
                tk.Label(resultado_frame, text="Professor não encontrado.", font=("Segoe UI", 16), fg="white", bg="#003366").pack()
                return

            # Dados do professor
            tk.Label(resultado_frame, text=f"Nome Completo: {prof['Nome Completo']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=0)
            tk.Label(resultado_frame, text=f"ID: {id_usuario}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)
            tk.Label(resultado_frame, text=f"Email: {prof['Email']}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)
            tk.Label(resultado_frame, text=f"CPF: {prof['CPF']}", font=("Segoe UI", 14), fg="white", bg="#003366").pack(pady=0)
            # Disciplina que leciona
            
            disciplinas_prof = []
            for lista_d in disciplinas.values():  # cada aluno
                 for disc in lista_d:  # cada disciplina do aluno
                     if disc['Professor'] == id_usuario and disc['Nome da Diciplina'] not in disciplinas_prof:
                        disciplinas_prof.append(disc['Nome da Diciplina'])


            if not disciplinas_prof:
                disciplinas_prof.append("Nenhuma")

# Mostra todas as disciplinas em uma linha
            tk.Label(resultado_frame,
                text=f"Disciplina(s): {', '.join(disciplinas_prof)}",
                font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)

    # Botão Consultar
    tk.Button(frame, text="Consultar", command=consultar,
              bg="#0055AA", fg="white", font=("Segoe UI", 12, "bold"), width=15, height=1).pack(pady=10)

    # Botão Voltar
    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=1).pack(pady=10)
