#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long LLONG_INF = numeric_limits<long long>::max();

struct Edge
{
    int to;
    long long capacity;
    int rev;
};

vector<vector<Edge>> adj;
vector<int> level;
vector<int> iter;

void add_edge(int u, int v, long long cap)
{
    adj[u].push_back({v, cap, (int)adj[v].size()});
    adj[v].push_back({u, 0, (int)adj[u].size() - 1});
}

long long max_flow(int s, int t)
{
    long long flow = 0;
    while (true)
    {
        level.assign(adj.size(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (const auto &edge : adj[v])
            {
                if (edge.capacity > 0 && level[edge.to] < 0)
                {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }

        if (level[t] < 0)
        {
            break;
        }

        vector<int> parent_edge_idx(adj.size(), -1);
        vector<int> parent_node(adj.size(), -1);
        queue<int> path_q;
        path_q.push(s);

        while (!path_q.empty())
        {
            int u = path_q.front();
            path_q.pop();

            if (u == t)
                break;

            for (int i = 0; i < adj[u].size(); ++i)
            {
                Edge &e = adj[u][i];
                if (e.capacity > 0 && parent_node[e.to] == -1 && e.to != s)
                {
                    parent_node[e.to] = u;
                    parent_edge_idx[e.to] = i;
                    path_q.push(e.to);
                }
            }
        }

        if (parent_node[t] == -1)
        {
            break;
        }

        long long path_flow = LLONG_INF;
        for (int v = t; v != s; v = parent_node[v])
        {
            int u = parent_node[v];
            int edge_idx = parent_edge_idx[v];
            path_flow = min(path_flow, adj[u][edge_idx].capacity);
        }

        for (int v = t; v != s; v = parent_node[v])
        {
            int u = parent_node[v];
            int edge_idx = parent_edge_idx[v];
            adj[u][edge_idx].capacity -= path_flow;
            adj[v][adj[u][edge_idx].rev].capacity += path_flow;
        }
        flow += path_flow;
    }
    return flow;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X;
    while (cin >> X && X != -1)
    {
        vector<long long> controller_capacities(X + 1);
        for (int i = 1; i <= X; ++i)
        {
            cin >> controller_capacities[i];
        }

        int source = 0;
        int sink = 2 * X + 1;
        int num_nodes = 2 * X + 2;

        adj.assign(num_nodes, vector<Edge>());

        for (int i = 1; i <= X; ++i)
        {
            add_edge(i, X + i, controller_capacities[i]);
        }

        int Y;
        cin >> Y;
        for (int i = 0; i < Y; ++i)
        {
            int u, v;
            long long p;
            cin >> u >> v >> p;
            add_edge(X + u, v, p);
        }

        int E, S;
        cin >> E >> S;

        for (int i = 0; i < E + S; ++i)
        {
            int controller_id;
            cin >> controller_id;
            if (i < E)
            {
                add_edge(source, controller_id, LLONG_INF);
            }
            else
            {
                add_edge(X + controller_id, sink, LLONG_INF);
            }
        }

        cout << max_flow(source, sink) << endl;
    }

    return 0;
}