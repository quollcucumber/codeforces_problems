#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int minval;
    int numoc;
    int gcdval;
};
#define MAXN 100005
node tree[MAXN * 2];
node merge(node a, node b) {
    node ans;
    if(a.minval < b.minval) {
        ans.minval = a.minval;
        ans.numoc = a.numoc;
    }else if(a.minval > b.minval) {
        ans.minval = b.minval;
        ans.numoc = b.numoc;
    }else {
        ans.minval = a.minval;
        ans.numoc = a.numoc  + b.numoc;
    }
    ans.gcdval = gcd(a.gcdval, b.gcdval);
    return ans;
}
void upd(int index, int val) {
    index += MAXN;
    tree[index] = {val, 1, val};
    for(index /= 2; index > 0; index /= 2) {
        tree[index] = merge(tree[index * 2], tree[index * 2 + 1]);
    }
}
int query(int left, int right) {
    int sz = right - left;
    int gcdans = -1;
    left += MAXN;
    right += MAXN;
    int minval = INT_MAX;
    int numocc = 0;
    while(left < right) {
        if(left & 1) {
            if(gcdans == -1) {
                gcdans = tree[left].gcdval;
            }else {
                gcdans = gcd(gcdans, tree[left].gcdval);
            }
            if(minval > tree[left].minval) {
                minval = tree[left].minval;
                numocc = tree[left].numoc;
            }else if(minval == tree[left].minval) {
                numocc += tree[left].numoc;
            }
            left++;
        }
        if(right & 1) {
            right--;
            if(gcdans == -1) {
                gcdans = tree[right].gcdval;
            }else {
                gcdans = gcd(gcdans, tree[right].gcdval);
            }
            if(minval > tree[right].minval) {
                minval = tree[right].minval;
                numocc = tree[right].numoc;
            }else if(minval == tree[right].minval) {
                numocc += tree[right].numoc;
            }
        }
        left /= 2;
        right /= 2;
    }
    if(gcdans != minval) {
        return sz;
    }else {
        return sz - numocc;
    }
}
signed main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        upd(i, a);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout<<query(l, r + 1)<<'\n';
    }
    return 0;
}
