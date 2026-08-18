#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
     int n;
     cin >> n;
     vector<int> arr(n);
     for(int i = 0; i < n; i++) cin >> arr[i];
     vector<int> b = arr;
     sort(b.begin(), b.end());
     int minval = (b[0] + 1) / 2 + (b[1] + 1) / 2;
     for(int i = 0; i < n; i++) {
          int total = (arr[i] + 1) / 2;
          int left = INT_MAX, right = INT_MAX;
          if(i != 0) left = arr[i-1];
          if(i != n-1) right = arr[i+1];
          minval = min(minval, max(left, right));
          left -= total;
          right -= total;
          minval = min(minval, total + max(0ll, (left + 1) / 2));
          minval = min(minval, total + max(0ll,(right + 1) / 2));
     }
     for(int i = 0; i < n-1; i++) {
          int a = arr[i];
          int c = arr[i+1];
          if(a * 2 >= c && c * 2 >= a) {
               minval = min(minval, (a + c + 2) / 3);
          }else {
               minval = min(minval, (max(a, c) + 1) / 2);
          }
     }
     for(int i = 0; i < n-2; i ++) {
          int a = arr[i];
          int c = arr[i+2];
          minval = min(minval, min(a, c) + (max(a, c) - min(a, c) + 1) / 2);
          // minval = min(minval, (a + c) / 2);
     }
     cout<<minval<<'\n';
     return 0;
}
