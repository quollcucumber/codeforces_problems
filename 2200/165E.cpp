#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
// #define int long long
using namespace std;
bool seen[4194310];
bool inarr[4194310];
int cached[4194310];

int dp(int val) {
    // cerr<<val<<'\n';
    if (seen[val]) return cached[val];
    seen[val] = true;
    if (inarr[val]) return cached[val] = val;
    for (int i = 0; i < 22; i++) {
        int a = 1 << i;
        if (val % (a * 2) / a == 1) {
            if (dp(val - a)) {
                return cached[val] = dp(val-a);
            }
        }
    }
    return cached[val] = 0;
}
signed main() {
    int a = 1;
    for (int i = 0 ; i < 21; i++) {
        a *= 2;
        a ++;
    }
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0 ; i < n; i ++) {
        cin >> arr[i];
        inarr[arr[i]] = true;
    }
    for (int i = 0 ; i < n; i++) {
        if(dp(a-arr[i])) cout<<dp(a-arr[i])<<' ';
        else cout<<-1<<' ';
    }
    cout<<'\n';
}
