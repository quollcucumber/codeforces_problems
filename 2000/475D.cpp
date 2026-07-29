#include <bits/stdc++.h> // very not code golfed trust
#define int long long
using namespace std;
const int MAXN = 100005;
int tree[MAXN * 2];
// void upd(int pos, int val) {
//     tree[pos += MAXN] = val;
//     for(pos /= 2; pos> 0; pos /= 2) tree[pos] = gcd(tree[pos * 2], tree[pos * 2 + 1]);
// }
// int query(int left, int right) {
//     left += MAXN;
//     right += MAXN;
//     int gcdval = -1;
//     while(left < right) {
//         if(left & 1) {
//             if(gcdval == -1) gcdval = tree[left++];
//             else gcdval = gcd(gcdval, tree[left++]);
//         }
//         if(right & 1) {
//             if(gcdval == -1) gcdval = tree[--right];
//             else gcdval = gcd(gcdval,tree[--right]);
//         }
//         left /= 2;
//         right /= 2;
//     }
//     return gcdval;
// }
// frick my segtree TLE I need to make sparse table
int table[100005][20];
void init(vector<int>  * a) {
    for(int i = 0; i < a->size(); i++) {
        table[i][0] = (*a)[i];
    }
    for(int i = 1; i < 20; i++) {
        int prevlen = pow(2, i-1);
        for(int j = 0; j < a->size(); j++) {
            if(j + prevlen < 100005)table[j][i] = gcd(table[j][i-1], table[j+prevlen][i-1]);
        }
    }
}
int query(int left, int right) {
    int d = (right - left  + 1);
    int a = log2(d);
    return gcd(table[left][a], table[right - (int)pow(2, a) + 1][a]);
}

signed main() {
    map<int, int> vals;
    int n; cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    init(&arr);
    // for(int i = 0; i < n; i++) upd(i, arr[i]);
    for(int i = 0; i < n; i++) {
        int j = i;
        int t = 0;
        int gcdval = arr[i];
        while(j != n) {
            t++;
            assert(t<=60);
            int l = j, r = n;
            while(l + 1 < r) {
                int mid = (l + r) / 2;
                if(query(i, mid) == gcdval) {
                    l = mid;
                }else {
                    r = mid;
                }
            }
            vals[gcdval] += (l - j + 1);
            gcdval = query(i, r);
            j = r;
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int a;
        cin >> a;
        cout<<vals[a]<<'\n';
    }
}
