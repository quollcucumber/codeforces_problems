#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
char arr[100005];
vector<int> children[100005];
bool seenroot[100005];
vector<int> neighbors[100005];
void root(int node) {
    seenroot[node] = true;
    for(int i : neighbors[node]) {
        if(!seenroot[i]) {
            children[node].push_back(i);
            root(i);
        }
    }
}
void a(int node){
    for(int i : children[node]) {
        neighbors[node].push_back(i);
        neighbors[i].push_back(node);
        a(i);
    }
}
int subsize(int node) {
    int t = 1;
    for(int i : children[node]) t += subsize(i);
    return t;
}
void clear(int node) {
    seenroot[node] = false;
    for(int i : children[node]) clear(i);
    children[node].clear();
}
void clearnei(int node) {
    for(int i : children[node]) clearnei(i);
    neighbors[node].clear();
}
int centroids;
int n;
int centdp(int node, int sz) {
    int size = 1;
    bool iscent = true;
    for(int i : children[node]) {
        int a = centdp(i, sz);
        if(a > sz/2) iscent = false;
        size += a;
    }
    if(sz - size > sz/2) iscent = false;
    if(iscent) centroids = (node);
    return size;
}
void dp(int node, int letter) {
    clearnei(node);
    a(node);
    int sz = subsize(node);
    centdp(node, sz);
    int rootnode = centroids;
    clear(node);
    root(rootnode);
    arr[rootnode] = (char) ('A' + letter);
    for(int i : children[rootnode]) {
        dp(i, letter + 1);
    }
}
// int sz[100005];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    root(1);
    dp(1, 0);
    for(int i = 1; i <= n; i++) {
        cout<<arr[i]<<' ';
    }
    cout<<'\n';
}
