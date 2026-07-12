    #include <bits/stdc++.h>
    #define int long long
    using namespace std;
    struct node {
        bitset<61> a;
        bool set = false;
        int setval = 0;
    };
    const int MAXN = 400005;
    node tree[MAXN * 4];
    void prop(int node, int l, int r){
        if(tree[node].set){
            tree[node].a = bitset<61>(0);
            tree[node].a[tree[node].setval] = true;
            if (l + 1 != r) {
                tree[node * 2].set = true;
                tree[node * 2].setval = tree[node].setval;
                tree[node * 2 + 1].set = true;
                tree[node * 2 + 1].setval = tree[node].setval;
            }
            tree[node].set = false;
        }
     
    }
    void upd(int left, int right, int setval, int pos = 1, int l = 0, int r = MAXN){
        prop(pos,l , r);
        if(left <= l && right >= r){
            tree[pos].set = true;
            tree[pos].setval = setval;
            return;
        }
        int mid = (l + r) / 2;
        if (left < mid) {
            upd(left, right, setval, pos * 2, l, mid);
        }
        if (right > mid) {
            upd(left, right, setval, pos * 2 + 1, mid, r);
        }
        prop(pos, l, r);
        prop(pos * 2,l , mid);
        prop(pos * 2 + 1, mid, r);
        tree[pos].a = tree[pos * 2].a | tree[pos * 2+1].a;
    }
    bitset<61> query(int left, int right, int pos = 1, int l = 0, int r= MAXN) {
        prop(pos,l, r);
        if (left <= l && right >= r) {
            return tree[pos].a;
        }
        int mid = (l +r ) / 2;
        bitset<61> ans(0);
        if (left < mid) {
            ans = query(left, right, pos * 2, l, mid);
        }
        if (right > mid) {
            ans = ans | query(left, right, pos * 2 + 1, mid, r);
        }
        return ans;
    }
    vector<int> neighbors[MAXN]; // hmmm did I use american spelling
    vector<int> children[MAXN];
    bool seenroot[MAXN];
    void root(int node) {
        seenroot[node] = true;
        for (int i : neighbors[node]) {
            if (!seenroot[i]) {
                children[node].push_back(i);
                root(i);
            }
        }
    }
    int pos = 0;
    pair<int, int> tours[MAXN];
    void tour(int node) {
        int start = pos;
        pos++;
        for (int i : children[node]) tour(i);
        tours[node] = {start, pos}; // inc exc
    }
    signed main() {
        int n, m;
        cin >> n >> m;
        vector<int> colour(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> colour[i];
        }
        for (int i = 0; i < n-1; i++) {
            int a, b;
            cin >> a >> b;
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
        root(1);
        tour(1);
        for (int i = 1; i <= n; i++) {
            upd(tours[i].first, tours[i].first + 1, colour[i]);
        }
        for (int i = 0; i < m; i++) {
            int t;
            cin >> t;
            if (t == 1) {
                int v, c;
                cin >> v >> c;
                upd(tours[v].first, tours[v].second, c);
            }else {
                int v;
                cin >> v;
                cout<<query(tours[v].first, tours[v].second).count()<<'\n';
            }
        }
    }
