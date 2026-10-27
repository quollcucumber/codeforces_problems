// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
void solve() {
     int n, m;
     cin >> n >> m;
     vector<pair<int, int>> f(m);
     for(int i = 0; i < m; i++) cin >> f[i].first >> f[i].second;
     for(int i = 0; i < m; i++) f[i] = {f[i].second, f[i].first};
     sort(f.begin(), f.end());
     int maxval = 0;
     multiset<int> s;
     for(pair<int, int> i : f) s.insert(i.second);
     vector<int> presum(m + 1);
     auto a = s.end();
     presum[0] = 0;
     for(int i = 1; i <= m; i++) {
          a = prev(a);
          presum[i] = presum[i-1] + *a;
     }
     maxval = presum[min(n, m)];
     int numg = 0;
     for(int i = m-1; i >= 0; i--) {
          bool add = false;
          if(s.contains(f[i].second)) add = true, s.erase(s.find(f[i].second));
          else numg--;
          while(!s.empty() && *prev(s.end()) > f[i].first) {
               numg++;
               s.erase(prev(s.end()));
          }
          if(numg < n-1) {
               if(f[i].second <= f[i].first) maxval = max(maxval, presum[numg] + f[i].second + f[i].first * (n - 1 - numg));
               else maxval = max(maxval, presum[numg + 1] + f[i].first * (n - 1 - numg));
          }
          if(add) s.insert(f[i].second);
          if(!add) numg++;
     }
     cout<<maxval<<'\n';
}
signed main() {
     ios_base::sync_with_stdio(false);
     cin.tie(nullptr);
     int t;
     cin >> t;
     while(t--) {
          solve();
     }
     return 0;
}
