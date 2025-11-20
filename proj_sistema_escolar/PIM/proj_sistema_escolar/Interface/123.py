import tkinter

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
        
