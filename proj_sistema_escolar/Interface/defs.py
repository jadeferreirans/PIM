import tkinter

caminho_arq = "c:\\Users\\guile\\Desktop\\PIM\\proj_sistema_escolar\\data\\usuarios.txt"
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
caminho_arq = "c:\\Users\\guile\\Desktop\\PIM\\proj_sistema_escolar\\interface\\notas.txt"
with open(caminho_arq, "r", encoding="utf-8") as f:
    partes = f.read().strip().split(";")

notas = {}
for i in range(0, len(partes), 9):
    id, A, notaA, B, notaB, C, notaC, D, notaD = partes[i:i+9]
    notas[id] = {
        A: notaA,
        B: notaB,
        C: notaC,
        D: notaD 
            
    }
        
caminho_arq = "c:\\Users\\guile\\Desktop\\PIM\\proj_sistema_escolar\\interface\\faltas.txt"
with open(caminho_arq, "r", encoding="utf-8") as f:
    partes = f.read().strip().split(";")

faltas = {}
for i in range(0, len(partes), 9):
    id, A, faltasA, B, faltasB, C, faltasC, D, faltasD = partes[i:i+9]
    faltas[id] = {
        A: faltasA,
        B: faltasB,
        C: faltasC,
        D: faltasD
    }
    
def pegar_notas(id_aluno):
        if id_aluno not in notas:
            return "Nenhuma nota registrada."

        d = notas[id_aluno]

        return (
            f"Disciplina A: {d['A']}\n"
            f"Disciplina B: {d['B']}\n"
            f"Disciplina C: {d['C']}\n"
            f"Disciplina D: {d['D']}"
        )