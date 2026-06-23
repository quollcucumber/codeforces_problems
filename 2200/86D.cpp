#include <bits/stdc++.h>
#define int long long
using namespace std;
int sqrtv = 400;
bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
   if(a.first.first / sqrtv < b.first.first / sqrtv) return true;
   if(a.first.first / sqrtv > b.first.first / sqrtv) return false;
   return a.first.second < b.first.second;
}
signed main() {
   int n, q;
   cin >>  n >> q;
   int arr[n+1];
   for(int i = 1; i <= n; i++) {
      cin >> arr[i];
   }
   vector<pair<pair<int, int>, int>> v;
   for(int i = 0; i < q; i++) {
      int l, r;
      cin >> l >> r;
      v.push_back({{l, r}, i});
   }
   sort(v.begin(), v.end(), cmp);
   int m[1000005];
   memset(m, 0, sizeof(m));
   int total = 0;
   for(int i = v[0].first.first; i <= v[0].first.second; i++) {
      m[arr[i]]++;
      total += arr[i] * (m[arr[i]] + m[arr[i]] - 1);
   }
   int l = v[0].first.first;
   int r = v[0].first.second;
   int ans[q];
   ans[v[0].second] = total;
   for(int i = 1; i < q; i++) {
      while(v[i].first.first < l) {
         l--;
         m[arr[l]]++;
         total += arr[l] * (m[arr[l]] + m[arr[l]]-1);
      }
      while(v[i].first.second > r) {
         r++;
         m[arr[r]]++;
         total += arr[r] * (m[arr[r]] + m[arr[r]]-1);
      }
      while(v[i].first.first > l) {
         total -= arr[l] * (m[arr[l]] + m[arr[l]] - 1);
         m[arr[l]]--;
         l++;
      }
      while(v[i].first.second < r) {
         total -= arr[r] * (m[arr[r]] + m[arr[r]] - 1);
         m[arr[r]]--;
         r--;
      }
      ans[v[i].second] = total;
   }
   for(int i = 0; i < q; i++) {
      cout<<ans[i]<<'\n';
   }
   return 0;
}
