// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
struct node {
    vector<pair<int, int>> edges; // why do I have a struct with one thing in it :skull:
};
const int MAXN = 250005;
node tree[MAXN * 9];
int n;
void upd(int left, int right, int weight, int node, bool add, int pos = 1, int l = 0, int r = MAXN) {
    if(left <= l && right >= r) {
        if(add) tree[node].edges.push_back({pos + MAXN, weight});
        else tree[pos + MAXN * 5].edges.push_back({node, weight});
        return;
    }
    int mid = (l + r) / 2;
    if(left < mid) {
        upd(left, right, weight, node, add, pos * 2, l, mid);
    }
    if(right > mid) {
        upd(left, right, weight, node, add, pos * 2 + 1,mid, r);
    }
}
int pos(int val) {
    int l = 0, r = MAXN;
    int ans = 1;
    while(l + 1 < r) {
        int mid = (l + r)/ 2;
        if(val < mid) {
            ans *= 2;
            r = mid;
        }else {
            ans = ans * 2 + 1;
            l = mid;
        }
    }
    return ans;
}
signed main() {
    int n, q, s;
    cin >> n >> q >> s;
    for(int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if(t == 1) {
            int u, v, w;
            cin >>  u>> v >> w;
            tree[u-1].edges.push_back({v-1, w});
        }else if(t == 2) {
            int u, l, r, w;
            cin >> u >> l >> r >> w;
            upd(l-1, r, w, (u-1), true);
        }else {
            int u, l, r, w;
            cin >> u >> l >> r >> w;
            upd(l-1, r, w, (u-1), false);
        }
    }
    for(int i = 0; i < n; i++) {
        tree[i].edges.push_back({MAXN + pos(i), 0});
        tree[MAXN+pos(i)].edges.push_back({i, 0});
        tree[i].edges.push_back({MAXN*5 + pos(i), 0});
        tree[MAXN*5 + pos(i)].edges.push_back({i, 0});
    }
    for(int i = MAXN+1; (i-1)*2+1 + MAXN < MAXN * 5; i++) {
        tree[i].edges.push_back({(i-MAXN)*2 + MAXN, 0});
        tree[i].edges.push_back({(i-MAXN)*2+1 + MAXN, 0});
    }
    for(int i = MAXN*5+2; i < MAXN * 9; i++) {
        tree[i].edges.push_back({(i-MAXN*5)/2 + MAXN * 5, 0});
    }
    bool seen[9 * MAXN];
    int dist[9 * MAXN];
    for(int i = 0; i < 9 * MAXN; i++) dist[i] = -1;
    memset(seen, false, sizeof(seen));
    vector<pair<int, int>> v;
    priority_queue p(v.begin(), v.end(), greater<pair<int, int>>());
    p.push({0, (s-1)});
    while(!p.empty()) {
        int node = p.top().second;
        int dis = p.top().first;
        if(node == 231079) {
            int a = 0;
        }
        p.pop();
        if(!seen[node]) {
            seen[node] = true;
            dist[node] = dis;
            for(pair<int, int> i : tree[node].edges) {
                if(!seen[i.first]) {
                    p.push({dis + i.second, i.first});
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cout<<dist[i]<<' ';
    }
    cout<<'\n';
}
