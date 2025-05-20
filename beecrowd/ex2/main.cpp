#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef long long ll;
typedef pair<ll, pair<int, int>> state;
const ll INF = 1e18;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int C, V;
  cin >> C >> V;
  vector<vector<pair<int, int>>> grafo(C + 1);
  for (int i = 0; i < V; i++)
  {
    int u, v, custo;
    cin >> u >> v >> custo;
    grafo[u].emplace_back(v, custo);
    grafo[v].emplace_back(u, custo);
  }

  vector<vector<ll>> dist(C + 1, vector<ll>(2, INF));
  dist[1][0] = 0;

  priority_queue<state, vector<state>, greater<state>> pq;
  pq.push({0, {1, 0}});

  while (!pq.empty())
  {
    auto [custo_atual, estado] = pq.top();
    auto [cidade, paridade] = estado;
    pq.pop();

    if (custo_atual != dist[cidade][paridade])
      continue;

    for (auto &[prox, pedagio] : grafo[cidade])
    {
      int nova_paridade = 1 - paridade;
      ll novo_custo = custo_atual + pedagio;
      if (novo_custo < dist[prox][nova_paridade])
      {
        dist[prox][nova_paridade] = novo_custo;
        pq.push({novo_custo, {prox, nova_paridade}});
      }
    }
  }

  if (dist[C][0] == INF)
    cout << -1 << "\n";
  else
    cout << dist[C][0] << "\n";

  return 0;
}