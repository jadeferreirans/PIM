import tkinter
import json

caminho_arq = "c:\\Users\\guile\\Desktop\\PIM\\proj_sistema_escolar\\interface\\notas.txt"
with open(caminho_arq, "r", encoding="utf-8") as f:
            partes = f.read().strip().split(";")

notas = {}
for i in range(0, len(partes), 5):
            id, A, B, C, D = partes[i:i+5]
            notas[id] = {
               "A": A,
               "B": B,
               "C": C,
               "D": D
            }
            

print(json.dumps(notas, indent=4, ensure_ascii=False))
