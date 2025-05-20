import sys
import heapq

def solve():
    data = sys.stdin.read().strip().split()
    # Se não houver dados de entrada, encerra a execução
    if not data:
        return
    
    it = iter(data)
    C = int(next(it))
    V = int(next(it))
    
    # Cria o grafo utilizando lista de adjacência (1-indexado)
    graph = [[] for _ in range(C + 1)]
    for _ in range(V):
        u = int(next(it))
        v = int(next(it))
        toll = int(next(it))
        graph[u].append((v, toll))
        graph[v].append((u, toll))
    
    # Dijkstra com estado de paridade: 
    # 0 indica número par de pedágios; 1 indica número ímpar.
    INF = float('inf')
    dist = [[INF, INF] for _ in range(C + 1)]
    dist[1][0] = 0
    heap = [(0, 1, 0)]  # (custo, nó, paridade)
    
    while heap:
        cost, u, parity = heapq.heappop(heap)
        if cost > dist[u][parity]:
            continue
        for v, toll in graph[u]:
            new_cost = cost + toll
            new_parity = 1 - parity  # alterna a paridade
            if new_cost < dist[v][new_parity]:
                dist[v][new_parity] = new_cost
                heapq.heappush(heap, (new_cost, v, new_parity))
    
    # Queremos chegar à cidade C com número par de pedágios (paridade 0)
    print(dist[C][0] if dist[C][0] != INF else -1)

if __name__ == '__main__':
    # Se estiver em modo interativo (sem redirecionamento de arquivo), 
    # é possível ler da entrada padrão linha a linha.
    if sys.stdin.isatty():
        input_lines = []
        try:
            while True:
                line = input()
                if line == "":
                    break
                input_lines.append(line)
        except EOFError:
            pass
        sys.stdin = sys.__stdin__ = open(0)  # redefine a stdin se necessário
        sys.stdin = open("".join(input_lines), "r")
    solve()