// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
const int maxlen = 1e12+5;
struct line {
     int m, c;
     int operator()(int x) const {return m*x+c;}
};
struct lct {
     vector<signed> children[2];
     vector<line> nodes;
     int makenode() {
          nodes.push_back({0, 0});
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
     void insert(line a, int pos = 0, int l = -maxlen, int r = maxlen) {
          line cur = nodes[pos];
          int mid = (l + r) / 2;
          if(cur(mid) < a(mid)) {
               swap(cur, a);
          }
          nodes[pos] = cur;
          if(l+1==r) return;
          if(a(l) > cur(l)) {
               insert(a, child(0, pos), l, mid);
          }else {
               insert(a, child(1, pos), mid, r);
          }
     }
     int ans(int x, int pos = 0, int l = -maxlen, int r = maxlen) {
          int mid = (l + r) / 2;
          if(l + 1 == r) return nodes[pos](x);
          if(x < mid) {
               return max(nodes[pos](x), ans(x, child(0, pos), l, mid));
          }else {
               return max(nodes[pos](x), ans(x, child(1, pos), mid, r));
          }
     }
};
signed main() {
     lct tree;
     tree.makenode();
     int n;
     cin >> n;
     vector<int> a(n);
     for(int i = 0; i < n; i++) cin >> a[i];
     vector<int> presum(n+1);
     vector<int> premult(n + 1);
     presum[0] = 0;
     premult[0] = 0;
     for(int i = 0; i < n; i++) {
          presum[i+1] = presum[i] + a[i];
          premult[i+1] = premult[i] + a[i] * (i + 1);
     }
     // for(int i = 0; i < n; i ++) {
     //      for(int j = i; j < n; j++) {
     //           maxval = max(maxval, premult[j+1] - premult[i] - (i) * (presum[j+1] - presum[i]));
     //      }
     // }
     int maxval = 0;
     for(int i = 0; i < n; i++) {
          tree.insert({-i, -premult[i] + (i) * presum[i]});
          int val = tree.ans(presum[i+1]) + premult[i+1];
          maxval = max(maxval, val);
     }
     cout<<maxval<<'\n';
     // cout<<tree.ans(a[n-1])<<'\n';
}
