#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
vector<int> children[200005];
vector<int> neighbors[200005];
bool seenroot[200005];
void root(int node) {
    seenroot[node] = true;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            children[node].push_back(i);
            root(i);
        }
    }
}
int subsize[200005];
pair<int, int> calcsum(int node) {
    int subsum = 1;
    int total = 1;
    for(int i :children[node]) {
        pair<int, int> a = calcsum(i);
        subsum += a.first;
        total += a.second + a.first;
    }
    subsize[node] = subsum;
    return {subsum, total};
}
int maxval = 0;
int n;
void dp(int node, int total) {
    maxval = max(maxval, total);
    for(int i : children[node]) {
        int val = total;
        val -= subsize[i];
        val += n - subsize[i];
        dp(i, val);
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a>> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    root(1);
    dp(1, calcsum(1).second);
    cout<<maxval<<'\n';
}
