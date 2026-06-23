// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
const int SQRT = 400;
bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    if(a.second.first / SQRT > b.second.first / SQRT) {
        return false;
    }else if(a.second.first / SQRT < b.second.first / SQRT) {
        return true;
    }else {
        return a.second.second < b.second.second;
    }
}
signed main() {
    int n, m, k;
    cin >> n >> m  >> k;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i];
    int prexor[n+1];
    prexor[0] = 0;
    for(int i = 1; i<=n ;i++) prexor[i] = prexor[i-1] ^ arr[i-1];
    // for(int i = 0; i < n; i++)prexor[i] = prexor[i+1];
    int l = 0, r = 0;
    vector<pair<int, pair<int, int>>> v;
    for(int i = 0; i < m; i++) {
        int ql, qr;
        cin >> ql >> qr;
        ql--;
        qr--;
        v.push_back({i, {ql, qr}});
    }
    sort(v.begin(), v.end(), cmp);
    unordered_map<int, int> ma;
    ma[prexor[1]] = 1;
    ma[0] ++;
    int ans[m];
    int total = 0;
    if(k == prexor[1]) total = 1;
    for(int i = 0; i < m ;i++) {
        while(r < v[i].second.second) {
            r++;
            total += ma[k ^ prexor[r+1]];
            ma[prexor[r+1]]++;
        }
        while(l > v[i].second.first) {
            l--;
            total += ma[k ^ prexor[l]];
            ma[prexor[l]]++;
        }
        while(r > v[i].second.second) {
            ma[prexor[r+1]] --;
            total -= ma[k ^ prexor[r+1]];
            r--;
        }
        while(l < v[i].second.first) {
             ma[prexor[l]] --;
            total -= ma[k ^ prexor[l]];
            l++;
        }
        ans[v[i].first] = total;
    }
    for(int i = 0; i < m; i++) {
        cout<<ans[i]<<'\n';
    }

}
