#include <bits/stdc++.h>
#define int long long
using namespace std;
map<int, int> * a[100005];
vector<int> children[100005];
pair<int, int> ans[100005];
pair<map<int, int> * , pair<int, int>> merge(map<int, int> * a, map<int, int> * b, pair<int, int> maxa, pair<int, int> maxb) {
   if(a->size() > b->size()) {
      pair<int, int> maxval = maxa;
      for(pair<int, int> i : (*b)) {
         (*a)[i.first] += i.second;
         if((*a)[i.first] > maxval.first) {
            maxval.first = (*a)[i.first];
            maxval.second = i.first;
         }else if((*a)[i.first] == maxval.first) {
            maxval.second += i.first;
         }
      }
      // b = a;
      return {a, maxval};
   }else {
      pair<int, int> maxval = maxb;
      for(pair<int, int> i : (*a)) {
         (*b)[i.first] += i.second;
         if((*b)[i.first] > maxval.first) {
            maxval.first = (*b)[i.first];
            maxval.second = i.first;
         }else if((*b)[i.first] == maxval.first) {
            maxval.second += i.first;
         }
      }
      // a = b;
      return {b, maxval};
   }
}
int n;
int colour[100005];
bool seen[100005];
vector<int> neighbors[100005];
void root(int node) {
   seen[node] = true;
   for(int i : neighbors[node]) {
      if(!seen[i]) {
         children[node].push_back(i);
         root(i);
      }
   }
}
map<int, int> arr[100005];
int pos = 0;
void dp(int node) {
   int loc = pos++;
   arr[loc][colour[node]] = 1;
   pair<int, int> maxval = {1, colour[node]};
   auto pos = &arr[loc];
   for(int i : children[node]) {
      dp(i);
      pair<map<int, int> *, pair<int, int>> z =  merge(a[i], pos,  ans[i], maxval);
      maxval = z.second;
      pos = z.first;
   }
   ans[node] = maxval;
   a[node] = pos;
}
signed main() {
   cin >> n;
   for(int i = 1; i <= n ;i++) {
      cin >> colour[i];
   }
   for(int i = 0; i < n-1; i++) {
      int a, b;
      cin >> a>> b;
      neighbors[a].push_back(b);
      neighbors[b].push_back(a);
   }
   root(1);
   dp(1);
   for(int i = 1; i <= n; i++) {
      cout<<ans[i].second<<' ';
   }
   cout<<'\n';
   return 0;
}
