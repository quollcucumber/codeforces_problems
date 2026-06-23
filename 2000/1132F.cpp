// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
string s;
bool seen[505][505];
int cached[505][505];
int dp(int l, int r) {
    if(l == 2 && r == 5) {
        int q = 8;
    }
    if(l > r) return 0;
    if(seen[l][r]) return cached[l][r];
    seen[l][r] = true;
    int startl = l;
    int startr = r;
    while(l != r && s[l] == s[l+1]) l++;
    if(l == r) return cached[startl][startr] = 1;
    int minval = dp(l + 1, r) + 1;
    for(int point = l +1; point <= r; point++) {
        if(s[point] == s[l]) {
            // while(point != r && s[point+1] == s[l]) point++;
            minval = min(minval, dp(l+1, point-1) + dp(point, r));
        }
    }
    // cerr<<l << ' ' << r<<' '<<minval<<'\n';
    return cached[startl][startr] = minval;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    cin >> s;
    cout<<dp(0, n-1)<<'\n';
}
