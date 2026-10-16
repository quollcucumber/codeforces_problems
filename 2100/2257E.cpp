#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
     int n, x;
     cin >> n >> x;
     vector<vector<pair<int, int>>> buildings(n);
     for(int i = 0; i < n; i++) {
          int m;
          cin >> m;
          buildings[i].resize(m);
          for(int j = 0; j < m; j++) cin >> buildings[i][j].first;
          for(int j = 0; j < m; j++) cin >> buildings[i][j].second;
     }
     vector<pair<int, int>> vec;
     priority_queue p(vec.begin(), vec.end(), greater<pair<int, int>>());
     vector<int> getsbigger(n);
     for(int i = 0; i < n; i++) {
          int total = 0;
          // getsbigger[i] = 0;
          int maxcost = 0;
          for(int j = 0; j < buildings[i].size(); j++) {
               total -= buildings[i][j].first;
               maxcost = max(maxcost, -1 * total);
               total += buildings[i][j].second;
               if(total > 0) {
                    p.push({maxcost, i});
                    break;
               }
          }
     }
     while(!p.empty()) {
          pair<int, int> a = p.top();
          p.pop();
          if(a.first > x) {
               break;
          }else {
               int total = 0;
               for(int j = getsbigger[a.second]; j < buildings[a.second].size(); j++) {
                    total -= buildings[a.second][j].first;
                    total += buildings[a.second][j].second;
                    if(total > 0) {
                         x += total;
                         getsbigger[a.second] = j+1;
                         int t = 0;
                         int maxval = 0;
                         for(int k = j + 1; k < buildings[a.second].size(); k++) {
                              t -= buildings[a.second][k].first;
                              maxval = max(maxval, -1 * t);
                              t += buildings[a.second][k].second;
                              if(t > 0) {
                                   p.push({maxval, a.second});
                                   break;
                              }
                         }
                         break;
                    }
               }
          }
     }
     int minindex = 1;
     int maxval = 0;
     for(int i = 0; i < n; i++) {
          int total = x;
          for(int j = getsbigger[i]; j < buildings[i].size(); j++) {
               total -= buildings[i][j].first;
               if(total < 0) {
                    if(j > maxval) {
                         maxval = j;
                         minindex = i+1;
                    }
                    break;
               }
               total += buildings[i][j].second;
          }
          if(total >= 0) {
               if(buildings[i].size() > maxval) {
                    maxval = buildings[i].size();
                    minindex = i+1;
               }
          }
     }
     cout<<maxval<<' '<<minindex<<'\n';
}

signed main() {
     int t;
     // t = 1;
     cin >>  t;
     while(t--) {
          solve();
     }
     return 0;
}
