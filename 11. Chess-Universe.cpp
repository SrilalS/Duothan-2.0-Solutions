#include <stdio.h>
#include <bits/stdtr1c++.h>
 
#define MOD 88883
#define valid(i, j) ((i) >= 0 && (i) < n && (j) >= 0 && (j) < m)
 
using namespace std;
 
const int dx[] = {0, 0, -1, 1, 1, 1, -1, -1};
const int dy[] = {-1, 1, 0, 0, 1, -1, 1, -1};
 
long long num[8][8];
char str[10][10], pattern[20];
int n, m, p, counter[8][8][100010] = {0};
unsigned long long hashmap[8][8][100010] = {0};
 
inline void add(int i, int j, unsigned long long mask){
    int k = ++mask % MOD;
    while (hashmap[i][j][k] && hashmap[i][j][k] != mask) k++;
    hashmap[i][j][k] = mask, counter[i][j][k]++;
}
 
inline int get(int i, int j, unsigned long long mask){
    int k = ++mask % MOD;
    while (hashmap[i][j][k] && hashmap[i][j][k] != mask) k++;
    return counter[i][j][k];
}
 
void insert(int i, int j, int c, int lim, unsigned long long mask){
    if (c > lim){
        add(i, j, 0);
        for (unsigned long long k = mask; k > 0; k = (k - 1) & mask){
            add(i, j, k);
        }
        return;
    }
 
    int d, k, l;
    for (d = 0; d < 8; d++){
        k = i + dx[d], l = j + dy[d];
        if (valid(k, l) && str[k][l] == pattern[c] && !(mask & num[k][l])){
            insert(k, l, c + 1, lim, mask | num[i][j]);
        }
    }
}
 
void count(int i, int j, int c, int lim, unsigned long long mask, long long& res){
    if (c < lim){
        res += get(i, j, 0);
        for (unsigned long long k = mask; k > 0; k = (k - 1) & mask){
            if (__builtin_popcountll(k) & 1) res -= get(i, j, k);
            else res += get(i, j, k);
        }
        return;
    }
 
    int d, k, l;
    for (d = 0; d < 8; d++){
        k = i + dx[d], l = j + dy[d];
        if (valid(k, l) && str[k][l] == pattern[c] && !(mask & num[k][l])){
            count(k, l, c - 1, lim, mask | num[i][j], res);
        }
    }
}
 
long long solve(){
    int i, j, h = 0, lim = p / 2;
 
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            num[i][j] = 1LL << h++;
        }
    }
 
 
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            if (str[i][j] == pattern[0]){
                insert(i, j, 1, lim, 0);
            }
        }
    }
 
    long long res = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            if (str[i][j] == pattern[p - 1]){
                count(i, j, p - 2, lim, 0, res);
            }
        }
    }
    return res;
}
 
int main(){
    int i, j, k, l;
 
    n = 8, m = 8;
    scanf("%d", &p);
    assert(p >= 1 && p <= 11);
    scanf("%s", pattern);
    assert(strlen(pattern) == p);
    for (i = 0; i < p; i++) assert(pattern[i] >= 'a' && pattern[i] <= 'z');
 
    assert(n == 8 && m == 8);
    for (i = 0; i < n; i++){
        assert(scanf("%s", str[i]) != EOF);
        assert(strlen(str[i]) == m);
        for (j = 0; j < m; j++){
            assert(str[i][j] >= 'a' && str[i][j] <= 'z');
        }
    }
 
    cout << solve() << endl;
    return 0;
}