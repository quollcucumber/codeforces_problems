// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    pair<int, pair<int, int>> ans = {67, {67, 67}};
    int minval = INT_MAX;
    for(int i = 1; i <= a * 2; i++) {
        for(int j = i; j <= b * 2; j+= i) {
            int dist = abs(i-a) + abs(j-b);
            int z = (c / j) * j;
            int num;
            if(abs(z-c) <  abs((z+j)-c)) {
                num = z;
            }else {
                num = (z+j);
            }
            if(dist + abs(c - num)< minval) {
                minval = dist + abs(c - num);
                ans = {i, {j, num}};
            }
        }
    }
    cout<<minval<<'\n';
    cout<<ans.first<<' '<<ans.second.first<<' '<<ans.second.second<<'\n';
}
signed main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
