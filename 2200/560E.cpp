// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
int fac[200005];
const int MOD = 1e9+7;
int power(int a, int b) {
    if(b == 1) return a;
    if(b % 2 == 0) return power(a * a % MOD, b / 2);
    return a * power(a * a % MOD, b / 2) % MOD;
}
int inv(int a) {
    return power(a, MOD-2);
}
int choose(int a, int b) {
    int val = fac[a];
    val *= inv(fac[a-b]);
    val = val % MOD;
    val *= inv(fac[b]);
    val = val % MOD;
    return val;
}
signed main() {
    fac[0] = 1;
    for(int i = 1; i < 200005; i++) fac[i] = (i * fac[i-1]) % MOD;
    // cout<<choose(100, 2)<<'\n';
    int h, w, n;
    cin >> h >> w >> n;
    h--;
    w--;
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        v.push_back({a, b});
    }
    sort(v.begin(), v.end());
    vector<int> numways(n);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int total = choose(v[i].first + v[i].second, v[i].first);
        for(int j = 0; j < i; j++) {
            if(v[j].second <= v[i].second) {
                int ways = a[j];
                int x = abs(v[j].second - v[i].second);
                int y = abs(v[j].first - v[i].first);
                ways *= choose(x + y, y);
                ways = ways % MOD;
                total -= ways;
                total += MOD;
                total = total % MOD;
            }
        }
        a[i] = total;
    }
    v.push_back({h, w});
    int i = n;
    int total = choose(v[i].first + v[i].second, v[i].first);
    for(int j = 0; j < n; j++) {
        if(v[j].second <= v[i].second) {
            int ways = a[j];
            int x = abs(v[j].second - v[i].second);
            int y = abs(v[j].first - v[i].first);
            ways *= choose(x + y, y);
            ways = ways % MOD;
            total -= ways;
            total += MOD;
            total = total % MOD;
        }
    }
    cout<<total<<'\n';
    return 0;
}
