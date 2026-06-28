// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;

string a, b;
bool seena[2005][2005][2];
int cacheda[2005][2005][2];
int m, d;
const int MOD = 1e9+7;
int dpa(int pos, int mod, bool big) {
    if(seena[pos][mod][big]) return cacheda[pos][mod][big];
    seena[pos][mod][big] = true;
    if(pos == a.size()) {
        if(mod == 0) return cacheda[pos][mod][big] = 1-big;
        return cacheda[pos][mod][big] = 0;
    }
    if(pos % 2 == 1 && big && a[pos] -  '0' < m) return cacheda[pos][mod][big] = 0;
    if(pos % 2 == 1 && big && a[pos] - '0' == m) return cacheda[pos][mod][big] = dpa(pos + 1, (mod * 10 + m) % d, true);
    if(pos % 2 == 1) return cacheda[pos][mod][big] = dpa(pos + 1, (mod * 10 + m) % d, false);
    int total = 0;
    if(big == 1) {
        if(a[pos] - '0' != m)  total += dpa(pos + 1, (mod * 10 + a[pos]-'0') % d, true);
        total = total % MOD;
        for(int i = 0 ; i < a[pos] - '0'; i++) {
            if(i != m) {
                total += dpa(pos + 1,(mod * 10 + i) % d, false);
                total = total % MOD;
            }
        }
    }else {
        for(int i = 0 ; i < 10; i++) {
            if(i != m) {
                total += dpa(pos + 1,(mod * 10 + i) % d, false);
                total = total % MOD;
            }
        }
    }
    return cacheda[pos][mod][big] = total;
}
bool seenb[2005][2005][2];
int cachedb[2005][2005][2];
int dpb(int pos, int mod, bool big) {
    if(seenb[pos][mod][big]) return cachedb[pos][mod][big];
    seenb[pos][mod][big] = true;
    if(pos == b.size()) {
        if(mod == 0) return cachedb[pos][mod][big] = 1;
        return cachedb[pos][mod][big] = 0;
    }
    if(pos % 2 == 1 && big && b[pos] -  '0' < m) return cachedb[pos][mod][big] = 0;
    if(pos % 2 == 1 && big && b[pos] - '0' == m) return cachedb[pos][mod][big] = dpb(pos + 1, (mod * 10 + m) % d, true);
    if(pos % 2 == 1) return cachedb[pos][mod][big] = dpb(pos + 1, (mod * 10 + m) % d, false);
    int total = 0;
    if(big == 1) {
        if(b[pos] - '0' != m) total += dpb(pos + 1, (mod * 10 + b[pos]-'0') % d, true);
        total = total % MOD;
        for(int i = 0 ; i < b[pos] - '0'; i++) {
            if(i != m) {
                total += dpb(pos + 1,(mod * 10 + i) % d, false);
                total = total % MOD;
            }
        }
    }else {
        for(int i = 0 ; i < 10; i++) {
            if(i != m) {
                total += dpb(pos + 1,(mod * 10 + i) % d, false);
                total = total % MOD;
            }
        }
    }
    return cachedb[pos][mod][big] = total;
}
signed main() {
    cin >> d >> m;
    cin >> a >> b;
    cout<<(dpb(0, 0, 1) - dpa(0, 0, 1) + MOD * 10) % MOD<<'\n';
    return 0;
}
