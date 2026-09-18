#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define getchar_unlocked _getchar_nolock
// ^ idk why but cf seems unhappy
// #define int long long
using namespace std;
int arr[4005][4005];
int presum[4005][4005];
int n, k;
int dp[4005][805];
int total = 0;
int li = 0, ri = 0;
int score(int l, int r) {
    return (presum[r+1][r+1] - presum[r+1][l] - presum[l][r + 1] + presum[l][l])/2;
    // while (ri < r) {
    //     total += presum[ri+1][ri + 1] - presum[ri+1][li];
    //     ri++;
    // }
    // while (li > l) {
    //     total += presum[li-1][ri + 1] - presum[li-1][li];
    //     li--;
    // }
    // while (ri > r) {
    //     total -= presum[ri][ri + 1] - presum[ri][li];
    //     ri--;
    // }
    // while (li < l) {
    //     total -= presum[li][ri + 1] - presum[li][li];
    //     li++;
    // }
    // return total;
}
void solve(int i, int l, int r, int lk, int rk) {
    int mid = (l + r) / 2;
    int bestval = INT_MAX, bestk = -1;
    for (int j = lk; j < min(mid +1 , rk); j++) {
        int val = score(j, mid);
        if (j != 0) val += dp[j-1][i-1];
        if (val < bestval) {
            bestval = val;
            bestk = j;
        }
    }
    dp[mid][i] = bestval;
    if (l < mid) solve(i, l, mid, lk, bestk+1);
    if (mid + 1 < r) solve(i, mid + 1, r, bestk, rk);
}
int getint() {
    char c = getchar_unlocked();
    while (!(c >= '0' && c <= '9')) c = getchar_unlocked();
    int ans = 0;
    while ((c >= '0' && c <= '9')) {
        ans = 10 * ans + (int)(c - '0');
        c = getchar_unlocked();
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    n = getint();
    k = getint();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = getint();
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            presum[i][j] = arr[i-1][j-1]  + (presum[i][j-1] + presum[i-1][j] - presum[i-1][j-1]);
        }
    }
    // cout<<score(0, 1)<<'\n';
    // cout<<score(0, 2)<<'\n';
    // cout<<score(0, 1)<<'\n';
    for (int i = 0; i < n; i++) {
        dp[i][0] = score(0, i);
    }
    for (int i = 1; i < k; i++) {
        solve(i, 0, n, 0, n);
    }
    cout<<dp[n-1][k-1]<<'\n';
}
