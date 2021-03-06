/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stas0.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie nieoptymalne, o zlozonosci O(n^2),            *
 *             dla kazdego wierzcholka z osobna oblicza sume odleglosci  *
 *             pozostalych od niego.                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 1000000
#define INFTY 100000000

int n;
vector<int> t[MAX_N];
int d[MAX_N];
queue<int> kol;

void bfs(int v)
{
  for (int i = 0; i < n; i++)
    d[i] = INFTY;
  d[v] = 0;
  kol = queue<int>();
  kol.push(v);
  while (!kol.empty())
  {
    int w = kol.front();
    kol.pop();
    for (int i = 0; i < (int)t[w].size(); i++)
      if (d[t[w][i]] == INFTY)
      {
        d[t[w][i]] = d[w] + 1;
        kol.push(t[w][i]);
      }
  }
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    t[a].push_back(b);
    t[b].push_back(a);
  }
  long long mx = -1;
  int wierzch = 0;
  for (int v = 0; v < n; v++)
  {
    bfs(v);
    long long akt = 0LL;
    for (int i = 0; i < n; i++)
      akt += d[i];
    if (akt > mx)
    {
      mx = akt;
      wierzch = v;
    }
  }
  printf("%d\n", wierzch + 1);
  return 0;
}
