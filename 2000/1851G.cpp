#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 200005;
vector<int> neighbors[MAXN];
vector<int> children[MAXN];
int p[MAXN];
int dsu(int node) {
    if(p[node] == node) return node;
    return p[node] = dsu(p[node]);
}
int weights[MAXN];
bool seenroot[MAXN];
int parent[MAXN];
int dist[MAXN];
void root(int node, int d= 0) {
    dist[node] = d;
    seenroot[node] = true;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            parent[i] = node;
            children[node].push_back(i);
            root(i, d + 1);
        }
    }
}
pair<int, int> jmp[MAXN][20];
int n, m;
void calcjump() {
    for(int i = 1; i <= n; i++) jmp[i][0] = {parent[i], max(weights[i], weights[parent[i]])};
    for(int i = 1; i < 20; i++) {
        for(int j = 1; j <= n; j ++) {
            jmp[j][i] = {jmp[jmp[j][i-1].first][i-1].first, max(jmp[j][i-1].second, jmp[jmp[j][i-1].first][i-1].second)};
        }
    }
}
pair<int, int> jump(int node, int length) {
    int maxval = 0;
    for(int i = 19; i >= 0; i--) {
        if(length >= (1ll<<i)) {
            maxval = max(maxval, jmp[node][i].second);
            node = jmp[node][i].first;
            length -= (1LL << i);
        }
    }
    return {node, maxval};
}
int maxw(int a, int b) {
    int maxval = max(weights[a], weights[b]);
    if(dist[a] > dist[b]) {
        pair<int, int> newa = jump(a, dist[a] - dist[b]);
        maxval = max(maxval, newa.second);
        a = newa.first;
    }else if(dist[b] > dist[a]) {
        pair<int, int> newb = jump(b, dist[b] - dist[a]);
        maxval = max(maxval, newb.second);
        b = newb.first;
    }
    if(a == b) return maxval;
    for(int i = 19; i >= 0; i--) {
        if(jmp[a][i].first != jmp[b][i].first) {
            maxval = max(maxval, jmp[a][i].second);
            maxval = max(maxval, jmp[b][i].second);
            a = jmp[a][i].first;
            b = jmp[b][i].first;
        }
    }
    a = parent[a];
    maxval = max(maxval, weights[a]);
    return maxval;
}
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) neighbors[i].clear();
    for(int i = 1; i <= n; i++) children[i].clear();
    for(int i = 1; i <= n; i++) p[i] = i;
    for(int i = 1; i <= n; i++) seenroot[i] = false;
    for(int i = 1; i <=n ; i++ )cin >> weights[i];
    vector<pair<int, pair<int, int>>> edges;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edges.push_back({max(weights[a], weights[b]), {a, b}});
    }
    sort(edges.begin(), edges.end());
    for(int i = 0; i < m; i++) {
        if(dsu(edges[i].second.first) != dsu(edges[i].second.second)) {
            neighbors[edges[i].second.first].push_back(edges[i].second.second);
            neighbors[edges[i].second.second].push_back(edges[i].second.first);
            p[dsu(edges[i].second.first)] = edges[i].second.second;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!seenroot[i]) {
            parent[i] = i;
            root(i);
        }
    }
    calcjump();
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int a, b, e;
        cin >>a >> b >> e;
        if(dsu(a) != dsu(b) || maxw(a, b) - weights[a] > e) {
            cout<<"NO\n";
        }else {
            cout<<"YES\n";
        }
    }
    cout<<'\n';
}
signed main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
