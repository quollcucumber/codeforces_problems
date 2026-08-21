#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 300005;
pair<int, int> tree[MAXN * 2];
pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
     if(a.first > b.first) return a;
     return b;
}
void upd(int pos, int val) {
     pos += MAXN;
     tree[pos] = {val, pos - MAXN};
     pos /= 2;
     while (pos != 0) {
          tree[pos] = merge(tree[pos * 2], tree[pos * 2 + 1]);
          pos /= 2;
     }
}
pair<int, int> query(int left, int right) {
     left += MAXN;
     right += MAXN;
     pair<int, int> maxval = {-1, -1};
     while (left < right) {
          if (left & 1) maxval = merge(maxval, tree[left++]);
          if (right & 1) maxval = merge(maxval, tree[--right]);
          left /= 2;
          right /= 2;
     }
     return maxval;
}
signed main() {
     int n, d;
     cin >> n >> d;
     set<int> points;
     vector<int> arr(n);
     for (int i = 0; i < n; i++) {
          cin >> arr[i];
          points.insert(arr[i]);
          points.insert(arr[i] + d);
          points.insert(arr[i] - d);
     }
     unordered_map<int, int> point;
     unordered_map<int, int> backpoint;
     int pos = 1;
     for (int i : points) {
          backpoint[pos] = i;
          point[i] = pos++;
     }
     for(int i = 0; i < MAXN; i++) upd(i, -2);
     vector<int> nextarr(n);
     unordered_map<int, int> position;
     pair<int, int> maxval = {-1, -1};
     for (int i = n-1; i >= 0; i--) {
          pair<int, int> a = merge(query(point[arr[i] + d], MAXN),query(0, point[arr[i] - d] + 1));
          int val = 1 + a.first;
          if(a.second == -1) nextarr[i] = -1;
          else nextarr[i] = position[backpoint[a.second]];
          upd(point[arr[i]], val);
          position[arr[i]] = i;
          maxval = merge(maxval, {val, i});
     }
     vector<int> path;
     int node = maxval.second;
     while(node != -1) {
          path.push_back(node);
          node = nextarr[node];
     }
     cout<<path.size()<<'\n';
     for(int i : path) {
          cout<<i + 1<<' ';
     }
     cout<<'\n';
}
