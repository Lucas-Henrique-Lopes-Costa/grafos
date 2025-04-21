from collections import deque
import math


def bfs(capacity, source, sink, parent):
    visited = [False] * len(capacity)
    queue = deque([source])
    visited[source] = True

    while queue:
        u = queue.popleft()

        for v in range(len(capacity)):
            if not visited[v] and capacity[u][v] > 0:
                queue.append(v)
                visited[v] = True
                parent[v] = u
                if v == sink:
                    return True
    return False


def min_trips(x, y, streets, a, b, c):
    capacity = [[0] * x for _ in range(x)]

    for u, v, p in streets:
        capacity[u - 1][v - 1] = p
        capacity[v - 1][u - 1] = p

    trips = 0

    while c > 0:
        parent = [-1] * len(capacity)

        if not bfs(capacity, a - 1, b - 1, parent):
            break

        path_capacity = float("Inf")
        s = b - 1
        while s != a - 1:
            path_capacity = min(path_capacity, capacity[parent[s]][s])
            s = parent[s]

        trips += 1
        c -= path_capacity

        v = b - 1
        while v != a - 1:
            u = parent[v]
            capacity[u][v] -= path_capacity
            capacity[v][u] += path_capacity
            v = parent[v]

    return trips


while True:
    x, y = map(int, input().split())
    if x == 0 and y == 0:
        break

    streets = []
    for _ in range(y):
        u, v, p = map(int, input().split())
        streets.append((u, v, p))

    a, b, c = map(int, input().split())

    print(min_trips(x, y, streets, a, b, c))
