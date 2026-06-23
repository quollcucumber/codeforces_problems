#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
void solve() {
    int n, m;
    cin >> n >> m;
    int arr[n][m];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> arr[i][j];
            int parity = (i + j) % 2;
            if(arr[i][j] % 2 == parity) {
                cout<<arr[i][j]<<' ';
            }else {
                cout<<arr[i][j] + 1<<' ';
            }
        }
        cout<<'\n';
    }
}
signed main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
