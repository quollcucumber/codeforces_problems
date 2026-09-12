// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
const int maxlen = 1e9+5;
struct line {
     int m, c;
     int operator()(int x) const {return m*x+c;}
};
struct lct {
     vector<int> children[2];
     vector<line> nodes;
     int makenode() {
          nodes.push_back({0, LONG_LONG_MAX/4});
          children[0].push_back(-1);
          children[1].push_back(-1);
          return (int)nodes.size()-1;
     }
     int child(int k, int pos) {
          if(children[k][pos] == -1) {
               children[k][pos] = makenode();
          }
          return children[k][pos];
     }
     void insert(line a, int pos = 0, int l = 0, int r = maxlen) {
          line cur = nodes[pos];
          int mid = (l + r) / 2;
          if(cur(mid) > a(mid)) {
               swap(cur, a);
          }
          nodes[pos] = cur;
          if(l+1==r) return;
          if(a(l) < cur(l)) {
               insert(a, child(0, pos), l, mid);
          }else {
               insert(a, child(1, pos), mid, r);
          }
     }
     int ans(int x, int pos = 0, int l = 0, int r = maxlen) {
          int mid = (l + r) / 2;
          if(l + 1 == r) return nodes[pos](x);
          if(x < mid) {
               return min(nodes[pos](x), ans(x, child(0, pos), l, mid));
          }else {
               return min(nodes[pos](x), ans(x, child(1, pos), mid, r));
          }
     }
};
signed main() {
     lct tree;
     tree.makenode();
     int n;
     cin >> n;
     vector<int> a(n), b(n);
     for(int i = 0; i < n; i++) cin >> a[i];
     for(int i = 0; i < n; i++) cin >> b[i];
     tree.insert({b[0], 0});
     for(int i = 1; i < n-1; i++) {
          int val = tree.ans(a[i]);
          tree.insert({b[i], val});
     }
     cout<<tree.ans(a[n-1])<<'\n';
}
