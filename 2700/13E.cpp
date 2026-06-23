#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
const int SQRT = 300;
int block(int i) {return i/SQRT;}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for(int i = 0;i < n ; i++) cin >> arr[i];
    vector<pair<int, int>> forward(n);
    for(int i = n-1; i >= 0; i--) {
        if(arr[i] + i >= n) {
            forward[i] = {0, i};
        }else {
            if(block(arr[i] + i) != block(i)) {
                forward[i] = {1, arr[i] + i};
            }else {
                forward[i] = {forward[arr[i] + i].first + 1, forward[arr[i] + i].second};
            }
        }
    }
    for(int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if(type == 0) {
            int a, b;
            cin >> a >> b;
            a--;
            arr[a] = b;
            for(int j =min(n-1, block(a) * SQRT + SQRT - 1); j >= block(a) * SQRT; j--) {
                if(arr[j] + j >= n) {
                    forward[j] = {0, j};
                }else {
                    if(block(arr[j] + j) != block(j)) {
                        forward[j] = {1, arr[j] + j};
                    }else {
                        forward[j] = {forward[arr[j] + j].first + 1, forward[arr[j] + j].second};
                    }
                }
            }
        }else {
            int a;
            cin >> a;
            int pos = a-1;
            int total = 0;
            while(forward[pos].second != pos) {
                total += forward[pos].first;
                pos = forward[pos].second;
            }
            cout<<forward[pos].second+1<<' '<<total+1<<'\n';
        }
    }
}
