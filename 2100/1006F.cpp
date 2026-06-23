#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int arr[n][m];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    queue<pair<int, pair<int, int>>> q;
    int dist = n + m - 2;
    int f = dist / 2;
    int s = dist - f;
    q.push({arr[0][0], {0, 0}});
    for(int j = 0; j <f; j++) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            pair<int, int> loc = q.front().second;
            int xorval = q.front().first;
            q.pop();
            if(loc.second != m-1) q.push({xorval ^ arr[loc.first][loc.second+1], {loc.first, loc.second+1}});
            if(loc.first != n-1) q.push({xorval ^ arr[loc.first+1][loc.second], {loc.first+1, loc.second}});
        }
    }
    queue<pair<int, pair<int, int>>> back;
    back.push({0, {n-1, m-1}});
    for(int j = 0; j < s; j++) {
        int sz = back.size();
        for(int i = 0; i < sz; i++) {
            pair<int,int> loc = back.front().second;
            int xorval = back.front().first;
            back.pop();
            if(loc.second != 0) back.push({xorval ^ arr[loc.first][loc.second], {loc.first, loc.second-1}});
            if(loc.first != 0) back.push({xorval ^ arr[loc.first][loc.second], {loc.first-1, loc.second}});
        }
    }
    unordered_map<int, int> a[n][m];
    while(!back.empty()) {
        pair<int, int> loc = back.front().second;
        int xorval = back.front().first;
        a[loc.first][loc.second][xorval]++;
        back.pop();
    }
    int total = 0;
    while(!q.empty()) {
        pair<int,int> loc = q.front().second;
        int val = q.front().first;
        q.pop();
        total += a[loc.first][loc.second][val ^ k];
    }
    cout<<total<<'\n';
}
