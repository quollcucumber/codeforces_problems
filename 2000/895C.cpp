// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
// #define int long long
using namespace std;
int num[75];
int mask[75];
bool seen[75][(1<<19)+5];
int cached[75][(1<<19)+5];
const int MOD = 1e9 + 7;
int dp(int pos, int m) {
    if(seen[pos][m]) return cached[pos][m];
    seen[pos][m] = true;
    if(pos == 71) {
        if(m == 0) return cached[pos][m] = 1;
        return cached[pos][m] = 0;
    }
    if(num[pos] == -1) return cached[pos][m] = dp(pos + 1, m);
    return cached[pos][m] = (long long)((long long)(long long)dp(pos + 1, m ^ mask[pos]) * (long long)num[pos]  + (long long)dp(pos + 1, m) * (long long)num[pos]) % (long long)MOD;
}
bool isprime(int a){
    for(int j = 2; j * j <= a; j++) if(a % j == 0) return false;
    return true;
}
signed main() {
    int n;
    cin >> n;
    for(int i = 0; i < 75; i++) num[i] = -1;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if(num[a] == -1) num[a] = 1;
        else num[a] = ((long long)num[a] * (long long)2) % (long long)MOD;
    }
    vector<int> primes;
    for(int i = 2; i <= 70; i++) {
        if(isprime(i)) primes.push_back(i);
    }
    for(int i = 1; i <= 70; i++) {
        int temp = i;
        for(int j = 0; j < primes.size(); j++) {
            mask[i] *= 2;
            int bit = 0;
            while(temp % primes[j] == 0) {
                bit ^= 1;
                temp /= primes[j];
            }
            mask[i] += bit;
        }
    }
    cout<<dp(1, 0)-1<<'\n';
}
