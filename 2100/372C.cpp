#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m, d;
    cin >> n >> m >> d;
    vector<int> score(n, 0);
    vector<pair<int, pair<int, int>>> v;
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--;
        v.push_back({t,{a, b}});
    }
    sort(v.begin(),v.end());
    v.push_back({v[v.size()-1].first + 1, {67,67}});
    for (int i = m-1; i >= 0; i--) {
        deque<pair<int, int>> de;
        vector<int> newscore(n);
        for (int j = 0; j < n; j++) {
            int l = max(0ll, j - d * (v[i+1].first - v[i].first));
            int r = min(n-1, j + d * (v[i+1].first - v[i].first));
            while (de.empty() || de[de.size()-1].second < r) {
                int pos = 0;
                if (!de.empty()) pos = de[de.size()-1].second + 1;
                while (!de.empty() && de[de.size()-1].first < score[pos]) {
                    de.pop_back();
                }
                de.push_back({score[pos], pos});
            }
            while (!de.empty() && de[0].second < l) {
                de.pop_front();
            }
            newscore[j] = de[0].first + (v[i].second.second - abs(v[i].second.first - j));
        }
        score = newscore;
    }
    int maxval = LONG_LONG_MIN;
    for (int i = 0; i < n; i++) maxval = max(maxval, score[i]);
    cout<<maxval<<'\n';
}
