// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;

int n, d;
vector<int> a;
vector<pair<int, int>> loc;
int dist(pair<int, int> a, pair<int, int> b) {
     return abs(a.first - b.first) + abs(a.second - b.second);
}
bool check(int start) {
     priority_queue<pair<int, int>>  p;
     p.push({start, 0});
     vector<bool> seen(n, 0);
     while(!p.empty()) {
          int am = p.top().first;
          int node = p.top().second;
          if(node == n-1) return true;
          p.pop();
          if(!seen[node]) {
               seen[node] = true;
               for(int i = 0; i < n; i++) {
                    if(node != i && !seen[i] && dist(loc[node], loc[i]) * d <= am) {
                         p.push({ am - dist(loc[node], loc[i]) * d + a[i], i});
                    }
               }
          }
     }
     return false;
}

signed main() {
     cin >> n >> d;
     a.resize(n);
     fill(a.begin(), a.end(), 0);
     for(int i = 1; i < n-1; i++) {
          cin >> a[i];
     }
     for(int i = 0; i < n; i++) {
          int a, b;
          cin >> a >> b;
          loc.push_back({a, b});
     }
     int l = 0, r = 1e15;
     while(l + 1 < r) {
          int mid = (l + r) / 2;
          if(check(1e15 - mid)) {
               l = mid;
          }else {
               r = mid;
          }
     }
     cout<<(int)1e15 - l<<'\n';
}
