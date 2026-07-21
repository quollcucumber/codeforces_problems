#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
// #define int long long
using namespace std;
const int MAXN = 35005;
struct node {
    int maxval;
    int lazyadd;
};
node tree[MAXN * 4][55];
void prop(int node, int arr, int l, int r) {
    // tree[node][arr].maxval += tree[node][arr].lazyadd;
    if(l + 1 != r) {
        tree[node * 2][arr].lazyadd += tree[node][arr].lazyadd;
        tree[node * 2+ 1][arr].lazyadd += tree[node][arr].lazyadd;
        tree[node * 2][arr].maxval += tree[node][arr].lazyadd;
        tree[node * 2+ 1][arr].maxval += tree[node][arr].lazyadd;
    }
    tree[node][arr].lazyadd = 0;
}
void upd(int left, int right, int arr, int val,  int pos = 1, int l = 0, int r = MAXN) {
    prop(pos, arr, l, r);
    if(left <= l && right >= r) {
        tree[pos][arr].lazyadd += val;
        tree[pos][arr].maxval += val;
        return;
    }
    int mid = (l + r) / 2;
    if(left < mid) {
        upd(left, right, arr, val, pos * 2, l, mid);
    }
    if(right > mid) {
        upd(left, right, arr, val, pos * 2 + 1, mid, r);
    }
    // prop(pos, arr, l, r);
    // prop(pos * 2, arr, l, mid);
    // prop(pos * 2 + 1, arr, mid, r);
    tree[pos][arr].maxval = max(tree[pos*2][arr].maxval, tree[pos * 2 + 1][arr].maxval);
}
int query(int left, int right, int arr, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos, arr, l, r);
    if(left <= l && right >= r) {
        return tree[pos][arr].maxval;
    }
    int maxval = 0;
    int mid = (l + r) / 2;
    if(left < mid) {
        maxval = max(maxval, query(left, right, arr, pos * 2, l, mid));
    }
    if(right > mid) {
        maxval = max(maxval, query(left, right, arr, pos * 2 + 1, mid, r));
    }
    return maxval;
}
signed main() {
    int n, k;
    // cin >> n;
    // k = 2;
    cin >> n >> k;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    vector<int> nextocc(n+1, n);
    vector<int> ans(n);
    for(int i = n-1; i >= 0; i --) {
        ans[i] = nextocc[arr[i]];
        nextocc[arr[i]] = i;
    }
    for(int kval = 1; kval <= k; kval++) {
        for(int i = n-1; i >= 0; i--) {
            upd(i+1, ans[i]+1, kval-1, 1);
            int val = max(query(i+1, i+2, kval), query(i, n+1, kval - 1));
            upd(i, i+1, kval, val);
        }
    }
    cout<<query(0, 1, k)<<'\n';
    return 0;
}
