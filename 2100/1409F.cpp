// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
int n, m;
string a, b;
bool seen[205][205][205];
int cached[205][205][205];
int dp(int pos, int k, int num) {
    if(seen[pos][k][num]) return cached[pos][k][num];
    seen[pos][k][num] = 1;
    if(pos == n) return cached[pos][k][num] = 0;

    int maxval = 0;
    if(b[0] == b[1]) {
        if(k > 0) {
            maxval = max(maxval, dp(pos + 1, k-1, num+1) + num);
        }
        maxval = max(maxval, dp(pos + 1, k, num));
        if(a[pos] == b[0]) maxval = max(maxval, dp(pos + 1, k, num+1) + num);
    }
    if(k > 0) {
        maxval = max(maxval, dp(pos + 1, k-1, num+1));
        maxval = max(maxval, dp(pos + 1, k-1, num) + num);
    }
    maxval = max(maxval, dp(pos + 1, k, num));
    if(a[pos] == b[0]) maxval = max(maxval, dp(pos + 1, k, num+1));
    if(a[pos] == b[1]) maxval = max(maxval, dp(pos + 1, k, num) + num);
    return cached[pos][k][num] = maxval;
}
signed main() {
    cin >> n >> m;
    cin >> a >> b;
    cout<<dp(0, m, 0);
}
