#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
// #define int long long
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    vector<int> v(t);
    for(int i = 0; i < t; i++) cin >> v[i];
    vector<int> oc(t + 1);
    for(int i = 0; i < t; i++) oc[v[i]]++;
    if(oc[0] != 1) {
        cout<<-1<<'\n';
        return 0;
    }
    int b = *max_element(v.begin(), v.end());
    for(int i = 1; i <= t; i++) {
        if(oc[i] != 4*i) {
            int y = i;
            for(int n = 1; n <= t; n++) {
                int m = t / n;
                if(n * m == t) {
                    int x = m - (b - (n - y));
                    if(x <= m && y <= n) {
                        vector<int> newoc(t+1);
                        for(int j = 1; j <= n; j++) {
                            for(int k = 1; k <= m; k++) {
                                newoc[abs(j-y) + abs(k-x)]++;
                            }
                        }
                        if(newoc == oc) {
                            cout<<n<<' '<<m<<'\n';
                            cout<<y<<' '<<x<<'\n';
                            return 0;
                        }
                    }
                }
            }
            break;
        }
    }
    cout<<-1<<'\n';
    return 0;
}
