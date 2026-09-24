#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
vector<int> arr;
struct node {
     int minval;
     int numminval;
     int lazyadd;
};
int maxn;
struct segtree {
     vector<node> nodes;
     void init(int n) {
          nodes.resize(n * 4);
          maxn = n;
     }
     void prop(int node, int l, int r) {
          if(l + 1 != r) {
               nodes[node * 2].lazyadd += nodes[node].lazyadd;
               nodes[node * 2].minval += nodes[node].lazyadd;
               nodes[node * 2+1].lazyadd += nodes[node].lazyadd;
               nodes[node * 2+1].minval += nodes[node].lazyadd;
          }
          nodes[node].lazyadd = 0;
     }
     node merge(node a, node b) {
          if(a.minval < b.minval) return {a.minval, a.numminval, 0};
          if(a.minval > b.minval) return {b.minval, b.numminval, 0};
          return {a.minval, a.numminval + b.numminval, 0};
     }
     void upd(int left, int right, int val, int pos = 1, int l = 0, int r = maxn) {
          prop(pos, l, r);
          if(left <= l && r <= right) {
               nodes[pos].lazyadd += val;
               nodes[pos].minval += val;
               if(nodes[pos].numminval == 0) nodes[pos].numminval = (r - l);
               return;
          }
          int mid = (l + r) / 2;
          if(left < mid) {
               upd(left, right, val, pos * 2, l, mid);
          }
          if(right > mid) {
               upd(left, right, val, pos * 2 + 1, mid, r);
          }
          nodes[pos] = merge(nodes[pos * 2], nodes[pos * 2 + 1]);
     }
     int query() {
          if(nodes[1].minval == 0) return nodes[1].numminval;
          return 0;
     }
};

// hmmm the value at index i of the segtree is like the length to i - (maxval - minval) right? No that sucks bc it can be negative!!!
// it should be like (maxval - minval) - i :o
;
int dnc(int l, int r) {
     int mid = (l + r) / 2;
     if(l + 1 == r) return 1;
     int total = dnc(l, mid) + dnc(mid, r);
     segtree a;
     a.init(r - mid);
     deque<pair<int, pair<int, int>>> minstack;
     for(int i = mid; i < r; i++) a.upd((i - mid), i + 1 - mid, -1 * (i - mid));
     int minval = arr[mid];
     int prevpos = 0;
     for(int i = mid; i < r; i++) {
          minval = min(minval, arr[i]);
          if(i == r-1 || arr[i+1] < minval) {
               a.upd(prevpos, i+1 - mid, -minval);
               minstack.push_back({minval, {prevpos, i - mid}});
               prevpos = i - mid +1;
          }
     }
     deque<pair<int, pair<int, int>>> maxstack;
     int maxval = arr[mid];
     prevpos = 0;
     for(int i = mid; i < r; i++) {
          maxval = max(maxval, arr[i]);
          if(i == r-1 || arr[i+1] > maxval) {
               a.upd(prevpos, i+1 - mid, maxval);
               maxstack.push_back({maxval, {prevpos, i - mid}});
               prevpos = i - mid +1;
          }
     }
     for(int i = mid-1; i>= l; i--) {
          a.upd(0, r - mid, -1);
          while(!minstack.empty() && minstack[0].first > arr[i]) {
               a.upd(minstack[0].second.first, minstack[0].second.second + 1, (minstack[0].first - arr[i]));
               minstack.pop_front();
          }
          if(minstack.empty()) minstack.push_front({arr[i], {0, (r - mid) -1}});
          else if(minstack[0].second.first != 0) minstack.push_front({arr[i], {0, minstack[0].second.first-1}});
          while(!maxstack.empty() && maxstack[0].first < arr[i]) {
               a.upd(maxstack[0].second.first, maxstack[0].second.second + 1, -1 * (maxstack[0].first - arr[i]));
               maxstack.pop_front();
          }
          if(maxstack.empty()) maxstack.push_front({arr[i], {0, (r - mid) -1}});
          else if(maxstack[0].second.first != 0) maxstack.push_front({arr[i], {0, maxstack[0].second.first-1}});
          total += a.query();
     }
     return total;
}
signed main() {
     int n;
     cin >> n;
     vector<pair<int, int>> vec;
     for(int i = 0; i < n; i++) {
          int x, y;
          cin >> x >> y;
          vec.push_back({x, y});
     }
     sort(vec.begin(), vec.end());
     arr.resize(n);
     for(int i = 0; i < n; i++) arr[i] = vec[i].second;
     // okay, now the problem is like given an permutation of size n, how many pairs {l, r} are there such that r-l == maxval - minval I think we use dnc or smth
     // int total = 0;
     // for(int l = 0; l < n; l++) {
     //      int minval = arr[l], maxval = arr[l];
     //      for(int r = l; r < n; r++) {
     //           minval = min(minval, arr[r]);
     //           maxval = max(maxval, arr[r]);
     //           total += (maxval - minval) == (r - l);
     //      }
     // }
     // cout<<total<<'\n';
     cout<<dnc(0, n)<<'\n';
     return 0;
}
