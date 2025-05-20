#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

typedef pair<int, int> ii;
const int INF = numeric_limits<int>::max();

int maxBottleneckPath(int n, int origem, int destino, const vector<vector<ii>> &grafo)
{
  vector<int> capacidade(n + 1, 0);
  capacidade[origem] = INF;

  priority_queue<ii> pq;
  pq.push({capacidade[origem], origem});

  while (!pq.empty())
  {
    int cap_atual = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (u == destino)
      break;

    if (cap_atual < capacidade[u])
      continue;

    for (auto &edge : grafo[u])
    {
      int v = edge.first;
      int cap_aresta = edge.second;
      int novaCap = min(capacidade[u], cap_aresta);
      if (novaCap > capacidade[v])
      {
        capacidade[v] = novaCap;
        pq.push({capacidade[v], v});
      }
    }
  }
  return capacidade[destino];
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  while (true)
  {
    int n, r;
    cin >> n >> r;
    if (n == 0 && r == 0)
      break;

    vector<vector<ii>> grafo(n + 1, vector<ii>());
    for (int i = 0; i < r; i++)
    {
      int u, v, cap;
      cin >> u >> v >> cap;
      grafo[u].push_back({v, cap});
      grafo[v].push_back({u, cap});
    }

    int A, B, C;
    cin >> A >> B >> C;

    int maxCap = maxBottleneckPath(n, A, B, grafo);

    int capEfetiva = maxCap - 1;

    int viagens = (C + capEfetiva - 1) / capEfetiva;

    cout << viagens << "\n";
  }
  return 0;
}