#include <bits/stdc++.h>
// #define int long long
using namespace std;
#define SQRT 200
int nextarr[100005][SQRT];
signed main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    int query;
    cin >> query;
    for(int k = SQRT - 1; k >= 1; k--) {
        for(int j = n; j >= 1; j--) {
            if(j + arr[j-1] + k > n) {
                nextarr[j][k] = 1;
            }else {
                nextarr[j][k] = nextarr[j + arr[j-1] + k][k] + 1;
            }
        }
    }
    for(int i = 0; i < query; i++) {
        int p, k;
        cin >> p >> k;
        if(k >= SQRT) {
            int t = 0;
            while(p <= n) {
                t++;
                p = p + k + arr[p-1];
            }
            cout<<t<<'\n';
        }else {
            cout<<nextarr[p][k]<<'\n';
        }
    }
    return 0;
}
