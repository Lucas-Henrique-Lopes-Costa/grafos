#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int bfs_maior_pedagio(int n, int s, int t, int c, vector<vii> &adj)
{
  queue<pair<pair<int, int>, int>> fila;
  fila.push({{s, 0}, 0});

  set<pair<int, int>> visitados;

  int maior_pedagio_encontrado = -1;

  while (!fila.empty())
  {
    int no_atual = fila.front().first.first;
    int custo_atual = fila.front().first.second;
    int maior_pedagio_atual = fila.front().second;
    fila.pop();

    if (no_atual == t)
    {
      maior_pedagio_encontrado = max(maior_pedagio_encontrado, maior_pedagio_atual);
      continue;
    }

    pair<int, int> estado = {no_atual, maior_pedagio_atual};
    if (visitados.count(estado))
      continue;

    visitados.insert(estado);

    for (auto &edge : adj[no_atual])
    {
      int vizinho = edge.first;
      int pedagio = edge.second;

      int novo_custo_total = custo_atual + pedagio;

      if (novo_custo_total <= c)
      {
        int novo_maior_pedagio = max(maior_pedagio_atual, pedagio);
        fila.push({{vizinho, novo_custo_total}, novo_maior_pedagio});
      }
    }
  }

  return maior_pedagio_encontrado;
}

int solve()
{
  int n, m, s, t, c;
  cin >> n >> m >> s >> t >> c;

  vector<vii> adj(n + 1);
  for (int i = 0; i < m; ++i)
  {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
  }

  return bfs_maior_pedagio(n, s, t, c, adj);
}

int main()
{
  int num_test_cases;
  cin >> num_test_cases;

  while (num_test_cases--)
  {
    cout << solve() << endl;
  }

  return 0;
}