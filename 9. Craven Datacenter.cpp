#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5+5;

ll n, k, block[N], ind, val[20*N], sum[20*N], chars[20*N][2], start[N], nums[N], save[N];
pair<ll, ll>  sorted_nums[N], s[N];
ll ar1[N], ar2[N];

void build(int l = 0, int r = 2*n-1) {
    ind++; int cx = ind;
    if (l == r)
        return;
    chars[cx][0] = ind+1; build(l, (l+r)/2);
    chars[cx][1] = ind+1; build((l+r)/2 + 1, r);
}

void insert(int i, int l, int r, int ind1) {
    ind++;
    if (l == 0 && r == 2*n-1)
        start[i+1] = ind;
    val[ind] = val[ind1]+1;
    sum[ind] = sum[ind1]+nums[i];
    if (l == r) return;
    int middle_i = (l+r)/2; 
    if (save[i] <= middle_i) {
        chars[ind][0] = ind+1; chars[ind][1] = chars[ind1][1];
        insert(i, l, middle_i, chars[ind1][0]);
    } else {
        chars[ind][1] = ind+1; chars[ind][0] = chars[ind1][0];
        insert(i, middle_i+1, r, chars[ind1][1]);
    }
}

ll check(int l, int r) {
    ll ind1 = start[l], ind2 = start[r+1];
    ll l1 = 0, r1 = 2*n-1;
    ll s = 0, x = (r-l+1)/2;
    while (x != 0) {
        int middle_i = (l1+r1)/2;
        if (val[chars[ind2][0]]-val[chars[ind1][0]] <= x) {
            x -= (val[chars[ind2][0]]-val[chars[ind1][0]]);
            s += (sum[chars[ind2][0]]-sum[chars[ind1][0]]);
            l1 = middle_i+1; ind1 = chars[ind1][1]; ind2 = chars[ind2][1];
        } else {
            r1 = middle_i; ind1 = chars[ind1][0]; ind2 = chars[ind2][0];
        }
    }
    return block[r+1]-block[l]-2*s;
}

void traverse(int l, int r, int start_i, int end_i) {
    if (r < l) return;
    int middle_i = (l+r)/2, index = -1;
    ar1[middle_i] = 1e18;
    for (int i = start_i; i <= min(end_i, middle_i); i++) {
        ll cur = ar2[i-1]+check(2*i, 2*middle_i+1);
        if (cur < ar1[middle_i]) ar1[middle_i] = cur, index = i;
    }
    traverse(l,middle_i-1,start_i,index);
    traverse(middle_i+1,r,index,end_i);
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> sorted_nums[i].first >> sorted_nums[i].second;
        sorted_nums[i].first += sorted_nums[i].second;
    }
    sort(sorted_nums, sorted_nums+n);
    for (int i = 0; i < n; i++) {
        nums[2*i] = sorted_nums[i].first-sorted_nums[i].second;
        nums[2*i+1] = sorted_nums[i].second;
        s[2*i] = pair<ll, ll> (nums[2*i], 2*i);
        s[2*i+1] = pair<ll, ll> (nums[2*i+1], 2*i+1);
    }
    for (int i = 0; i < 2*n; i++)
        block[i+1] = block[i]+nums[i];

    sort(s, s+2*n);
    for (int i = 0; i < 2*n; i++) save[s[i].second] = i;
    start[0] = 1;
    build();
    for (int i = 0; i < 2*n; i++) insert(i, 0, 2*n-1, start[i]);
    for (int i = 0; i < n; i++) ar2[i] = check(0, 2*i+1);
    for (int j = 2; j <= k; ++j) {
        traverse(0, n-1, 0, n-1);
        for (int i = 0; i < n; i++)
            ar2[i] = ar1[i];
    }

    cout << ar2[n-1] << endl;
}