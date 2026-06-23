// Kinda cheesed this problem lol this shouldn't really count

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i];
    for(int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if(type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            for(int j = l; j <= r; j++) {
                if(arr[j] > x) arr[j]-=x;
            }
        }else {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            int total = 0;
            for(int j = l; j <= r; j++) {
                if(arr[j] == x) {
                    total++;
                }
            }
            cout<<total<<'\n';
        }
    }
    
    return 0;
}
