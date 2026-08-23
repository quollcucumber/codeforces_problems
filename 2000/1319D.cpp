#include <bits/stdc++.h>
// #define int long long
using namespace std;
int dif(int a, int b) {
    return ((a&1)^(b&1)) + ((a&2)^(b&2))/2 +  ((a&4)^(b&4))/4;
}
vector<vector<bool>> v;
bool seen[1000005][8];
int cached[1000005][8];
int n, m;
int p;
int dp(int pos, int mask) {
    if (seen[pos][mask]) return cached[pos][mask];
    seen[pos][mask] = true;
    if (pos == m) return cached[pos][mask] = 0;
    int minval = INT_MAX;
    int maskarr = 0;
    for (int i = 0; i < n; i++) {
        maskarr *= 2;
        maskarr += v[i][pos];
    }
    for (int ma = 0; ma < p; ma++) {
        bool works = true;
        if (n > 1) {
            int t = (mask & 1) + (mask & 2) / 2 + (ma & 1) + (ma & 2) / 2;
            if (t % 2 == 0) works = false;
        }
        if (n > 2) {
            int t = (mask & 4)/4 + (mask & 2) / 2 + (ma & 4)/4 + (ma & 2) / 2;
            if (t % 2 == 0) works = false;
        }
        if (works) {
            minval = min(minval, dp(pos + 1, ma) + dif(ma, maskarr));
        }
    }
    return cached[pos][mask] = minval;
}
signed main() {
    cin >> n >> m;
    if (n > 3 && m > 3) {
        cout<<-1<<'\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        vector<bool> a;
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            a.push_back(c - '0');
        }
        v.push_back(a);
    }
    if (m < 4) {
        vector<vector<bool>> newv;
        for (int i = 0; i < m; i++) {
            vector<bool> a;
            for (int j = 0; j < n; j++) {
                a.push_back(v[j][i]);
            }
            newv.push_back(a);
        }
        v = newv;
        int tempm = m;
        m = n;
        n = tempm;
    }
    int minval = INT_MAX;
    int first = 0;
    for (int i = 0; i < n; i++) {
        first *=2;
        first += v[i][0];
    }
    int second = 0;
    for (int i = 0; i < n; i++) {
        second *=2;
        second += v[i][1];
    }
    p = pow(2, n);

    for (int mask = 0; mask < pow(2,n); mask++) {
        // bool works = true;
        // if (n > 1) {
        //     int t = (mask & 1) + (mask & 2) / 2 + (second & 1) + (second & 2) / 2;
        //     if (t % 2 == 0) works = false;
        // }
        // if (n > 2) {
        //     int t = (mask & 4)/4 + (mask & 2) / 2 + (second & 4)/4 + (second & 2) / 2;
        //     if (t % 2 == 0) works = false;
        // }
        // if (works)
        minval = min(minval, dp(1, mask) + dif(first, mask));
    }
    cout<<minval<<'\n';
}
