#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
// #define int long long
using namespace std;
static uint64_t seed =
    chrono::steady_clock::now().time_since_epoch().count();
mt19937 Rand(seed);
struct treap {
    int val;
    int priority;
    int subsum;
    treap * l;
    treap * r;
    void init(int key) {
        val = key;
        priority = Rand();
        subsum = 1;
        l = NULL;
        r = NULL;
    }
    void fix() {
        subsum = 1;
        if (l != NULL) subsum += l->subsum;
        if (r != NULL) subsum += r->subsum;
    }
};
treap * merge(treap * a, treap * b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (a->priority > b->priority) {
        a->r = merge(a->r, b);
        a->fix();
        return a;
    }else {
        b->l = merge(a, b->l);
        b->fix();
        return b;
    }
}
pair<treap *, treap *> split(treap * a, int subsum) {
    if (subsum == 0) return {NULL, a};
    if (a == NULL) return {NULL, NULL};
    int leftsum = 0;
    if (a -> l != NULL) leftsum = a->l->subsum;
    if (leftsum >= subsum) {
        pair<treap *, treap *> b = split(a->l, subsum);
        a->l = b.second;
        a->fix();
        return {b.first, a};
    }else {
        pair<treap *, treap *> b= split(a->r, subsum - leftsum - 1);
        a->r = b.first;
        a->fix();
        return {a, b.second};
    }
}
#define MAXN 1000005
treap treaparr[MAXN];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    treap * tree = NULL;
    for (int i = 0; i < n; i++) {
        treap * a = &treaparr[i];
        a->init(i);
        tree = merge(tree, a);
    }
    vector<int> arr(n, -1);
    // set<int> s;
    // for (int i = 0; i < n; i++) s.insert(i);
    bitset<MAXN> bit;
    for (int i = 0; i < n; i++) bit[i] = 1;
    for (int i = 0; i < m; i++) {
        int pos, val;
        cin >> val >> pos;
        pos--, val--;
        pair<treap *, treap *> a = split(tree, pos);
        pair<treap *, treap *> b = split(a.second, 1);
        if (arr[b.first->val] == -1) {
            if (bit[val] == 1) {
                arr[b.first->val] = val;
                bit[val] = 0;
            }else {
                cout<<-1<<'\n';
                return 0;
            }
        }else if (arr[b.first->val] != val) {
            cout<<-1<<'\n';
            return 0;
        }
        tree = merge(b.first, a.first);
        tree = merge(tree, b.second);
    }
    // for (int i : arr) s.erase(i);
    int p = 0;
    for (int i : arr) {
        if (i == -1) {
            while (bit[p] == 0) p++;
            cout<<p+1<<' ';
            bit[p] = 0;
        }else {
            cout<<i + 1<<' ';
        }
    }
    cout<<'\n';
}
