#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 200005;
int p[MAXN];
int dsu(int node) {
     if(p[node] == node) return node;
     return p[node] = dsu(p[node]);
}
vector<int> neighbors[MAXN];
vector<int> children[MAXN];
bool seenroot[MAXN];
int parent[MAXN];
int subsum[MAXN];
int root(int node) {
     subsum[node] = 1;
     seenroot[node] = true;
     for(int i : neighbors[node]) {
          if(!seenroot[i]) {
               children[node].push_back(i);
               parent[i] = node;
               subsum[node] += root(i);
          }
     }
     return subsum[node];
}
void solve() {
     int n;
     cin >> n;
     for(int i = 0; i <= n; i++) {
          p[i] = i;
          seenroot[i] = false;
          children[i].clear();
          neighbors[i].clear();
     }
     pair<int, int> THE_EDGE; // I would put it in bold, except my ide sadly doesn't support this. The emphasis is that this is the ONE SPECIAL EDGE AND NO OTHER EDGE IS SPECIAL and I am NOT procrastonating implementation!
     for(int i = 0; i < n; i++) {
          int a, b;
          cin >> a>> b;
          if(dsu(a) == dsu(b)) {
               THE_EDGE = {a, b};
          }else {
               neighbors[a].push_back(b);
               neighbors[b].push_back(a);
               p[dsu(a)] = dsu(b);
          }
     }
     root(THE_EDGE.first);
     vector<int> cycle;
     while(THE_EDGE.second != THE_EDGE.first) {
          cycle.push_back(THE_EDGE.second);
          THE_EDGE.second = parent[THE_EDGE.second];
     }
     cycle.push_back(THE_EDGE.first);
     int total = 2 * n * (n-1) / 2;
     int prev = -1;
     for(int i : cycle) {
          int numsub = 0;
          for(int j : children[i]) {
               if(j != prev) {
                    numsub += subsum[j];
                    // numnotalkeachother += subsum[j];
               }
          }
          total -= numsub * (numsub + 1) / 2;
          prev = i;
     }
     // total -= numnotalkeachother * (numnotalkeachother - 1) / 2;
     cout<<total<<'\n';
}
signed main() {
     int t;
     cin >> t;
     while(t--) {
          solve();
     }
     return 0;
}
