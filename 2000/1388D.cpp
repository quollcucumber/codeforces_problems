// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;

int n;
vector<int> a, b;
int ans = 0;
vector<int> v;
vector<int> children[200005];
bool done[200005];
int dp(int node) {
     int total = a[node];
     for(int i : children[node]) total += dp(i);
     if(total >= 0) v.push_back(node);
     ans += max(0ll, total);
     done[node] = total >= 0;
     a[node] = total;
     return max(0ll, total);
}
void fix(int node) {
     int total = a[node];
     if(total < 0) v.push_back(node), ans += total;
     for(int i : children[node]) fix(i);
}
signed main() {
     ios_base::sync_with_stdio(false);
     cin.tie(nullptr);
     cin >> n;
     a.resize(n);
     b.resize(n);
     for(int i = 0; i < 2 *n; i++) cin >> (i < n ? a[i] : b[i - n]);
     for(int i = 0; i < n; i++) if(b[i] != -1) children[b[i]-1].push_back(i);
     for(int i = 0; i < n; i++) if(b[i] == -1) dp(i);
     for(int i = 0; i < n; i++) if(b[i] == -1) fix(i);
     cout<<ans<<'\n';
     for(int i : v) cout<<i + 1<<' ';
     cout<<'\n';
     return 0;
}
