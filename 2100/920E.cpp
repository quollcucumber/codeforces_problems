#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;


// int parent[200005];
// int dsu(int node) {
//     if(parent[node] == node) return node;
//     return parent[node] = dsu(parent[node]);
// }

bool seen[200005];
set<int> notset;
vector<set<int>> notin;
void rec(int node) {
    seen[node] = true;
    vector<int> nodes;
    for(int i : notset) {
        if(!notin[node].contains(i)) {
            nodes.push_back(i);
        }
    }
    for(int i : nodes) {
        notset.erase(i);
    }
    for(int i : nodes) {
        rec(i);
    }
}
signed main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) notin.push_back({});
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        notin[a-1].insert(b-1);
        notin[b-1].insert(a-1);
    }
    vector<int> sizes;
    for(int i = 0; i < n; i++) {
        if(!seen[i]) {
            notset.clear();
            for(int j = i+1; j < n; j++) notset.insert(j);
            rec(i);
            sizes.push_back(n - i - notset.size());
        }
    }
    sort(sizes.begin(), sizes.end());
    cout<<sizes.size()<<'\n';
    for(int i : sizes) {
        cout<<i<<' ';
    }
    cout<<'\n';
}
