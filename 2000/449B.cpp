// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> neighbors[n+ 1];
    vector<pair<int, pair<int, int>>> vec;
    for(int i = 0; i < m; i ++) {
        int u, v, x;
        cin >> u >> v >> x;
        vec.push_back({x, {u, v}});
        neighbors[u].push_back({v, x});
        neighbors[v].push_back({u, x});
    }
    vector<pair<int, int>> v;
    priority_queue p(v.begin(), v.end(), greater<pair<int, int>>());
    p.push({0, 1});
    bool seen[n+1];
    memset(seen, false, sizeof(seen));
    int dista[n+1];
    vector<pair<int, int>> trains;
    for(int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        trains.push_back({a, b});
        neighbors[1].push_back({a, b});
        neighbors[a].push_back({1, b});
    }
    while(!p.empty()) {
        int node = p.top().second;
        int dist = p.top().first;
        p.pop();
        if(!seen[node]) {
            seen[node] = true;
            dista[node] = dist;
            for(pair<int, int> i : neighbors[node]) {
                if(!seen[i.first]) {
                    p.push({dist + i.second, i.first});
                }
            }
        }
    }

    int total = 0;
    int degree[n+1];
    memset(degree, 0, sizeof(degree));
    for(int i = 0; i < vec.size(); i++) {
        if(dista[vec[i].second.first] + vec[i].first == dista[vec[i].second.second]) {
            degree[vec[i].second.second]++;
        }
        if(dista[vec[i].second.first]  == dista[vec[i].second.second] + vec[i].first) {
            degree[vec[i].second.first]++;
        }
    }
    for(int i = 0; i < trains.size(); i++) {
        if(dista[trains[i].first] == trains[i].second) {
            if(degree[trains[i].first] == 0) {
                degree[trains[i].first]++;
            }else {
                total ++;
                // degree[trains[i].first]--;
            }
        }else {
            total++;
        }
    }
    cout<<total<<'\n';
}
