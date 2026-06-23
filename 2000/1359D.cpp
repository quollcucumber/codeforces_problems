// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
signed main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n ; i++) {
        cin >> arr[i];
    }
    unordered_map<int, int> maxtotal;
    for(int i = -30; i <= 30; i++) {
        maxtotal[i] = INT_MIN;
    }
    int maxval = 0;
    for(int i = 0; i < n; i++) {
        for(int j = -30; j < arr[i]; j++) maxtotal[j]= INT_MIN;
        for(int j = arr[i]; j <= 30; j++) maxtotal[j]+=arr[i];
        for(int j = arr[i]; j <= 30; j++) maxtotal[j] = max(arr[i], maxtotal[j]);
        // for(int j = -30; j <= 30; j++)
        //     cerr<< maxtotal[j] - j<<' ';
        // cerr<<'\n';
        for(int j = -30; j <= 30; j++)
            maxval = max(maxval,  maxtotal[j] - j);
    }
    cout<<maxval<<'\n';
}
