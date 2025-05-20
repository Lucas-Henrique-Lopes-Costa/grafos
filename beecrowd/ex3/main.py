import sys
import heapq

input = sys.stdin.readline


def dijkstra(n, graph, s, t, c, max_pedagio):
    dist = [float("inf")] * (n + 1)
    dist[s] = 0
    pq = [(0, s)]

    while pq:
        custo, u = heapq.heappop(pq)
        if custo > c:
            continue
        if u == t:
            return True
        for v, w in graph[u]:
            if w > max_pedagio:
                continue
            if dist[v] > custo + w:
                dist[v] = custo + w
                heapq.heappush(pq, (dist[v], v))
    return False


def main():
    T = int(input())
    for _ in range(T):
        n, m, s, t, c = map(int, input().split())
        graph = [[] for _ in range(n + 1)]
        max_pedagio = 0
        min_pedagio = 100_001
        for _ in range(m):
            u, v, w = map(int, input().split())
            graph[u].append((v, w))
            max_pedagio = max(max_pedagio, w)
            min_pedagio = min(min_pedagio, w)

        l, r = min_pedagio, max_pedagio
        resposta = -1
        while l <= r:
            mid = (l + r) // 2
            if dijkstra(n, graph, s, t, c, mid):
                resposta = mid
                r = mid - 1
            else:
                l = mid + 1
        print(resposta)


if __name__ == "__main__":
    main()
