#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 300005;
struct node {
    int total;
    int maxval;
    int maxpos;
};
node merge(node a, node b) {
    node newnode;
    newnode.total = a.total + b.total;
    if(a.maxval > b.maxval) {
        newnode.maxval = a.maxval;
        newnode.maxpos = a.maxpos;
    }else  {
        newnode.maxval = b.maxval;
        newnode.maxpos = b.maxpos;
    }
    return newnode;
}
node tree[MAXN * 2];
node query(int left, int right) {
    node total ={0, 0, 0};
    left += MAXN;
    right += MAXN;
    while(left < right) {
        if(left & 1) total =merge(total, tree[left++]);
        if(right & 1) total = merge(total,  tree[--right]);
        left/=2;
        right /=2;
    }
    return total;
}
void upd(int pos, int val) {
    pos += MAXN;
    tree[pos]= {val, val, pos - MAXN};
    pos /= 2;
    while(pos > 0) {
        tree[pos] = merge(tree[pos * 2],tree[pos * 2 + 1]);
        pos /= 2;
    }
}
int ans[1000005];
int d(int n) {
    return ans[n];
}
signed main() {
    for(int i = 1; i < 1000005; i++) {
        for(int j = i; j < 1000005; j += i) {
            ans[j]++;
        }
    }
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        upd(i, a);
    }
    for(int i = 0; i < m; i++) {
        int type, l, r;
        cin >> type >> l >> r;
        if(type == 1) {
            queue<pair<int, int>> vals;
            vals.push({l-1, r-1});
            while(!vals.empty()) {
                pair<int, int> range = vals.front();
                vals.pop();
                node a = query(range.first, range.second+1);
                if(a.maxval > 2) {
                    upd(a.maxpos, d(a.maxval));
                    if(a.maxpos != range.first) {
                        vals.push({range.first, a.maxpos- 1});
                    }
                    if(a.maxpos != range.second) {
                        vals.push({a.maxpos + 1, range.second});
                    }
                }
            }
        }else {
            cout<<query(l-1, r).total<<'\n';
        }
    }
    return 0;
}
