// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
int l, r;
int m[100005];
int total = 0;
vector<int> v;
int cost(int left, int right) {
    while (left < l) {
        total += m[v[l-1]];
        m[v[l-1]]++;
        l--;
    }
    while (right > r) {
        total += m[v[r+1]];
        m[v[r+1]]++;
        r++;
    }
    while (left > l) {
        m[v[l]]--;
        total -= m[v[l]];
        l++;
    }
    while (right < r) {
        m[v[r]]--;
        total -= m[v[r]];
        r--;
    }
    return total;
}
int dp[21][100005];
void solve(int i, int l, int r, int left, int right) {
    int bestval = LONG_LONG_MAX, bestk = 0;
    int mid = (l + r) / 2;
    for (int k = left; k <= right; k++) {
        int val = cost(k, mid);
        if (k != 0) val += dp[i-1][k-1];
        if (val < bestval) {
            bestval = val;
            bestk = k;
        }
    }
    dp[i][mid] = bestval;
    if (l + 1 == r) return;
    solve(i, l, mid, left, bestk + 1);
    solve(i, mid, r, bestk, right);
}
signed main() {
    int n, k;
    cin >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    l = 0, r = 0, total = 0;
    m[v[0]] = 1;
    for (int i = 0; i < n; i++) {
        dp[0][i] = cost(0, i);
    }
    for (int i = 1; i < k; i++) {
        solve(i, 0, n, 0, n);
    }
    cout<<dp[k-1][n-1]<<'\n';
}
