#include <bits/stdc++.h>
#define int long long
using namespace std;
bool seen[35][35][55];
int cached[35][35][55];
int dp(int n, int m, int k) {
    if (seen[n][m][k]) return cached[n][m][k];
    seen[n][m][k] = true;
    if (k == 0) return cached[n][m][k] = 0;
    if (k == n * m) return cached[n][m][k] = 0;
    if (n == 0 || m == 0) return cached[n][m][k] = 1e12;
    int minval = 1e12;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            minval = min(minval, dp(i, m, j) + dp(n - i, m, k-j) + m * m);
        }
    }
    for (int i = 1; i < m; i++) {
        for (int j = 0; j <= k; j++) {
            minval = min(minval, dp(n, i, j) + dp(n, m - i, k-j) + n * n);
        }
    }
    return cached[n][m][k] = minval;
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    cout<<dp(n, m, k)<<'\n';
}
signed main() {
    int t;
    cin >> t;
    while (t--) solve();
}
