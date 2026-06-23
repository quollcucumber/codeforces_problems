#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
struct node {
    int total;
    int maxval;
    int maxpos;
};
node merge(node a, node b) {
    node newnode;
    newnode.total = a.total +  b.total;
    if(a.maxval > b.maxval) {
        newnode.maxval = a.maxval;
        newnode.maxpos = a.maxpos;
    }else {
        newnode.maxval = b.maxval;
        newnode.maxpos = b.maxpos;
    }
    return newnode;
}
#define MAXN 100005
node tree[MAXN * 2];
void upd(int pos, int val){
    pos += MAXN;
    tree[pos] = {val, val, pos - MAXN};
    pos /= 2;
    while(pos != 0) {
        tree[pos] = merge(tree[pos * 2], tree[pos * 2 + 1]);
        pos /= 2;
    }
}
node query(int l, int r){
    node a ={0, -1 ,-1};
    l += MAXN;
    r += MAXN;
    while(l < r) {
        if(l & 1) a = merge(a, tree[l++]);
        if(r & 1) a = merge(a, tree[--r]);
        l /= 2;
        r /= 2;
    }
    return a;
}
signed main() {
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        upd(i, a);
    }
    for(int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if(type == 1) {
            int l, r;
            cin >> l >> r;
            l--;
            cout<<query(l, r).total<<'\n';
        }else if(type == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            while(true) {
                node ans = query(l, r);
                if(ans.maxval >= x) {
                    upd(ans.maxpos, ans.maxval % x);
                }else {
                    break;
                }
            }
        }else {
            int pos, val;
            cin >> pos >> val;
            upd(pos - 1, val);
        }
    }
}
