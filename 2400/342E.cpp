// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
bool red[100005];

const int SQRT = 300;
vector<int> neighbors[100005];
vector<int> children[100005];
bool seenroot[100005];
void root(int node) {
    seenroot[node] = true;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            children[node].push_back(i);
            root(i);
        }
    }
}
vector<int> euler;
vector<int> depths;
int first[100005];
void tour(int node, int depth) {
    euler.push_back(node);
    depths.push_back(depth);
    if(first[node] == -1) first[node] = euler.size()-1;
    for(int i : children[node]) {
        tour(i, depth +1);
        euler.push_back(node);
        depths.push_back(depth);
    }
}
int table[20][200015];
void calctable() {
    for(int i = 0; i < depths.size(); i++) {
        table[0][i] = depths[i];
    }
    for(int i = 1; i < 20; i++) {
        int a = 1<<i;
        int b = 1<<(i-1);
        for(int j = 0; j < 200015 - a + 1; j++) {
            table[i][j] = min(table[i-1][j], table[i-1][j+b]);
        }
    }
}
int dist(int a, int b) {
    int pos1 = min(first[a], first[b]);
    int pos2 = max(first[a], first[b]);
    int dist = pos2 - pos1 + 1;
    int len = log2(dist);
    int minval = min(table[len][pos1], table[len][pos2 - (1<<len)+1]);
    return depths[pos1] + depths[pos2] - minval * 2;
}
int n, m;
void solve(vector<pair<int, int>> vec) {
    vector<int> close(n + 1);
    for(int i = 0; i <=n; i++) close[i] = {-1};
    queue<int> q;
    for(int i = 1; i <= n; i++) if(red[i]) q.push(i);
    int d = 0;
    while(!q.empty()) {
        int sz = q.size();
        for(int j = 0; j < sz; j++) {
            int a = q.front();
            q.pop();
            if(close[a] == -1) {
                close[a] = d;
                for(int k : neighbors[a]) {
                    if(close[k] == -1) {
                        q.push({k});
                    }
                }
            }
        }
        d++;
    }
    vector<int> nodes;
    for(pair<int, int> i : vec) {
        if(i.first== 2) {
            nodes.push_back(i.second);
        }
    }
    for(pair<int, int> i : vec) {
        if(i.first  == 1) {
            red[i.second] = true;
            for(int node : nodes) {
                int a = dist(i.second, node);
                if(a < close[node]) {
                    close[node] = a;
                }
            }
        }else {
            cout<<close[i.second]<<'\n';
        }
    }
}
signed main() {
    cin >> n >> m;
    for(int i = 0; i <= n; i++) first[i] = -1;
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    root(1);
    tour(1, 0);
    calctable();
    red[1] = true;
    vector<pair<int, int>> queries;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        queries.push_back({a, b});
    }
    for(int i = 0; i < (m + SQRT - 1) / SQRT; i++) {
        vector<pair<int, int>> ans;
        for(int j = i * SQRT; j < min(m, i * SQRT + SQRT); j++) {
            ans.push_back(queries[j]);
        }
        solve(ans);
    }
    return 0;
}
