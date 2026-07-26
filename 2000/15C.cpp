#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
int f(int x) {
    if(x % 4 == 0) return x;
    if(x % 4 == 1) return 1;
    if(x % 4 == 2) return x + 1;
    return 0;
}
int ans(int l, int r) {
    return f(r) ^ f(l-1);
}
signed main() {
    int n;
    cin >> n;
    int xorval = 0;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a>> b;
        xorval ^= ans(a, a + b - 1);
    }
    if(xorval != 0) {
        cout<<"tolik\n";
    }else {
        cout<<"bolik\n";
    }
    return 0;
}
