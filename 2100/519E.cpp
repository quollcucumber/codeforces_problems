#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
// #define int long long
using namespace std;
vector<int> neighbors[100005];
vector<int> children[100005];
bool seenroot[100005];
int dist[100005];
int subsum[100005];
int parent[100005];
int root(int node, int distval) {
    dist[node] = distval;
    seenroot[node] = true;
    int total = 1;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            parent[i] = node;
            children[node].push_back(i);
            total += root(i, distval + 1);
        }
    }
    return subsum[node] = total;
}
int n;
int jmp[100005][20];
void calcjump() {
    for(int i = 0; i < n; i++) jmp[i][0] = parent[i];
    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            jmp[j][i] = jmp[jmp[j][i-1]][i-1];
        }
    }
}
int jump(int node, int dist) {
    for(int i = 19; i >= 0; i--) {
        if(dist >= (1<<i)) {
            dist -= (1 <<i);
            node = jmp[node][i];
        }
    }
    return node;
}
int lca(int a, int b) {
    if(dist[a] < dist[b]) {
        b = jump(b, dist[b] - dist[a]);
    }else if(dist[b] < dist[a]) {
        a = jump(a, dist[a] - dist[b]);
    }
    if(a == b) return a;
    for(int i = 19; i >= 0; i--) {
        if(jmp[a][i] != jmp[b][i]) {
            a = jmp[a][i];
            b = jmp[b][i];
        }
    }
    return parent[a];
}
void solve(int a, int b) {
    if(a == b){
        cout<<n<<'\n';
        return;
    }
    if(dist[a] % 2 != dist[b] % 2) {
        cout<<0<<'\n';
        return;
    }
    int lcan = lca(a, b);
    int dista = dist[a] - dist[lcan];
    int distb = dist[b] - dist[lcan];
    int mid;
    pair<int, int> exnode;
    if(dista > distb) {
        mid = jump(a, (dista+distb)/2);
        exnode = {parent[mid], jump(a, (dista+distb)/2-1)};
    }else if(dista < distb) {
        mid = jump(b, (dista+distb)/2);
        exnode = {parent[mid], jump(b, (dista+distb)/2-1)};
    }else {
        mid = lcan;
        exnode = {jump(b, (dista+distb)/2-1), jump(a, (dista+distb)/2-1)};
    }
    int total = n;
    vector<pair<int, int>> v;
    if(exnode.first != parent[mid]) total -= subsum[exnode.first];
    if(exnode.second != parent[mid]) total -= subsum[exnode.second];
    if(parent[mid] == exnode.first || parent[mid] == exnode.second){
       total -= n - subsum[mid];
    }
    cout<<total<<'\n';
}
signed main() {
    cin >> n;
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    root(0, 0);
    calcjump();
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        solve(a, b);
    }
}
