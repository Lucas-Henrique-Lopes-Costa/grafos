#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<string> presents;
vector<int> depth;
vector<int> parent;
int N_nodes_global;

void bfs_preprocess(int start_node) {
    depth.assign(N_nodes_global + 1, -1);
    parent.assign(N_nodes_global + 1, 0);

    queue<int> q;

    q.push(start_node);
    depth[start_node] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

int count_distinct_presents(int u, int v) {
    set<string> distinct_presents;

    if (u == v) {
        distinct_presents.insert(presents[u - 1]);
        return distinct_presents.size();
    }

    vector<int> path_u_to_root;
    vector<int> path_v_to_root;

    int current_u = u;
    while (current_u != 0) {
        path_u_to_root.push_back(current_u);
        current_u = parent[current_u];
    }
    reverse(path_u_to_root.begin(), path_u_to_root.end());

    int current_v = v;
    while (current_v != 0) {
        path_v_to_root.push_back(current_v);
        current_v = parent[current_v];
    }
    reverse(path_v_to_root.begin(), path_v_to_root.end());

    size_t i = 0; 
    while (i < path_u_to_root.size() && i < path_v_to_root.size() && path_u_to_root[i] == path_v_to_root[i]) {
        i++;
    }

    for (size_t j = i - 1; j < path_u_to_root.size(); ++j) {
        distinct_presents.insert(presents[path_u_to_root[j] - 1]);
    }

    for (size_t j = i - 1; j < path_v_to_root.size(); ++j) {
        distinct_presents.insert(presents[path_v_to_root[j] - 1]);
    }
    
    return distinct_presents.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M_queries;
    cin >> N_nodes_global >> M_queries;

    presents.resize(N_nodes_global);
    for (int i = 0; i < N_nodes_global; ++i) {
        cin >> presents[i];
    }

    adj.resize(N_nodes_global + 1);
    for (int i = 0; i < N_nodes_global - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs_preprocess(1);

    for (int i = 0; i < M_queries; ++i) {
        int A, B;
        cin >> A >> B;
        cout << count_distinct_presents(A, B) << "\n";
    }

    return 0;
}