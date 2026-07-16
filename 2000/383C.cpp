// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
const int MAXN = 200005;
struct node {
    int lazyadd;
};
node tree[MAXN * 4];
void prop(int node, int l, int r) {
    if(l + 1 == r) {

    }else {
        tree[node * 2].lazyadd += tree[node].lazyadd;
        tree[node*2+1].lazyadd += tree[node].lazyadd;
        tree[node].lazyadd = 0;
    }
}
void upd(int left, int right, int val, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos, l, r);
    if(left <= l && right >= r) {
        tree[pos].lazyadd += val;
        return;
    }
    int mid = (l + r) / 2;
    if(left < mid) {
        upd(left, right, val, pos * 2,l, mid);
    }
    if(right > mid) {
        upd(left, right, val, pos * 2 + 1, mid, r);
    }
}
int query(int index, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos,l,r);
    if(l + 1 == r) {
        return tree[pos].lazyadd;
    }
    int mid = (l + r) / 2;
    if(index < mid) {
        return query(index, pos * 2,l, mid);
    }else{
        return query(index, pos * 2 + 1, mid, r);
    }
}
bool seenroot[MAXN];
vector<int> neighbors[MAXN];
vector<int> children[MAXN];
bool depth[MAXN];
void root(int node, bool a) {
    depth[node] = a;
    seenroot[node] = true;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            root(i, 1-a);
            children[node].push_back(i);
        }
    }
}
pair<int, int> tours[MAXN];
int pos = -1;
void tour(int node) {
    pos++;
    tours[node].first = pos;
    for(int i : children[node]) {
        tour(i);
    }
    tours[node].second = pos;
}
signed main() {
    int n,m;
    cin >> n >> m;
    vector<int> arr(n + 1);
    for(int i = 0; i < n; i++) cin >> arr[i+1];
    for (int i = 0; i < n-1; i++) {
        int a,b;
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    root(1, 0);
    tour(1);
    for(int i = 1; i <= n; i++) {
        if(depth[i]) {
            upd(tours[i].first, tours[i].first + 1, arr[i]);
        }else {
            upd(tours[i].first, tours[i].first + 1, -1 * arr[i]);
        }
    }
    for(int i = 0; i < m; i++) {
        // for(int j = 0; j < n; j++) {
        //     cout<<query(j)<<' ';
        // }
        // cout<<'\n';
        int t;
        cin >> t;
        if(t == 1) {
            int x, val;
            cin >> x >> val;
            if(depth[x]) {
                upd(tours[x].first, tours[x].second + 1, val);
            }else {
                upd(tours[x].first, tours[x].second + 1, -1* val);
            }
        }else {
            int a;
            cin >> a;
            if(depth[a]) {
                cout<<query(tours[a].first)<<'\n';
            }else {
                cout<<-1 * query(tours[a].first)<<'\n';

            }
        }
    }
}
