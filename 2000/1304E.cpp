#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> neighbors[100005];
vector<int> children[100005];
int jmp[100005][20];
bool seenroot[100005];
int depth[100005];
void root(int node, int d) {
     depth[node] = d;
     seenroot[node] = true;
     for(int i : neighbors[node]) {
          if(!seenroot[i]) {
               children[node].push_back(i);
               jmp[i][0] = node;
               root(i, d + 1);
          }
     }
}
int n;
void calc() {
     for(int i = 1; i < 20; i++) {
          for(int j = 0; j <= n; j++) {
               jmp[j][i] = jmp[jmp[j][i-1]][i-1];
          }
     }
}
int jump(int a, int dist) {
     for(int i = 19; i >= 0; i--) {
          if(dist >= (1<<i)) {
               dist -= (1<<i);
               a = jmp[a][i];
          }
     }
     return a;
}
int lca(int a, int b) {
     if(depth[a] > depth[b]) a = jump(a, abs(depth[b] - depth[a]));
     if(depth[a] < depth[b]) b = jump(b, abs(depth[b] - depth[a]));
     if(a == b) return a;
     for(int i = 19; i >= 0; i--) {
          if(jmp[a][i] != jmp[b][i]) {
               a = jmp[a][i];
               b = jmp[b][i];
          }
     }
     return jmp[b][0];
}

int len(int a, int b) {
     int lcanode = lca(a, b);
     return abs(depth[lcanode] - depth[a]) + abs(depth[lcanode] - depth[b]);
}
signed main() {
     cin >> n;
     for(int i = 0; i < n-1; i++) {
          int a, b;
          cin >> a >> b;
          neighbors[a].push_back(b);
          neighbors[b].push_back(a);
     }
     root(1, 0);
     calc();
     int q;
     cin >> q;
     for(int i = 0; i < q; i++) {
          int x, y, a, b, k;
          cin >> x >> y >> a >> b >> k;
          int d1 = len(a, b);
          int d2 = len(a, x) + len(y, b) + 1;
          int d3 = len(a, y) + len(b, x) + 1;
          if((d1 <= k && d1 % 2 == k % 2) || (d2 <= k && d2 % 2 == k % 2) || (d3 <= k && d3 % 2 == k % 2) ) {
               cout<<"YES\n";
          }else {
               cout<<"NO\n";
          }
     }
}
