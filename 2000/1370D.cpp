// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> v;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        v.push_back(a);
    }
    int l = 0, r = (int)(1e9) + 1; // 1e9 - eventual result
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        vector<int> vec;
        for(int j = 0; j < n; j++) {
            if(vec.size() % 2 == 0) {
                vec.push_back(v[j]);
            }else {
                if(v[j] <= (int)1e9 - mid) {
                    vec.push_back(v[j]);
                }
            }
        }
        if(vec.size() >= k) {
            l = mid;
        }else {
            r = mid;
        }
    }
    int minval = (int)1e9 - l;
    l = 0, r = (int)(1e9) + 1;
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        vector<int> vec;
        for(int j = 0; j < n; j++) {
            if(vec.size() % 2 == 1) {
                vec.push_back(v[j]);
            }else {
                if(v[j] <= (int)1e9 - mid) {
                    vec.push_back(v[j]);
                }
            }
        }
        if(vec.size() >= k) {
            l = mid;
        }else {
            r = mid;
        }
    }
    cout<<min(minval, (int)1e9 - l);
}
