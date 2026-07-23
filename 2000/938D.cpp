#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> neighbors(n+1);
    for (int i = 0; i < m; i ++) {
        int a, b, d;
        cin >> a >> b >> d;
        neighbors[a].push_back({b, d});
        neighbors[b].push_back({a, d});
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> v;
    priority_queue p(v.begin(), v.end(), greater<pair<int, int>>());
    for (int i = 0; i < n; i++) {
        p.push({a[i], i+1});
    }
    vector<int> dist(n + 1, 0);
    vector<bool> seen(n +1, 0);
    while (!p.empty()) {
        int d = p.top().first;
        int node = p.top().second;
        p.pop();
        if (!seen[node]) {
            seen[node] = true;
            dist[node] = d;
            for (pair<int, int> j : neighbors[node]) {
                if (!seen[j.first]) {
                    p.push({d + j.second * 2, j.first});
                }
            }
        }
    }
    for (int i =  1; i <= n; i++) {
        cout<<dist[i]<<' ';
    }
    cout<<'\n';
}
