#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 100005;
int tree[MAXN * 2];
void upd(int pos, int val) {
     tree[pos += MAXN] += val;
     for(pos /= 2; pos > 0; pos /= 2) tree[pos]=tree[pos*2]+tree[pos*2+1];
}
int query(int l, int r) {
     l+=MAXN,r+=MAXN;
     int total = 0;
     while(l < r) {
          if(l & 1) total+=tree[l++];
          if(r & 1) total+=tree[--r];
          l/=2;
          r/=2;
     }
     return total;
}
signed main() {
     int n, m;
     cin >> n >> m;
     vector<pair<pair<int, int>, pair<int, int>>> v;
     for(int i = 0; i < n; i++) {
          int t, a , b;
          cin >> t >> a >> b;
          v.push_back({{t, i}, {a,b}});
     }
     sort(v.begin(), v.end());
     int pos = 0;
     set<int> waiting;
     vector<vector<pair<int, int>>> atfloor(m + 1);
     vector<int> ans(n);
     int floor = 1;
     int time = 1;
     set<int> peopleinelev;
     set<pair<int, int>> up;
     set<pair<int, int>> down;
     while(true) {
          if(pos == v.size() && waiting.empty() && up.empty() && down.empty()) break;


          while(pos != v.size() && v[pos].first.first == time) {
               atfloor[v[pos].second.first].push_back({v[pos].second.second, v[pos].first.second});
               upd(v[pos].second.first, 1);
               waiting.insert(v[pos].second.first);
               pos++;
          }
          while(!atfloor[floor].empty()) {
               pair<int, int> a = atfloor[floor][atfloor[floor].size() - 1];
               if(a.first > floor) up.insert(a);
               else down.insert(a);
               upd(floor, -1);
               atfloor[floor].pop_back();
          }
          waiting.erase(floor);
          while(!up.empty() && up.begin()->first == floor) {
               pair<int, int> a = *up.begin();
               up.erase(up.begin());
               ans[a.second] = time;
          }
          while(!down.empty() && prev(down.end())->first == floor) {
               pair<int, int> a = *prev(down.end());
               down.erase(prev(down.end()));
               ans[a.second] = time;
          }


          int nexttime = INT_MAX;
          if(pos != v.size()) nexttime = min(nexttime, v[pos].first.first - time);
          if(!waiting.empty() && waiting.lower_bound(floor) != waiting.end()) nexttime = min(nexttime, *waiting.lower_bound(floor) - floor);
          if(!waiting.empty() && waiting.lower_bound(floor) != waiting.begin()) nexttime = min(nexttime,  floor - *prev(waiting.lower_bound(floor)));
          if(!up.empty()) nexttime = min(nexttime, up.begin()->first - floor);
          if(!down.empty()) nexttime = min(nexttime, floor - prev(down.end())->first);
          int pup = up.size() + query(floor + 1, MAXN);
          int pdown = down.size() + query(0, floor);
          if(pup != 0 || pdown != 0) {
               if(pup >= pdown) {
                    floor += nexttime;
               }else {
                    floor -= nexttime;
               }
          }
          time += nexttime;

     }
     for(int i = 0; i < n; i++) {
          cout<<ans[i]<<'\n';
     }
     return 0;
}
