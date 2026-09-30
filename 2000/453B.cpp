#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
bool seen[105][1<<17];
int cached[105][1<<17];
int arr[105];
int n;
signed main() {
     cin >> n;
     for(int i = 0; i < n; i++) cin >> arr[i];
     // cout<<dp(0, 0)<<'\n';
     // dp(0, 0);
     vector<int> masks(61);
     for(int i = 1; i <= 60; i++) {
          for(int j = 0; j < 17; j++) {
               if(i % (primes[j]) == 0) {
                    masks[i] += (1<<j);
               }
          }
     }
     for(int pos = n; pos >= 0; pos--) {
          for(int mask = (1<<17) -1; mask >= 0; mask--) {
               if(pos == n) {
                    cached[pos][mask] = 0;
                    continue;
               }
               int minval = INT_MAX;
               for(int i = 1; i <= 60; i++) {
                    int maska = masks[i];
                    if((maska & mask) == 0) {
                         minval = min(minval, abs(i - arr[pos]) +  cached[pos + 1][maska | mask]);
                    }
               }
               cached[pos][mask] = minval;
          }
     }
     int mask = 0;
     for(int k = 0; k < n; k++) {
          for(int i = 1; i <= 60; i++) {
               int maska = 0;
               for(int j = 0; j < 17; j++) {
                    if(i % (primes[j]) == 0) {
                         maska += (1<<j);
                    }
               }
               if(((maska & mask) == 0) && abs(i-arr[k]) + cached[k + 1][maska | mask] == cached[k][mask]) {
                    mask = mask | maska;
                    cout<<i<<' ';
                    break;
               }
          }
     }
     return 0;
}
