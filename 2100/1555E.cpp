#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
     int minval;
     int lazyadd;
};
const int MAXN = 1000005;
node tree[MAXN * 4];
void prop(int node, int l, int r) {
     if(l + 1 != r) {
          tree[node * 2].minval += tree[node].lazyadd;
          tree[node * 2].lazyadd += tree[node].lazyadd;
          tree[node * 2 + 1].minval += tree[node].lazyadd;
          tree[node * 2 + 1].lazyadd += tree[node].lazyadd;
     }
     tree[node].lazyadd = 0;
}
void upd(int left, int right, int val, int pos = 1, int l = 0, int r = MAXN) {
     if(left <= l && r <= right) {
          tree[pos].lazyadd += val;
          tree[pos].minval += val;
          return;
     }
     prop(pos,l, r);
     int mid = (l + r) / 2;
     if(left < mid) upd(left, right, val, pos * 2, l, mid);
     if(right > mid) upd(left, right, val, pos * 2 + 1, mid, r);
     tree[pos].minval = min(tree[pos * 2].minval, tree[pos * 2 + 1].minval);
}
int query(int left, int right, int pos = 1, int l = 0, int r = MAXN) {
     if(left <= l && r <= right) {
          return tree[pos].minval;
     }
     prop(pos, l, r);
     int mid = (l + r) / 2;
     int minval = INT_MAX;
     if(left< mid) minval = min(minval, query(left, right, pos * 2, l, mid));
     if(right > mid) minval = min(minval, query(left, right, pos * 2 + 1, mid, r));
     return minval;
}
signed main() {
     int n, m;
     cin >> n >> m;
     vector<pair<int, pair<int, int>>> vec;
     for(int i = 0; i < n; i++) {
          int w, l, r;
          cin >> l >> r >> w;
          vec.push_back({w, {l, r}});
     }
     sort(vec.begin(), vec.end());
     int r = 0;
     int minval = INT_MAX;
     for(int i = 0; i < n; i++) {
          // for(int j = 0; j < m; j++) cout<<query(j, j + 1)<<' ';
          // cout<<'\n';
          while(query(1, m) == 0) {
               if(r == n) {
                    cout<<minval<<'\n';
                    return 0;
               }
               if(vec[r].second.first != vec[r].second.second) upd(vec[r].second.first, vec[r].second.second, 1);
               // for(int j = 0; j < m; j++) cout<<query(j, j + 1)<<' ';
               // cout<<'\n';
               r++;
          }
          minval = min(minval, vec[r-1].first - vec[i].first);
          upd(vec[i].second.first, vec[i].second.second, -1);
     }
     cout<<minval<<'\n';
     return 0;
}
