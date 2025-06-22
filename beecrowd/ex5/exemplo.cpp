#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

bool bfs(vector<vector<long long>>& grafoResidual, int origem, int destino, vector<int>& pai) {
    int n = grafoResidual.size();
    vector<bool> visitado(n, false);
    queue<int> fila;

    fila.push(origem);
    visitado[origem] = true;
    pai[origem] = -1;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v = 0; v < n; ++v) {
            if (!visitado[v] && grafoResidual[u][v] > 0) {
                fila.push(v);
                pai[v] = u;
                visitado[v] = true;
                if (v == destino) {
                    return true;
                }
            }
        }
    }
    return visitado[destino];
}

long long edmondsKarp(vector<vector<long long>>& grafo, int origem, int destino) {
    int n = grafo.size();
    vector<vector<long long>> grafoResidual = grafo;
    vector<int> pai(n);
    long long fluxoMaximo = 0;

    while (bfs(grafoResidual, origem, destino, pai)) {
        long long fluxoCaminho = LLONG_MAX;
        for (int v = destino; v != origem; v = pai[v]) {
            int u = pai[v];
            fluxoCaminho = min(fluxoCaminho, grafoResidual[u][v]);
        }

        for (int v = destino; v != origem; v = pai[v]) {
            int u = pai[v];
            grafoResidual[u][v] -= fluxoCaminho;
            grafoResidual[v][u] += fluxoCaminho;
        }

        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numControladores;
    while (cin >> numControladores && numControladores != -1) {
        
        int numNos = 2 * numControladores + 2;
        int origemGlobal = 0;
        int destinoGlobal = numNos - 1;

        vector<vector<long long>> grafo(numNos, vector<long long>(numNos, 0));

        for (int i = 1; i <= numControladores; ++i) {
            long long capacidade;
            cin >> capacidade;
            grafo[2 * i - 1][2 * i] = capacidade;
        }

        int numLigacoes;
        cin >> numLigacoes;
        for (int i = 0; i < numLigacoes; ++i) {
            int u, v;
            long long p;
            cin >> u >> v >> p;
            grafo[2 * u][2 * v - 1] = p;
        }

        int numEntradas, numSaidas;
        cin >> numEntradas >> numSaidas;

        for (int i = 0; i < numEntradas; ++i) {
            int u;
            cin >> u;
            grafo[origemGlobal][2 * u - 1] = LLONG_MAX;
        }

        for (int i = 0; i < numSaidas; ++i) {
            int u;
            cin >> u;
            grafo[2 * u][destinoGlobal] = LLONG_MAX;
        }

        cout << edmondsKarp(grafo, origemGlobal, destinoGlobal) << "\n";
    }

    return 0;
}