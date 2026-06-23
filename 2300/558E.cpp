#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
using namespace std;
struct node {
    vector<int> chars;
    bool set;
    int setchar;
};
const int MAXN = 100005;
node tree[MAXN * 4];
void prop(int node, int l, int r) {
    if(tree[node].set) {
        if(l + 1 != r) {
            tree[node * 2].set = true;
            tree[node * 2].setchar = tree[node].setchar;
            tree[node * 2 + 1].set = true;
            tree[node * 2 + 1].setchar = tree[node].setchar;
        }
        for(int i = 0; i < 26; i++) tree[node].chars[i] = 0;
        tree[node].chars[tree[node].setchar] = (r - l);
        tree[node].set = false;
    }
}
void merge( vector<int> * ans, vector<int>  * a, vector<int> * b) {
    for(int i = 0; i < 26; i++) {
        (*ans)[i] = (*a)[i] + (*b)[i];
    }
}
vector<int> query(int left, int right, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos,l,r);
    if(left <= l && right >= r) {
        return tree[pos].chars;
    }
    int mid = (l + r) / 2;
    vector<int> ans;
    // for(int i = 0; i < 26;i++) ans[i] = 0;
    if(left < mid) {
        ans = query(left, right, pos  * 2, l, mid);
    }
    if(right > mid) {
        if(ans.size() == 0) ans = query(left, right, pos * 2 + 1, mid, r);
        else {
            vector<int> a = query(left, right, pos * 2 + 1, mid, r);
            merge(&ans, &ans, &a);
        }
    }
    return ans;
}
void upd(int left, int right, int val, int pos = 1, int l = 0, int r = MAXN) {
    if(left <= l && right >= r) {
        tree[pos].set = true;
        tree[pos].setchar = val;
        // prop(pos,l,r);
        return;
    }
    prop(pos,l,r);
    int mid = (l + r) / 2;
    if(left < mid) {
        upd(left, right, val, pos  * 2, l, mid);
    }
    if(right > mid) {
        upd(left, right, val, pos * 2 + 1, mid, r);
    }
    prop(pos,l,r);
    prop(pos * 2, l, mid);
    prop(pos * 2 + 1, mid, r);
    merge(&tree[pos].chars, &tree[pos * 2].chars, &tree[pos * 2 + 1].chars);
}
// void mergetree(int left, int right, int pos = 1, int l = 0, int r = MAXN) {
//     if(l + 1 == r) {
//         //do nothing :67:
//         prop(pos,l,r);
//         return;
//     }
//     prop(pos,l,r);
//     int mid = (l + r) / 2;
//     if(left < mid) {
//         mergetree(left, right, pos  * 2, l, mid);
//     }
//     if(right > mid) {
//         mergetree(left, right, pos * 2 + 1, mid, r);
//     }
//     prop(pos,l,r);
//     prop(pos * 2, l, mid);
//     prop(pos * 2 + 1, mid, r);
//     tree[pos].chars = merge(tree[pos * 2].chars, tree[pos * 2 + 1].chars);
// }
signed main() {
    for(int i = 0; i < 4 * MAXN; i++) {
        tree[i].chars.resize(26);
    }
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for(int i = 0; i < n; i++) {
        upd(i, i+1, s[i] - 'a');
    }
    for(int i = 0; i <q ; i ++) {
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        r--;
        vector<int> chars = query(l, r + 1);
        if(k == 0) {
            int pos = l;
            for(int j = 25; j >= 0; j--) {
                if(chars[j] != 0) {
                    upd(pos, pos + chars[j], j);
                    pos += chars[j];
                }
            }
        }else {
            int pos = l;
            for(int j = 0; j < 26; j++) {
                if(chars[j] != 0) {
                    upd(pos, pos + chars[j], j);
                    pos += chars[j];
                }
            }
        }
        // mergetree(l, r + 1);
    }
    for(int i = 0; i < n; i++) {
        vector<int> a = query(i, i + 1);
        for(int j = 0; j < 26; j++) {
            if(a[j] != 0) {
                cout<<(char) (j + 'a');
            }
        }
    }
    cout<<'\n';
    return 0;
}
