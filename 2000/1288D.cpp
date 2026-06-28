#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
bool seen[300005][256];
bool cached[300005][256];
int mask[300005];
int need = 1;
int n, m;
bool dp(int pos, int ma) {
    if (pos == n) return false;
    if (seen[pos][ma]) return cached[pos][ma];
    seen[pos][ma] = true;
    if ((mask[pos] | ma) == need)  return cached[pos][ma] = true;
    return cached[pos][ma] = dp(pos + 1, ma);
}
bool works(int a, vector<vector<int>> * arr) {
    if (a == 3) {
        int q = 0;
    }
    // memset(seen, false, sizeof(seen));
    set<int> s;
    for (int i = 0; i < n; i++) {
        int ma = 0;
        for (int j = 0; j < m; j++) {
            if ((*arr)[i][j] >= a) {
                ma = ma * 2 + 1;
            }else {
                ma = ma * 2;
            }
        }
        mask[i] = ma;
        s.insert(ma);
    }
    for (int i : s) {
        for (int j : s) {
            if ((i | j) == need) return true;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     if (dp(i, mask[i])) {
    //         return true;
    //     }
    // }
    return false;
}
signed main() {
    cin >> n >> m;
    for (int i = 0; i < m-1; i++) need = need * 2 + 1;
    vector<vector<int>> arr(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            arr[i].push_back(a);
        }
    }
    int l = 0, r = 1e9+5;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (works(mid, &arr)) {
            l = mid;
        }else {
            r = mid;
        }
    }
    memset(seen, false, sizeof(seen));
    for (int i = 0; i < n; i++) {
        int ma = 0;
        for (int j = 0; j < m; j++) {
            if ((arr)[i][j] >= l) {
                ma = ma * 2 + 1;
            }else {
                ma = ma * 2;
            }
        }
        mask[i] = ma;
    }
    for (int i = 0; i < n; i++) {
        if (dp(i, mask[i])) {
            for (int j = i; j < n; j++) {
                if ((mask[i] | mask[j]) == need) {
                    cout<<i + 1<<' '<<j + 1<<'\n';
                    return 0;
                }
            }
        }
    }
}
