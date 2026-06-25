#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    vector<int> b(n);
    bool works = false;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        if(arr[i] < k) b[i] = 0;
        else if(arr[i] > k) b[i] = 2;
        else {
            b[i] = 1;
            works = true;
        }
    }
    if(!works) {
        cout<<"no\n";
        return;
    }
    if(n == 1 && arr[0] == k) {
        cout<<"yes\n";
        return;
    }
    for(int i = 0 ; i < n - 1; i++) {
        if(b[i] == 1 && b[i+1] != 0) {
            cout<<"yes\n";
            return;
        }
    }
    for(int i = 1; i < n; i++) {
        if(b[i] == 1 && b[i-1] != 0) {
            cout<<"yes\n";
            return;
        }
    }
    for(int i = 0; i < n - 2; i++) {
        int z = 0, o = 0, t = 0;
        for(int j = 0; j < 3; j++) {
            if(b[i+j] == 0) z++;
            if(b[i+j] == 1) o++;
            if(b[i+j] == 2) t++;
        }
        if(z == 1 && o == 1 && t == 1) {
            cout<<"yes\n";
            return;
        }
        if(o == 2) {
            cout<<"yes\n";
            return;
        }
        if(t >= 2) {
            cout<<"yes\n";
            return;
        }
    }
    cout<<"no\n";
}
signed main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
