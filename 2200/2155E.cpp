#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
     int n, m, k;
     cin >> n >> m >> k;
     map<int, int> score;
     for(int i = 0; i < k; i++) {
          int x, y;
          cin >> x >> y;
          x--, y--;
          score[y]++;
     }
     if(n == 1) {
          if(score[1] % 2) cout<<"Mimo\n";
          else cout<<"Yuyu\n";
          return;
     }
     bool works = true;
     for(pair<int, int> i : score) {
          if(i.first != 0 && i.second % 2 == 1) works = false;
     }
     // works = works ^ (score[0] % 2);
     if(works) {
          cout<<"Yuyu\n";
     }else {
          cout<<"Mimo\n";
     }
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
