import tkinter

# Usuarios.txt (logiin e senha)
caminho_arq = "C:\\PIM\\proj_sistema_escolar\\data\\usuarios.txt"
usuarios = {}

with open(caminho_arq, "r", encoding="utf-8") as f:
    linhas = f.read().strip().splitlines()

for linha in linhas:
    if not linha.strip():
        continue
    partes = linha.split(";")
    id, tipo, nome, senha = partes
    usuarios[id] = {
        "tipo": tipo,
        "nome": nome,
        "senha": senha
    }
    
def carregar_usuarios():
    global usuarios
    return usuarios

# Alunos.txt (dados)
caminho_arq = "C:\\PIM\\proj_sistema_escolar\\data\\alunos.txt"
dados_al = {}

with open(caminho_arq, "r", encoding="utf-8") as f:
    linhas = f.read().strip().splitlines()

for linha in linhas:
    if not linha.strip():
        continue

    partes = linha.split(";")
    if len(partes) < 6:
        continue  # pula linhas incompletas

    id_aluno, nome, cpf, email, telefone, curso = partes[:6]

    dados_al[id_aluno] = {
        "Nome Completo": nome,
        "CPF": cpf,
        "Email": email,
        "Telefone": telefone,
        "Curso": curso
    }


# professores.txt (dados)
caminho_arq = "C:\\PIM\\proj_sistema_escolar\\data\\professores.txt"
dados_prof = {}

with open(caminho_arq, "r", encoding="utf-8") as f:
    linhas = f.read().strip().splitlines()

for linha in linhas:
    if not linha.strip():
        continue

    partes = linha.split(";")
    if len(partes) < 4:
        continue

    id_prof, nome, email, cpf = partes[:4]

    dados_prof[id_prof] = {
        "Nome Completo": nome,
        "Email": email,
        "CPF": cpf
    }


#diciplinas.txt
caminho_arq = "C:\\PIM\\proj_sistema_escolar\\data\\disciplinas.txt"
disciplinas = {}

with open(caminho_arq, "r", encoding="utf-8") as f:
    linhas = f.read().strip().splitlines()

for linha in linhas:
    partes = linha.split(";")
    if len(partes) < 5:
        continue

    id_aluno = partes[0]
    nome = partes[1]
    prof = partes[2]
    total_aulas = partes[3]
    id_disc = partes[4]

    if id_aluno not in disciplinas:
        disciplinas[id_aluno] = []

    # adiciona cada disciplina como um dicionário na lista
    disciplinas[id_aluno].append({
        "ID": id_disc,
        "Nome da Diciplina": nome,
        "Professor": prof,
        "Total de Aulas": total_aulas
    })



# Notas.txt
caminho_notas = "C:\\PIM\\proj_sistema_escolar\\data\\notas.txt"
notas = {}

with open(caminho_notas, "r", encoding="utf-8") as f:
    linhas = f.read().strip().splitlines()

for linha in linhas:
    partes = linha.split(";")
    if len(partes) < 6:
        continue

    id_disc = partes[0]
    id_aluno = partes[1]
    lista_notas = partes[2:6]

    if id_aluno not in notas:
        notas[id_aluno] = {}

    notas[id_aluno][id_disc] = lista_notas


# Faltas.txt
caminho_faltas = "C:\\PIM\\proj_sistema_escolar\\data\\faltas.txt"
faltas = {}

with open(caminho_faltas, "r", encoding="utf-8") as f:
    linhas = f.read().strip().splitlines()

for linha in linhas:
    partes = linha.split(";")
    if len(partes) < 3:
        continue

    id_aluno = partes[0]
    id_disc = partes[1]
    falta_total = partes[2]

    if id_aluno not in faltas:
        faltas[id_aluno] = {}

    faltas[id_aluno][id_disc] = falta_total


def pegar_notas(id_aluno):
    if id_aluno not in notas:
        return "Nenhuma nota registrada."
    
    d = notas[id_aluno]

    texto = ""
    for disc, valor in d.items():
        texto += f"Disciplina {disc}: {valor}\n"

    return texto.strip()

