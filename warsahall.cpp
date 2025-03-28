#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
  int n;
  cin >> n;

  const int maiorNumero = 10000;

  // Alocar dinamicamente uma matriz nxn
  int **M = new int *[n];
  for (int i = 0; i < n; i++)
    M[i] = new int[n];

  // Ler valores iniciais da matriz
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      cin >> M[i][j];
      if (i != j && M[i][j] == 0)
      {
        M[i][j] = maiorNumero;
      }
    }

  // Algoritmo de Warshall
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        M[i][j] = min(M[i][j], (M[i][k] + M[k][j]));

  // Exibir matriz resultante
  cout << "Matriz de menor caminho:" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cout << M[i][j] << " ";
      
    cout << endl;
  }

  // Liberar memória alocada
  for (int i = 0; i < n; i++)
    delete[] M[i];
  delete[] M;

  return 0;
}