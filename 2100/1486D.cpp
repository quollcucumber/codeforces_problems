// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for(int i = 0;i <n;i++) cin >> arr[i];
    int l = 0, r = n + 1;
    while(l +1  < r) {
        int mid = (l + r) / 2;
        vector<bool> a(n);
        for(int i = 0; i < n; i++) {
            if(arr[i] >= mid) {
                a[i] = 1;
            }else {
                a[i] = 0;
            }
        }
        vector<int> t(n);
        int total = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] == 1) total++;
            else total--;
            t[i] = total;
        }
        vector<int> maxval(n);
        int mv = INT_MIN;
        for(int i = n-1; i >= 0; i--) {
            mv = max(mv, t[i]);
            maxval[i] = mv;
        }
        bool works = false;
        for(int i = 1; i < n - k + 1; i ++) {
            if(maxval[i + k - 1] - t[i-1] > 0) works = true;
        }
        if(maxval[k-1] > 0) works = true;
        if(works) {
            l = mid;
        }else {
            r = mid;
        }
    }
    cout<<l<<'\n';
    return 0;
}
