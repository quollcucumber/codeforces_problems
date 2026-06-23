#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int t;
    cin >> t;
    for (int test = 0; test < t; test++) {
        int n, q;
        cin >> n >> q;
        int colours[n];
        for(int i = 0; i < n; i++) {
            cin >> colours[i];
        }
        int total = 0;
        vector<pair<int, int>> neighbors[n];
        map<int, int> colorval[n];
        for(int i = 0; i < n-1; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            u--;
            v--;
            neighbors[u].push_back({v, c});
            neighbors[v].push_back({u, c});
            if(colours[u] != colours[v]) {
                total += c;
            }
        }
        vector<pair<int, int>> children[n];
        pair<int, int> parent[n];
        bool seen[n];
        for(int i = 0; i < n; i++)seen[i]=false;
        queue<int> qu;
        qu.push(0);
        while(!qu.empty()) {
            int node = qu.front();
            qu.pop();
            seen[node] = true;
            for(pair<int, int> i : neighbors[node]) {
                if(!seen[i.first]) {
                    colorval[node][colours[i.first]] += i.second;
                    children[node].push_back(i);
                    parent[i.first] = {node, i.second};
                    qu.push(i.first);
                }
            }
        }
        for(int i = 0; i < q; i++) {
            int a, col;
            cin >> a >> col;
            a--;
            if(a != 0) {
                colorval[parent[a].first][colours[a]] -= parent[a].second;
                if(colours[a] == colours[parent[a].first]) total += parent[a].second;
            }
            total += colorval[a][colours[a]];
            colours[a] = col;
            if(a != 0) {
                colorval[parent[a].first][colours[a]] += parent[a].second;
                if(colours[a] == colours[parent[a].first]) total -= parent[a].second;
            }
            total -= colorval[a][colours[a]];
            cout<<total<<'\n';
        }
    }
}
