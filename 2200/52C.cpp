#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int lazyadd;
    int minval;
};
node tree[800055];
void prop(int pos, int l, int r) {
    tree[pos].minval += tree[pos].lazyadd;
    if(l + 1 != r) {
        tree[pos * 2].lazyadd += tree[pos].lazyadd;
        tree[pos * 2 + 1].lazyadd += tree[pos].lazyadd;
    }
    tree[pos].lazyadd = 0;
}
void update(int left, int right, int val, int pos = 1, int l = 0, int r = 200005) {
    prop(pos, l, r);
    if(left <= l && right >= r) {
        tree[pos].lazyadd += val;
        return;
    }
    int mid = (l+r) /2;
    if(left<  mid) {
        update(left, right, val, pos * 2, l, mid);
    }
    if(right > mid) {
        update(left, right, val, pos * 2 + 1, mid, r);
    }
    prop(pos, l, r); prop(pos*2, l, mid); prop(pos*2+1, mid, r);
    tree[pos].minval = min(tree[pos * 2].minval, tree[pos * 2 + 1].minval);
}
int query(int left, int right, int pos = 1, int l = 0, int r = 200005) {
    prop(pos, l, r);
    if(left <= l && right >= r) {
        return tree[pos].minval;
    }
    int minval = LONG_LONG_MAX;
    int mid = (l +r ) / 2;
    if(left < mid) {
        minval = min(minval, query(left, right, pos * 2, l, mid));
    }
    if(right > mid) {
        minval = min(minval, query(left, right, pos * 2 + 1, mid, r));
    }
    return minval;
}
signed main() {
    int n, m;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        update(i, i+1, a);
    }
    cin >> m;
    string str;
    getline(cin, str);
    for(int i = 0; i < m; i++) {
        string s;
        getline(cin, s);
        vector<int> inputs;
        bool negative = false;
        int total = 0;
        for(char j : s) {
            if(j == ' ' || j == '\n') {
                if(negative) total = -total;
                inputs.push_back( total);
                total = 0;
                negative = false;
            }else if(j == '-') {
                negative = true;
            }else {
                total *= 10;
                total += j - '0';
            }
        }
        if(negative) total = -total;
        inputs.push_back( total);
        if(inputs.size() == 2) {
            if(inputs[1] < inputs[0]) {
                cout<<min(query(inputs[0], n), query(0, inputs[1] + 1))<<'\n';;
            }else {
                cout<<query(inputs[0], inputs[1]+1)<<'\n';
            }
        }else {
            if(inputs[1] < inputs[0]) {
                update(inputs[0], n, inputs[2]);
                update(0, inputs[1] + 1, inputs[2]);
            }else {
                update(inputs[0], inputs[1] + 1, inputs[2]);
            }
        }
    }
    return 0;
}
