//https://codeforces.com/contest/242/problem/E
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int total;
    bool flip;
};
node segtree[400005][30];
// one segtree for each bit, um segtree[i][j] is like the ith node in the segtree bit worth 2^j
#define MAXN 100005
void prop(int node, int tree, int l, int r) {
    if(segtree[node][tree].flip) {
        segtree[node][tree].total = (r - l) - segtree[node][tree].total;
        if(l + 1 != r) {
            segtree[node * 2][tree].flip = 1 - segtree[node * 2][tree].flip;
            segtree[node * 2 + 1][tree].flip = 1 - segtree[node * 2 + 1][tree].flip;
        }
        segtree[node][tree].flip = false;
    }
}
void update(int left, int right,  int tree ,int pos = 1, int l = 0, int r = MAXN) {
    prop(pos, tree, l, r);
    if(l >= left && right >= r) {
        segtree[pos][tree].flip = true;
        prop(pos, tree, l, r);
        return;
    }
    int mid = (l + r) / 2;
    if(left < mid) {
        update(left, right, tree, pos * 2, l, mid);
    }
    if(right > mid) {
        update(left, right, tree, pos * 2 +1 , mid, r);
    }
    prop(pos, tree, l, r);
    prop(pos * 2, tree, l, mid);
    prop(pos * 2 + 1, tree, mid, r);
    segtree[pos][tree].total = segtree[pos * 2][tree].total + segtree[pos * 2 + 1][tree].total;
}
int query(int left, int right, int tree, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos, tree, l, r);
    if(l >= left && right >= r) {
        return segtree[pos][tree].total;
    }
    int total = 0;
    int mid = (l + r) / 2;
    if(left < mid) {
        total += query(left, right, tree, pos * 2, l, mid);
    }
    if(right > mid) {
        total += query(left, right, tree, pos * 2 + 1, mid, r);
    }
    return total;
}
signed main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int pos = 0;
        while(a > 0) {
            if(a % 2) {
                update(i, i + 1, pos);
            }
            a/= 2;
            pos++;
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        // for(int j = 0; j < n; j++) {
        // int t = 0;
        // for(int k = 0; k < 30; k++) t += pow(2, k) * query(j, j + 1, k);
        //     cout<<t<<' ';
        // }
        // cout<<'\n';
        int t;
        cin >> t;
        if(t == 1) {
            int l, r;
            cin >> l >> r;
            l--;
            int total = 0;
            int num = 1;
            for(int j = 0; j < 30; j++) {
                total += num * query(l, r, j);
                num*= 2;
            }
            cout<<total<<'\n';
        }else {
            int l, r, x;
            cin >> l>> r >>x;
            l--;
            int pos = 0;
            for(int j = 0; j < 30; j++) {
                if(x % 2== 1) {
                    update(l, r, pos);
                }
                x /= 2;
                pos++;
            }
        }
    }
}
