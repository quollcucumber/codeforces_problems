#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 100005;
bool isblack[MAXN];
bool seen[MAXN][2];
int cached[MAXN][2];
vector<int> children[MAXN];
const int MOD = 1e9+7;
int power(int a, int b) {
     if(b == 0) return 1;
     if(b % 2 == 1) return a * power(a*a % MOD,b/2) % MOD;
     return power(a*a % MOD,b/2) % MOD;
}
int inv(int a) {return power(a, MOD - 2);}
int dp(int node, bool numblack) {
     if(node == 1) {
          int q = 0;
     }
     if(seen[node][numblack]) return cached[node][numblack];
     seen[node][numblack] = true;
     if(numblack == 0 && isblack[node]) return cached[node][numblack] = 0;
     if(isblack[node] || numblack == 0) {
          int total = 1;
          for(int i : children[node]) {
               total *= dp(i, false) + dp(i, true);
               total = total % MOD;
          }
          return cached[node][numblack] = total;
     }else {
          int t = 1;
          for(int i : children[node]) {
               t *= dp(i, false) + dp(i, true);
               t = t % MOD;
          }
          int total = 0;
          for(int i : children[node]) {
               int val = t * inv(dp(i, false) + dp(i, true)) % MOD;
               val *= dp(i, true);
               val = val % MOD;
               total += val;
               total = total % MOD;
          }
          return cached[node][numblack] = total;
     }
}
signed main() {
     int n;
     cin >> n;
     for(int i = 1; i < n; i ++) {
          int a;
          cin >> a;
          children[a].push_back(i);
     }
     for(int i = 0; i < n; i++)  cin >> isblack[i];
     cout<<dp(0, 1)<<'\n';
}
