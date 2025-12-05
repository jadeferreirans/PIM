import tkinter as tk
from defs import notas, faltas, dados_prof , disciplinas, dados_al

usuario_logado = None
logout_func = None

def set_user(user):
    global usuario_logado
    usuario_logado = user

def set_logout(func):
    global logout_func
    logout_func = func

def montar_tela(frame):
    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    tk.Label(frame, text="Área do Professor",  
             font=("Arial Black", 22),
             fg="white", bg="#003366"
             ).pack(pady=40)

    tk.Button(frame, text="Consultar dados", 
              command=lambda:  montar_tela_dados(frame),
              bg="#0055AA", 
              fg="white", 
              font=("Segoe UI", 12, "bold"), 
              width=22, 
              height=2
              ).pack(pady=10)

    tk.Button(frame, text="Ver notas e faltas", 
              command=lambda: montar_tela_notas(frame),
              bg="#0055AA", 
              fg="white", 
              font=("Segoe UI", 12, "bold"), 
              width=22, 
              height=2
              ).pack(pady=10)

    tk.Button(frame, 
              text="Logout", 
              command=logout_func,
              bg="#555555", 
              fg="white", 
              font=("Segoe UI", 12, "bold"), 
              width=22, 
              height=2
              ).pack(pady=10)

def montar_tela_dados(frame):
    for widget in frame.winfo_children():
        widget.destroy()
  
    frame.configure(bg="#003366")
    id_prof = str(usuario_logado["id"])

    # Pega os dados do professor do dicionário global
    prof = dados_prof.get(id_prof)
    tk.Label(frame, text="Seus dados", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=30)
    
    if prof:
        tk.Label(frame, text=f"Nome Completo: {prof['Nome Completo']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"ID: {id_prof}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"CPF: {prof['CPF']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"Email: {prof['Email']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
    else:
        tk.Label(frame, text="Dados não encontrados.", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=20)
    # id do professor logado
    id_prof = str(usuario_logado["id"])

# pega a primeira disciplina que ele leciona
    disciplina = next(
        (disc["Nome da Diciplina"] 
        for lista_d in disciplinas.values() 
        for disc in lista_d 
        if disc["Professor"] == id_prof),
        "Nenhuma"
)
    tk.Label(frame, text=f"Disciplina: {disciplina}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)

    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=2).pack(pady=20)

def montar_tela_notas(frame):
    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")

    tk.Label(frame, text="Consultar Aluno", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=20)
    tk.Label(frame, text="Digite o ID do aluno:", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)

    entry_id = tk.Entry(frame, font=("Segoe UI", 16))
    entry_id.pack(pady=5)

    resultado_frame = tk.Frame(frame, bg="#003366")
    resultado_frame.pack(pady=10)

    def consultar():
        for widget in resultado_frame.winfo_children():
            widget.destroy()

        id_aluno = entry_id.get().strip()
        aluno = dados_al.get(id_aluno)

        if not aluno:
            tk.Label(resultado_frame, text="Aluno não encontrado.", font=("Segoe UI", 16), fg="white", bg="#003366").pack()
            return

        # Mostra dados do aluno
        for campo in ["Nome Completo", "ID", "Email", "Curso"]:
            valor = aluno[campo] if campo != "ID" else id_aluno
            tk.Label(resultado_frame, text=f"{campo}: {valor}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)

        # Mostra notas e faltas nas disciplinas do professor
        for disc in disciplinas.get(id_aluno, []):
            if disc["Professor"] != str(usuario_logado["id"]):
                continue

            disc_id = disc.get("ID")
            notas_aluno = notas.get(id_aluno, {}).get(disc_id, [])
            faltas_aluno = faltas.get(id_aluno, {}).get(disc_id, 0)

            tk.Label(
                resultado_frame,
                text=f"{disc['Nome da Diciplina']} - Notas: {' - '.join(str(n) for n in notas_aluno)} | Faltas: {faltas_aluno}",
                font=("Segoe UI", 16),
                fg="white",
                bg="#003366"
            ).pack(pady=1)

    tk.Button(frame, text="Consultar", command=consultar,
              bg="#0055AA", fg="white", font=("Segoe UI", 12, "bold"), width=20, height=2).pack(pady=10)

    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=2).pack(pady=20)

def montar_tela_notas1(frame):
    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")
    id_prof = str(usuario_logado["id"])

    tk.Label(frame, text="Notas e Faltas dos Alunos", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=20)

    for id_aluno, aluno in dados_al.items():
        # Mostra dados do aluno
        tk.Label(frame, text=f"Aluno: {aluno['Nome Completo']} (ID: {id_aluno})", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=5)

        # Para cada disciplina do aluno
        for disc in disciplinas.get(id_aluno, []):
            if disc["Professor"] != id_prof:
                continue  # ignora disciplinas de outro professor

            disc_id = disc.get("ID")
            notas_aluno = notas.get(id_aluno, {}).get(disc_id, [])
            faltas_aluno = faltas.get(id_aluno, {}).get(disc_id, 0)

            tk.Label(
                frame,
                text=f"{disc['Nome da Diciplina']} - Notas: {' - '.join(str(n) for n in notas_aluno)} | Faltas: {faltas_aluno}",
                font=("Segoe UI", 16),
                fg="white",
                bg="#003366"
                ).pack(pady=1)

    # Botão voltar
    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", 
              fg="white", 
              font=("Segoe UI", 12, "bold"), 
              width=12, 
              height=2
              ).pack(pady=20)

