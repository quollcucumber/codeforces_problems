// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
using namespace std;
// #define int long long
typedef long long ll;
int n, k;
vector<pair<int, int>> arr;
#define NUMFIVES (26*205)
int cached1[205][NUMFIVES];
int cached2[205][NUMFIVES];
signed main() {
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        pair<int, int> ans = {0, 0};
        while(a % 2 == 0) {
            ans.first++;
            a/=2;
        }
        while(a % 5 == 0) {
            ans.second++;
            a/=5;
        }
        arr.push_back(ans);
    }
    int mv = 0;
    for(int pos = n; pos >= 0; pos--) {
        for(int i = 0; i < 205; i ++) for(int j = 0; j < NUMFIVES; j++) cached1[i][j] = cached2[i][j];

        for(int left = 0; left <= k; left++) {
            for(int fivesneeded = 0; fivesneeded < NUMFIVES; fivesneeded++) {
                if(pos == n) {
                    if(fivesneeded == 0)  cached2[left][fivesneeded] = 0;
                    else cached2[left][fivesneeded] = INT_MIN;
                }else {
                    int maxval = cached1[left][fivesneeded];
                    if(left != 0) maxval = max(maxval,  cached1[left - 1][ max(0, fivesneeded - arr[pos].second)] + arr[pos].first);
                    cached2[left][fivesneeded] = maxval;
                    if(pos == 0 && left == k && maxval >= fivesneeded) {
                        mv = max(mv, fivesneeded);
                    }
                }
            }
        }
    }
    cout<<mv<<'\n';
    return 0;
}
