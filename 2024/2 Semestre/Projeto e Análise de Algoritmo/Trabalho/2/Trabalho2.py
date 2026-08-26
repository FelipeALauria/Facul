# Alunos: Bruna Fontes e Felipe do Amparo
"""
    Como executar no terminal:

        --- se for criar um novo grafo

            python3 Trabalho2.py tamanho --densidade x --algoritmo xxxx --salvar xxxxx.json

                tamanho: inteiro (10, 100, 500, 1000, 2000, 5000 ou 10000)
                densidade: d (denso) ou e (esparso)
                algoritmo: kruskal ou prim
                nome_de_arquivo.json
        
        --- se for carregar o grafo já criado

            python3 Trabalho2.py 100 --algoritmo kruskal --carregar grafo_100_denso_kruskal.json
    
"""
# bibliotecas
import heapq
import random
import argparse
import time
import json

# função main
def main():
     # configuração dos argumentos da linha de comando
    parser = argparse.ArgumentParser(description="Executar o algoritmo de Prim em um grafo.")
    parser.add_argument("num_vertices", type=int, help="Número de vértices do grafo")
    parser.add_argument("--densidade", choices=["e", "d"], default="esparso",
                        help="Densidade do grafo: 'esparso' ou 'denso' (padrão: esparso)")
    parser.add_argument("--raiz", type=int, default=0, help="Vértice inicial (padrão: 0)")
    parser.add_argument("--algoritmo", choices=["prim", "kruskal"], required=True,
                        help="Algoritmo a ser utilizado: 'prim' ou 'kruskal'")
    parser.add_argument("--salvar", type=str, help="Caminho do arquivo para salvar o grafo gerado")
    parser.add_argument("--carregar", type=str, help="Caminho do arquivo para carregar um grafo existente")

    args = parser.parse_args()
    num_vertices = args.num_vertices
    densidade = args.densidade
    raiz = args.raiz
    algoritmo = args.algoritmo

    # gerar grafo
    if args.carregar:
        grafo = carregar_grafo(args.carregar)
        print(f"Grafo carregado de {args.carregar}")
    else:
        grafo = gerar_grafo_conexo(num_vertices, densidade=densidade)
        if args.salvar:
            salvar_grafo(grafo, args.salvar)
            print(f"Grafo salvo em {args.salvar}")

    # conferindo se está funcionando corretamente
    print()
    print(f"Número de vértices: {grafo.num_vertices}")
    print(f"Número de arestas: {len(grafo.arestas)}")
    print()

    for i, (peso, u, v) in enumerate(grafo.arestas[:10]):  # amostra de 10 arestas para verificação
        print(f"Aresta {i}: ({u}, {v}) com peso {peso}")

    # escolha do algoritmo
    if algoritmo == "prim":
        agm = prim(grafo)
    elif algoritmo == "kruskal":
        agm = kruskal(grafo)

    # legenda
    print()
    print(f"\nÁrvore Geradora Mínima \nalgoritmo de {algoritmo.capitalize()}\n{num_vertices} vértices")
    
    # cálculo de tempo de execução
    tempo = tempo_execucao(prim if algoritmo == "prim" else kruskal, grafo)
    print(f"\nTempo de execução do algoritmo {algoritmo.capitalize()}: {tempo:.6f} segundos")
    print()

"""
            Definições e Funções Auxiliares
"""
class Grafo:
    def __init__(self, num_vertices):
        self.num_vertices = num_vertices
        # lista de adjacência
        self.adj = {i: [] for i in range(num_vertices)}  
        self.arestas = []

    def adicionar_aresta(self, u, v, peso):
        self.adj[u].append((v, peso))
        self.adj[v].append((u, peso))  # grafo não é direcionado
        # para o algoritmo de Kruskal
        self.arestas.append((peso, u, v))  

def gerar_grafo_conexo(num_vertices, densidade="e"):

    grafo = Grafo(num_vertices)

    # árvore inicial 
    for i in range(num_vertices - 1):
        peso = random.randint(1, 10)
        grafo.adicionar_aresta(i, i + 1, peso)

    # arestas extras para criar densidade
    if densidade == "e":
        num_arestas = min(num_vertices * 2, (num_vertices * (num_vertices - 1)) // 4)
    else:
        num_arestas = (num_vertices * (num_vertices - 1)) // 2 
    
    while len(grafo.arestas) < num_arestas:
        u, v = random.sample(range(num_vertices), 2)
        # evitar arestas duplicadas:
        if v not in [adj[0] for adj in grafo.adj[u]]:  
            peso = random.randint(1, 10)
            grafo.adicionar_aresta(u, v, peso)

    return grafo

# printa o grafo em formato de lista de adjacência
def printar_grafo(grafo):
    print("Grafo:")
    for vertice, adjacentes in grafo.adj.items():
        conexoes = ", ".join([f"{v}(peso={peso})" for v, peso in adjacentes])
        print(f"Vértice {vertice}: {conexoes}")
    print("\n")

# calcular o tempo de execução
def tempo_execucao(funcao, *args):
    inicio = time.time()
    funcao(*args)
    fim = time.time()
    return fim - inicio

# para realizar testes com o mesmo grafo
def salvar_grafo(grafo, nome_arquivo):
    with open(nome_arquivo, 'w') as arquivo:
        json.dump({
            "num_vertices": grafo.num_vertices,
            "arestas": grafo.arestas
        }, arquivo)

def carregar_grafo(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        dados = json.load(arquivo)
        grafo = Grafo(dados["num_vertices"])
        for peso, u, v in dados["arestas"]:
            grafo.adicionar_aresta(u, v, peso)
        return grafo

"""
            ALGORITMO DE PRIM

"""
def prim(grafo, raiz=0):
    
    num_vertices = grafo.num_vertices
    chave = [float('inf')] * num_vertices
    pai = [None] * num_vertices
    chave[raiz] = 0

    # fila de prioridade mínima (heap)
    fila_prioridade = [(0, raiz)]  # (peso, vértice)
    visitado = [False] * num_vertices

    agm = []
    peso_total = 0
    while fila_prioridade:
        peso, u = heapq.heappop(fila_prioridade)
        if visitado[u]:
            continue

        visitado[u] = True
        peso_total += peso
        for v, peso in grafo.adj[u]:
            if not visitado[v] and peso < chave[v]:
                chave[v] = peso
                pai[v] = u
                heapq.heappush(fila_prioridade, (peso, v))

    # árvore geradora mínima
    agm = [(pai[i], i, chave[i]) for i in range(num_vertices) if pai[i] is not None]
    
    print(f"Peso total da AGM: {peso_total}")
    print(f"Número de arestas na AGM: {len(agm)}")
    return agm

"""
            ALGORITMO DE KRUSKAL

"""
# estrutura de dados usada pelo algoritmo
class UnionFind:
    def __init__(self, n):
        self.pai = list(range(n))  
        self.rank = [0] * n  

    def find(self, u):
        if self.pai[u] != u:
            self.pai[u] = self.find(self.pai[u])  # caminho comprimido
        return self.pai[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)

        if root_u != root_v:
            # união pelo rank 
            if self.rank[root_u] > self.rank[root_v]:
                self.pai[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.pai[root_u] = root_v
            else:
                self.pai[root_v] = root_u
                self.rank[root_u] += 1
            return True
        return False

def kruskal(grafo):
    
    # ordena as arestas pelo peso
    grafo.arestas.sort()  
    
    uf = UnionFind(grafo.num_vertices)
    agm = []

    for peso, u, v in grafo.arestas:
        if uf.union(u, v):  # verificar se há formação de ciclo
            agm.append((u, v, peso))

    return agm

"""
            EXECUÇÃO DA MAIN
"""
if __name__ == "__main__":
   main()
