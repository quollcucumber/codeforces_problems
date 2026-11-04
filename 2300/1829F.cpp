//wtf is this problem hella peak

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
// #define int long long
using namespace std;

signed main() {
     int n, m;
     cin >> n >> m;
     map<pair<int, int>, bool> ma;
     for(int i = 0; i < m; i++) {
          int a, b;
          cin >>a >> b;
          ma[{a, b} ] = 1;
          ma[{b, a}] = 1;
     }
     for(int i = 1; i <= n; i++) {
          for(int j = i + 1; j <= n; j++) {
               if(!ma[{i, j}]) {
                    for(int k = j + 1; k <= n; k++) {
                         if(!ma[{k, j}] && !ma[{i, k}]) {
                              for(int l = k + 1; l <= n; l++) {
                                   if(!ma[{k, l}] && !ma[{i, l}] && !ma[{j, l}]) {
                                        for(int last = l + 1; last <= n; last++) {
                                             if(!ma[{k, last}] && !ma[{last, l}] && !ma[{j, last}] && !ma[{last, i}]) {
                                                  cout<<i << ' '<< j <<' '<<k<<' '<<l<<' '<<last<<'\n';
                                                  return 0;
                                             }
                                        }
                                   }
                              }
                         }
                    }
               }
          }
     }
     for(int i = 1; i <= n; i++) {
          for(int j = i + 1; j <= n; j++) {
               if(ma[{i, j}]) {
                    for(int k = j + 1; k <= n; k++) {
                         if(ma[{k, j}] && ma[{i, k}]) {
                              for(int l = k + 1; l <= n; l++) {
                                   if(ma[{k, l}] && ma[{i, l}] && ma[{j, l}]) {
                                        for(int last = l + 1; last <= n; last++) {
                                             if(ma[{k, last}] && ma[{last, l}] && ma[{j, last}] && ma[{last, i}]) {
                                                  cout<<i << ' '<< j <<' '<<k<<' '<<l<<' '<<last<<'\n';
                                                  return 0;
                                             }
                                        }
                                   }
                              }
                         }
                    }
               }
          }
     }
     cout<<-1<<'\n';
     return 0;
}
