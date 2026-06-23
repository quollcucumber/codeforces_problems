#include <bits/stdc++.h>
// #define int long long
using namespace std;
int MAXN = 10000005;

signed main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   bitset<20000005> done(0);
   bitset<20000005> prime(0);
   int n;
   cin >> n;
   vector<int> factors[n];
   int arr[n];
   unordered_map<int, int> m;
   for(int i = 0; i < n; i++) {
      cin >> arr[i];
      m[arr[i]] = i;
      done[arr[i]] = true;
   }
   // int smallfactor[MAXN];
   // int bigfactor[MAXN];
   // for(int i = 0; i < MAXN; i++) smallfactor[i] = 1;

   for(int i = 2; i < MAXN; i++) {
      if(!prime[i]) {
         prime[i] = true;
         if(done[i]) {
            factors[m[i]].push_back(i);
         }
         for(int j = i * 2; j < MAXN; j += i) {
            prime[j] = true;
            if(done[j]) {
               factors[m[j]].push_back(i);
            }
         }
      }
   }
   // for(int i =0; i < n; i++) {
   //    if(factors[i].empty()) {
   //       cout<<i<<'\n';
   //    }
   // }
   int a[n];
   int b[n];
   for(int i = 0;i < n; i ++) {
      if(m[arr[i]] != i) {
         int newi = m[arr[i]];
         int total = 1;
         for(int j = 1; j < factors[newi].size(); j++) total *= factors[newi][j];
         if(!factors[newi].empty()) total += factors[newi][0];
         if(gcd(total, arr[newi]) == 1 && factors[newi].size() >= 2) {
            a[i] = total - factors[newi][0];
            b[i] = factors[newi][0];
         }else{
            a[i] = -1;
            b[i] = -1;
         }
      }else {
         int total = 1;
         for(int j = 1; j < factors[i].size(); j++) total *= factors[i][j];
         if(!factors[i].empty()) total += factors[i][0];
         if(gcd(total, arr[i]) == 1 && factors[i].size() >= 2) {
            a[i] = total - factors[i][0];
            b[i] = factors[i][0];
         }else{
            a[i] = -1;
            b[i] = -1;
         }
      }
   }
   for(int i = 0; i < n; i++) {
      cout<<a[i]<<' ';
   }
   cout<<'\n';
   for(int i = 0; i < n; i++) {
      cout<<b[i]<<' ';
   }
   cout<<'\n';

   return 0;
}
