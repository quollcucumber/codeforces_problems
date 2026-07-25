// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
using namespace std;
#define int long long

vector<int> neighbors[200005];
vector<int> children[200005];
bool seenroot[200005];
int parent[200005];
int dist[200005];
void root(int node, int d) {
    dist[node] = d;
    seenroot[node] = true;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            children[node].push_back(i);
            parent[i] = node;
            root(i, d + 1);
        }
    }
}
int jmp[200005][20];
int n;
void calcjmp() {
    for(int i = 1; i <= n; i++) {
        jmp[i][0] = parent[i];
    }
    for(int j = 1; j < 20; j ++) {
        for(int i = 1; i <= n; i++) {
            jmp[i][j] = jmp[jmp[i][j-1]][j-1];
        }
    }
}
int jump(int node, int dist) {
    if(dist == -1) return node;
    for(int i = 19; i >= 0; i--) {
        if(dist >= (1<<i)) {
            dist -= (1<<i);
            node = jmp[node][i];
        }
    }
    return node;
}
int lca(int a, int b) {
    if(dist[a] < dist[b]) b = jump(b, dist[b] - dist[a]);
    if(dist[a] > dist[b]) a = jump(a, dist[a] - dist[b]);
    if(a == b) return a;
    for(int i = 19; i >= 0; i--) {
        if(jmp[a][i] != jmp[b][i]) {
            a = jmp[a][i];
            b = jmp[b][i];
        }
    }
    assert(a != b);
    assert(parent[a] == parent[b]);
    return parent[a];
}
signed main() {
    cin >> n;
    for(int i = 0; i < n-1; i++) {
        int  a, b;
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    root(1, 0);
    parent[1] = 1;
    calcjmp();
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<int> nodes;
        for(int j = 0; j < k; j++) {
            int a;
            cin >> a;
            nodes.push_back(a);
        }
        if(k == 1) {
            cout<<"YES\n";
        }else {
            int a = nodes[0], b = nodes[1];
            int lcanode = lca(a, b);
            for(int j = 2; j < k; j++) {
                lcanode = lca(lcanode, nodes[j]);
            }
            set<int> s;
            set<int> dists;
            int lowest = 1;
            for(int j = 0; j < k; j++) {
                if(dist[nodes[j]] > dist[lowest]) {
                    lowest = nodes[j];
                }
                s.insert(nodes[j]);
                dists.insert(dist[nodes[j]]);
            }
            for(int j : dists) {
                s.erase(jump(lowest, dist[lowest] - j));
            }
            if(s.empty()) {
                cout<<"YES\n";
            }else {
                int subtreelca = jump(lowest, dist[lowest] - dist[lcanode] - 1);
                int nlow = 1;
                dists.clear();
                for(int j : s) {
                    if(dist[j] > dist[nlow]) {
                        nlow = j;
                    }
                    dists.insert(dist[j]);
                }
                if(jump(nlow, dist[nlow] - dist[lcanode] - 1) == subtreelca) {
                    cout<<"NO\n";
                }else {
                    for(int j : dists) {
                        s.erase(jump(nlow, dist[nlow] - j));
                    }
                    if(s.empty()) {
                        cout<<"YES\n";
                    }else {
                        cout<<"NO\n";
                    }
                }
            }
        }
    }
    return 0;
}
