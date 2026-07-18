// this problem is so overrated ngl

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
int occ[1<<18];
int parent[1<<18];
int dsu(int node) {
    if(parent[node] == node) return node;
    return parent[node] = dsu(parent[node]);
}
signed main() {
    for(int i = 0; i < (1 << 18); i++) parent[i] = i;
    int n;
    cin >> n;
    int total = 0;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        total -= a;
        occ[a]++;
    }
    occ[0] ++;
    for(int num = (1<<18)-1; num >= 0; num--) {
        for(int mask = num;; mask=(mask-1)&num) {
            int connect = mask ^ num;
            if(occ[mask] && occ[connect] && dsu(connect) != dsu(mask)) {
                total += (occ[mask] + occ[connect] - 1) * num;
                parent[dsu(connect)] = dsu(mask);
                occ[mask] = 1;
                occ[connect] = 1;
            }
            if(mask == 0) break;
        }
    }
    cout<<total<<'\n';
}
