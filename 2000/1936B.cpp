#include <bits/stdc++.h>
#define int long long
using namespace std;

struct seg {
    int sum, add;
};
seg tree[4000055];
void prop(int pos, int l, int r) {
    tree[pos].sum += (r - l) * tree[pos].add;
    if(l + 1 != r) {
        tree[pos * 2].add += tree[pos].add;
        tree[pos* 2 + 1].add += tree[pos].add;
    }
    tree[pos].add = 0;
}
int query(int left, int right, int pos = 1, int l = 0, int r = 1000001) {
    prop(pos, l, r);
    if(l >=left && right >= r) {
        return tree[pos].sum;
    }
    int mid = (l + r) /2;
    int total = 0;
    if(left < mid) {
        total +=  query(left, right, pos * 2, l, mid);
    }
    if(right > mid){
        total += query(left, right, pos * 2 + 1, mid, r);
    }
    return total;
}
void update(int left, int right, int val, int pos = 1, int l = 0, int r = 1000001) {
    prop(pos, l, r);
    if(left <= l && right >= r) {
        if(val == -1) {
            tree[pos].add = 0;
            tree[pos].sum = 0;
        }else {
            tree[pos].add += val;
            prop(pos, l, r);
        }
        if(val != -1) {
            return;
        }
        if(l + 1 == r) {
            return;
        }
    }
    int mid = (l + r) / 2;
    if(left < mid) {
        update(left, right, val, pos * 2, l, mid);
    }
    if(right > mid) {
        update(left, right, val, pos * 2 + 1, mid, r);
    }
    prop(pos, l, r);
    prop(pos, l, mid);
    prop(pos, mid, r);
    tree[pos].sum = tree[pos * 2 ].sum + tree[pos* 2 + 1].sum;
}

signed main(){
    int t;
    cin >> t;
    for(int test=  0; test < t; test++) {
        // vector<int> ans;
        // mt19937 Rand(random_device{}());
        // for(int test = 0; test < 1; test++) {
        // string s = "RLLRRRLLR";
        // int n = s.size();
        // // int n = Rand() % 10;
        // for(int i = 0; i < n; i++) {
        //     if(Rand() % 2) s += '<';
        //     else s += '>';
        // }
        // for(int i = 0 ; i < n; i++) {
        //     string copy = s;
        //     int pos = i;
        //     int total = 0;
        //     while(pos != -1 && pos != n) {
        //         if(copy[pos] == '<') {
        //             copy[pos] = '>';
        //             pos--;
        //         }else {
        //             copy[pos] = '<';
        //             pos++;
        //         }
        //         total++;
        //     }
        //     ans.push_back(total);
        // }
        // }
        int n;
        cin >> n;
        string s;
        cin >> s;
        int left[n + 1];
        int right[n + 1];
        int total = 0;
        left[0] = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '>') total++;
            left[i+1] = total;
        }
        total = 0;
        right[n] = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(s[i] == '<') total++;
            right[i] = total;
        }
        vector<pair<int, pair<int, int>>> v;
        for(int i = 0; i < n; i++) {
            int numleft = left[i];
            int numright = right[i+1];
            int val = 0;
            int bounceleft = -1;
            int bounceright = -1;
            if(numleft > numright) {
                if(s[i] == '<') {
                    bounceleft = numright+1;
                    bounceright = numright;
                }else {
                    bounceleft = numright;
                    bounceright = numright;
                }
                val = n - i;
                // cout<<"right\n";
            }else if(numleft < numright) {
                if(s[i] == '>') {
                    bounceright = numleft+1;
                    bounceleft = numleft;
                }else {
                    bounceleft = numleft;
                    bounceright = numleft;
                }
                val = i + 1;
                //cout<<left<<'\n';
            }else if(s[i] == '<') {
                bounceleft = numleft;
                bounceright = numright;
                val = i + 1;
                // cout<<left<<'\n';
            }else {
                bounceleft = numleft;
                bounceright = numright;
                val =  n - i;
                // cout<<"right\n";
            }
            v.push_back({val, {bounceleft, bounceright}});
        }
        int lefts = 0;
        for(int i = 0; i < n; i++) {
            // for(int j = 0; j < 10; j++) cout<<query(j, j + 1)<<' ';
            // cout<<'\n';
            if(v[i].second.first != 0) {
                v[i].first += query(lefts - v[i].second.first, lefts);
            }
            if(lefts != 0) {
                update(0, lefts, 2);
            }
            if(s[i] == '>') {
                update(lefts,lefts+1, 2);
                lefts++;
            }
        }
        int rights = 0;
        update(0, n+1, -1);
        for(int i = n-1; i >= 0; i--) {
            // for(int j = 0; j < 10; j++) cout<<query(j, j + 1)<<' ';
            // cout<<'\n';
            if(v[i].second.second != 0) {
                v[i].first += query(rights - v[i].second.second, rights);
            }
            if(rights != 0) {
                update(0, rights, 2);
            }
            if(s[i] == '<') {
                update(rights, rights + 1, 2);
                rights++;
            }
        }
        for(int i = 0; i < n; i ++) {
            // if(ans[i] != v[i].first) {
            // cout<<ans[i]<<' '<<v[i].first<<'\n';
            // cout<<s<<'\n';
            // return 0;
            // }
            cout<<v[i].first<<'\n';
        }
        update(0, n+1, -1);
    }
}
