from collections import deque


def pre_processar_arvore(grafo, raiz=1):

    n = len(grafo)
    profundidade = [-1] * n
    pai = [-1] * n

    # BFS para calcular profundidades e pais
    fila = deque([raiz])
    profundidade[raiz] = 0

    while fila:
        no_atual = fila.popleft()

        for vizinho in grafo[no_atual]:
            if profundidade[vizinho] == -1:
                profundidade[vizinho] = profundidade[no_atual] + 1
                pai[vizinho] = no_atual
                fila.append(vizinho)

    return profundidade, pai


def encontrar_caminho_rapido(profundidade, pai, a, b):

    if a == b:
        return [a]

    caminho = []

    if profundidade[a] < profundidade[b]:
        a, b = b, a

    caminho_a = [a]
    while profundidade[a] > profundidade[b]:
        a = pai[a]
        caminho_a.append(a)

    caminho_b = [b]
    while a != b:
        a = pai[a]
        b = pai[b]
        caminho_a.append(a)
        caminho_b.append(b)

    caminho_b.pop()  # Remover o LCA duplicado
    caminho = caminho_a + caminho_b[::-1]

    return caminho


def contar_presentes_distintos(caminho, presentes):

    presentes_distintos = set()

    for casa in caminho:
        presentes_distintos.add(
            presentes[casa - 1]
        )  # -1 porque os índices começam em 0

    return len(presentes_distintos)


def main():
    """
    Função principal que lê a entrada e processa as consultas.
    """
    n, m = map(int, input().split())
    presentes = input().split()

    grafo = [[] for _ in range(n + 1)]  # +1 porque as casas são numeradas de 1 a n

    for _ in range(n - 1):
        a, b = map(int, input().split())
        grafo[a].append(b)
        grafo[b].append(a)  # Grafo não direcionado

    profundidade, pai = pre_processar_arvore(grafo)

    for _ in range(m):
        a, b = map(int, input().split())
        caminho = encontrar_caminho_rapido(profundidade, pai, a, b)
        resultado = contar_presentes_distintos(caminho, presentes)
        print(resultado)


if __name__ == "__main__":
    main()
