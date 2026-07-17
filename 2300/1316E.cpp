#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<pair<int, int>> a;
const int maxmask = 128;
bool seen[100005][maxmask];
int cached[100005][maxmask];
int s[100005][7];
int n, p, k;
signed main() {
    cin >> n >> p >> k;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        a.push_back({val, i});
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            cin >>s[i][j];
        }
    }
    for(int pos = n; pos >= 0; pos--) {
        for(int mask = pow(2, p) - 1; mask >= 0; mask--) {
            if (pos == n) {
                if (mask == pow(2, p) - 1) cached[pos][mask] = 0;
                else cached[pos][mask] = -1e12;
            }else {
                int numchosen = pos;
                for (int i =0; i < p; i++) {
                    if ((mask & (1<<i)) != 0) {
                        numchosen--;
                    }
                }
                int maxval = 0;
                for (int i =0; i < p; i++) {
                    if ((mask & (1<<i)) == 0) {
                        maxval = max(maxval, cached[pos + 1][ mask + (1 << i)] + s[a[pos].second][i]);
                    }
                }
                if (numchosen < k) maxval = max(maxval, cached[pos + 1][ mask] + a[pos].first);
                else maxval = max(maxval, cached[pos + 1][ mask]);
                cached[pos][mask] = maxval;
            }
        }
    }
    cout<<cached[0][0]<<'\n';
}
