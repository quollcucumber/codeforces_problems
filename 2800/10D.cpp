#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;
int n, m;
vector<int> a;
vector<int> b;

signed main() {
	cin >> n; a.resize(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	cin >> m; b.resize(m);
	for(int i = 0; i < m; i++) cin >> b[i];
	vector<int> dp(m);
	// vector<int> parent(m, -1);
	vector<pair<int, int>> nodes;
	vector<int> pos(m, -1);
	for(int i = 0; i < n; i++) {
		int maxbefore = 0;
		int lastindex = -1;
		for(int j = 0; j < m; j++) {
			if(a[i] == b[j]) {
				if(maxbefore + 1 > dp[j]) {
					dp[j] = maxbefore + 1;
					nodes.push_back({j, lastindex});
					pos[j] = nodes.size()-1;
				}
				// dp[j] = max(dp[j], maxbefore + 1);
			}else if(b[j] < a[i]) {
				if(dp[j] > maxbefore) {
					maxbefore = dp[j];
					lastindex = pos[j];
				}
			}
		}
	}
	int maxpos = 0;
	int maxval = 0;
	for(int i = m-1; i >= 0; i--) {
		if(dp[i] > maxval) {
			maxval = dp[i];
			maxpos = i;
		}
	}
	cout<<maxval<<'\n';
	vector<int> vec;
	maxpos = pos[maxpos];
	for(int i = 0; i < maxval; i ++) {
		vec.push_back(b[nodes[maxpos].first]);
		maxpos = nodes[maxpos].second;
	}
	reverse(vec.begin(), vec.end());
	for(int i : vec) cout<<i<<' ';
	cout<<'\n';
	return 0;
}
