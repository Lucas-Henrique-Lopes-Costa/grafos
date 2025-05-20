#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int dijkstra(int n, int s, int t, int c, vector<vii> &adj)
{
  vector<pair<int, int>> dist(n + 1, {1e9, 0});
  dist[s] = {0, 0};

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, s});

  while (!pq.empty())
  {
    int d = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (d > dist[u].first)
      continue;

    for (auto &edge : adj[u])
    {
      int v = edge.first;
      int weight = edge.second;

      int new_cost = dist[u].first + weight;
      int new_max_toll = max(dist[u].second, weight);

      if (new_cost <= c && new_cost < dist[v].first)
      {
        dist[v].first = new_cost;
        dist[v].second = new_max_toll;
        pq.push({new_cost, v});
      }
      else if (new_cost <= c && new_cost == dist[v].first && new_max_toll > dist[v].second)
      {
        dist[v].second = new_max_toll;
      }
    }
  }

  if (dist[t].first == 1e9)
  {
    return -1;
  }
  else
  {
    return dist[t].second;
  }
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

  return dijkstra(n, s, t, c, adj);
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