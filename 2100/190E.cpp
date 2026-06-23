#include <bits/stdc++.h>
// #define int long long
using namespace std;


// int parent[200005];
// int dsu(int node) {
//     if(parent[node] == node) return node;
//     return parent[node] = dsu(parent[node]);
// }
#define set unordered_set
bool seen[500005];
set<int> notset;
vector<set<int>> notin;
vector<int> vec;
void rec(int node) {
    vec.push_back(node);
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) notin.push_back({});
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        notin[a-1].insert(b-1);
        notin[b-1].insert(a-1);
    }
    vector<pair<int, vector<int>>> sizes;
    for(int i = 0; i < n; i++) {
        if(!seen[i]) {
            notset.clear();
            vec.clear();
            for(int j = i+1; j < n; j++) notset.insert(j);
            rec(i);
            sizes.push_back({n - i - notset.size(), vec});
        }
    }
    sort(sizes.begin(), sizes.end());
    cout<<sizes.size()<<'\n';
    for(pair<int, vector<int>> i : sizes) {
        cout<<i.first<<' ';
        for(int j : i.second) {
            cout<<j+1<<' ';
        }
        cout<<'\n';
    }
    cout<<'\n';
}
