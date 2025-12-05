import tkinter as tk
from defs import notas, faltas, dados_al, dados_prof, disciplinas

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

    tk.Label(frame, text="Área do Aluno", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=40)

    tk.Button(frame, text="Consultar seus dados", command=lambda: montar_tela_dados(frame),
              bg="#0055AA", fg="white", font=("Segoe UI", 12, "bold"), width=22, height=2).pack(pady=10)

    tk.Button(frame, text="Ver faltas", command=lambda: montar_tela_faltas(frame),
              bg="#0055AA", fg="white", font=("Segoe UI", 12, "bold"), width=22, height=2).pack(pady=10)

    tk.Button(frame, text="Ver notas", command=lambda: montar_tela_notas(frame),
              bg="#0055AA", fg="white", font=("Segoe UI", 12, "bold"), width=22, height=2).pack(pady=10)

    tk.Button(frame, text="Logout", command=logout_func,
              bg="#555555", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=2).pack(pady=20)

def montar_tela_dados(frame):
    for widget in frame.winfo_children():
        widget.destroy()
  
    frame.configure(bg="#003366")
    id_prof = usuario_logado["id"]

    # Pega os dados do professor do dicionário global
    prof = dados_prof.get(id_prof)
    tk.Label(frame, text="Seus dados", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=30)
    
    if prof:
        tk.Label(frame, text=f"Nome Completo: {prof['Nome Completo']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"ID: {id_prof}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"CPF: {prof['CPF']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"Email: {prof['Email']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"Telefone: {prof['Telefone']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
        tk.Label(frame, text=f"Curso: {prof['Curso']}", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=1)
    else:
        tk.Label(frame, text="Dados não encontrados.", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=20)

    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=2).pack(pady=20)


def montar_tela_faltas(frame):
    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")
    aluno_id = usuario_logado["id"]

    tk.Label(frame, text="Suas faltas", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=30)

    if aluno_id in faltas:
        texto = ""
        # percorre todas as disciplinas do aluno
        for disciplina in disciplinas[aluno_id]:
            id_disc = disciplina["ID"]
            nome_disc = disciplina["Nome da Diciplina"]
            falta = faltas.get(aluno_id, {}).get(id_disc, "0")
            texto += f"Disciplina {nome_disc} - Faltas: {falta}\n"
    else:
        texto = "Nenhuma falta registrada."

    tk.Label(frame, text=texto, font=("Segoe UI", 16), fg="white", bg="#003366", justify="left").pack(pady=20)
    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=2).pack(pady=20)


def montar_tela_notas(frame):
    for widget in frame.winfo_children():
        widget.destroy()

    frame.configure(bg="#003366")
    tk.Label(frame, text="Suas Notas", font=("Arial Black", 22), fg="white", bg="#003366").pack(pady=20)

    aluno_id = str(usuario_logado["id"])  # garantir string — compatível com o tratamento acima

    if aluno_id not in notas or not notas[aluno_id]:
        tk.Label(frame, text="Nenhuma nota encontrada.", font=("Segoe UI", 16), fg="white", bg="#003366").pack(pady=20)
        return

    texto = ""
    for disciplina in disciplinas[aluno_id]:
        id_disc = disciplina["ID"]
        nome_disc = disciplina["Nome da Diciplina"]
        lista_notas = notas.get(aluno_id, {}).get(id_disc, ["Sem notas"])
        texto += f"{nome_disc}: {' - '.join(lista_notas)}\n"

    tk.Label(frame, text=texto, font=("Segoe UI", 16), fg="white", bg="#003366", justify="left").pack(pady=20)

    tk.Button(frame, text="Voltar", command=lambda: montar_tela(frame),
              bg="#AA0000", fg="white", font=("Segoe UI", 12, "bold"), width=12, height=2).pack(pady=20)
