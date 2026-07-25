#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
using namespace std;
#define int long long
void solve() {
    int n, m;
    cin >> n >> m ;
    vector<vector<bool>> arr(n);
    vector<int> sum(n);
    int t = 0;
    for(int i = 0; i <n ; i++) {
        int total = 0;
        arr.push_back({});
        for(int j = 0; j < m; j++) {
            char a;
            cin >> a;
            arr[i].push_back(a - '0');
            if(a == '1') total++;
        }
        sum[i] = total;
        t += total;
    }
    if(t % n != 0 ) {
        cout<<-1<<'\n';
        return;
    }
    int ans = 0;
    vector<pair<pair<int, int>, int>> v;
    for(int i = 0; i < m; i++) {
        set<pair<int, int>> ones;
        set<pair<int, int>> zeros;
        for(int j = 0; j < n; j++) {
            if(arr[j][i]) {
                ones.insert({sum[j], j});
            }else {
                zeros.insert({sum[j], j});
            }
        }
        while(true) {
            if(zeros.empty() || ones.empty()) break;
            pair<int, int> a = *prev(ones.end());
            pair<int, int> b = *zeros.begin();
            ones.erase(a);
            zeros.erase(b);
            if(a.first > t/n && b.first < t/n) {
                sum[a.second]--;
                sum[b.second]++;
                ans++;
                v.push_back({{a.second, b.second}, i});
            }
        }
    }
    set<int> check;
    for(int i = 0; i <n; i++) check.insert(sum[i]);
    // if(check.size() != 1) {
    //     cout<<-1<<'\n';
    //     return;
    // }
    cout<<ans<<'\n';
    for(int i = 0; i < v.size(); i++) {
        cout<<v[i].first.first+1<<' '<<v[i].first.second+1<<' '<<v[i].second+1<<'\n';
    }
}
signed main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
