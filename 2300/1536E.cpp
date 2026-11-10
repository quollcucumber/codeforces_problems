#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
int power(int a, int b) {
     if(b == 0) return 1;
     if(b % 2) return a * power(a * a % MOD, b / 2) % MOD;
     return power(a * a % MOD, b / 2);
}
void solve() {
     int n,m;
     cin >> n >> m;
     int total = 0;
     for(int i = 0; i < n * m; i++) {
          char c;
          cin >> c;
          total += c == '#';
     }
     if(total == n * m) cout<<power(2, total) - 1<<'\n';
     else cout<<power(2, total)<<'\n';

}
signed main() {
     int t;
     cin >> t;
     while(t--) solve();
     return 0;
}
