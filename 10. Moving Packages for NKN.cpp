#include <bits/stdc++.h>
using namespace std;
const int mNum = 300011;
char s[mNum];
int Dg[mNum], d[mNum];
vector<int> w[mNum];
int F(int u, int c) {
  if (d[u] != -1) return d[u];
  d[u] = 0;
  for (int v : w[u]) {
    d[u] = max(d[u], F(v, c));
  }
  d[u] += (s[u] == c + 'a');
  return d[u];
}
int main() {
  int x, m;
  scanf("%d%d", &x, &m);
  scanf("%s", s + 1);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    w[u].push_back(v);
    ++Dg[v];
  }
  int ct = 0;
  queue<int> qu;
  for (int i = 1; i <= x; ++i) {
    if (!Dg[i])
      qu.push(i), ++ct;
  }
  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();
    for (int v : w[u]) {
      if (--Dg[v] == 0)
        qu.push(v), ++ct;
    }
  }
  if (ct < x) {
    puts("-1");
  } else {
    int ansr = 0;
    for (int c = 0; c < 26; ++c) {
      memset(d, 0xff, sizeof d);
      for (int i = 1; i <= x; ++i)
        ansr = max(ansr, F(i, c));
    }
    printf("%d\n", ansr);
  }
  return 0;
}