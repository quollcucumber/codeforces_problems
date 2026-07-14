// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
// #define int long long
using namespace std;
const int MAXN = 1e6 + 5;
int ans[MAXN];
bool seenroot[MAXN];
vector<int> neighbours[MAXN];
vector<int> children[MAXN];
void root(int node) {
    seenroot[node] = true;
    for(int i : neighbours[node]) {
        if(!seenroot[i]) {
            children[node].push_back(i);
            root(i);
        }
    }
}
pair<int, vector<int>> arr[MAXN];
pair<int, vector<int>> * dp(int node) {
    arr[node].first = 0;
    arr[node].second.push_back(1);
    pair<int, vector<int>> * ret = &arr[node];
    for(int child : children[node]) {
        pair<int, vector<int>> * a = dp(child);
        a->second.push_back(0);
        if(a->second.size() > ret->second.size()) {
            int maxindex = a->first;
            int maxval = a->second[maxindex];
            for(int i = ret->second.size()-1; i >= 0; i--) {
                a->second[a->second.size()  + i - ret->second.size()] += ret->second[i];
                if(a->second[a->second.size()  + i - ret->second.size()] > maxval || (a->second[a->second.size()  + i - ret->second.size()] == maxval && maxindex < a->second.size()  + i - ret->second.size())) {
                    maxval = a->second[a->second.size()  + i - ret->second.size()];
                    maxindex = a->second.size()  + i - ret->second.size();
                }
            }
            ret = a;
            ret->first = maxindex;
        }else {
            int maxindex = ret->first;
            int maxval = ret->second[maxindex];
            for(int i = a->second.size()-1; i>=0;i--) {
                ret->second[ret->second.size() - a->second.size() + i] += a->second[i];
                if(ret->second[ret->second.size() - a->second.size() + i] > maxval || (ret->second[ret->second.size() - a->second.size() + i] == maxval && maxindex < ret->second.size() - a->second.size() + i)) {
                    maxval = ret->second[ret->second.size() - a->second.size() + i];
                    maxindex = ret->second.size() - a->second.size() + i;
                }
            }
            ret->first = maxindex;
        }
    }
    ans[node] =ret->second.size() - 1 - ret->first;
    return ret;
}
signed main() {
    int n;
    cin >> n;
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        neighbours[a].push_back(b);
        neighbours[b].push_back(a);
    }
    root(1);
    dp(1);
    for(int i = 1; i <= n; i++) {
        cout<<ans[i]<<'\n';
    }
}
