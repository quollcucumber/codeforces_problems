#include <bits/stdc++.h>
#define int long long
using namespace std;
bool seenroot[100005];
vector<pair<int, int>> neighbors[100005];
vector<pair<int, int>> children[100005];
vector<int> vecs;
int total = 0;
void root(int node) {
     seenroot[node] = true;
     for(pair<int, int> i : neighbors[node]) {
          if(!seenroot[i.first]) {
               root(i.first);
               children[node].push_back(i);
          }
     }
}
int dp(int node) {
     int t = 0;
     for(pair<int, int> i : children[node]) {
          int a = dp(i.first);
          t += a;
          total += a * i.second;
          int val = i.second;
          while(val >= 1) {
               vecs.push_back(a * (val - val/ 2));
               val /= 2;
          }
     }
     if(t == 0) t = 1;
     return t;
}
void solve() {
     total = 0;
     int n, s;
     cin >> n >> s;
     for(int i = 1; i <= n; i++) seenroot[i] = false;
     for(int i = 1; i <= n; i++) children[i].clear();
     for(int i = 1; i <= n; i++) neighbors[i].clear();
     for(int i = 0; i < n-1; i++) {
          int u, v, w;
          cin >> u >> v >> w;
          neighbors[u].push_back({v, w});
          neighbors[v].push_back({u, w});
     }
     root(1);
     dp(1);
     sort(vecs.begin(), vecs.end());
     int pos = (int)vecs.size()-1;
     while(s < total) total -= vecs[pos--];
     cout<<abs(abs((int)vecs.size()-1 - pos))<<'\n';;
     vecs.clear();
}
signed main() {
     int t;
     cin >>  t;
     while(t--) {
          solve();
     }
     return 0;
}
