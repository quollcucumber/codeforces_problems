#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
#define int long long
using namespace std;

signed main() {
    int n, k, x;
    cin >> n >> k >> x;
    if (n / k > x) {
        cout<<-1<<'\n';
        return 0;
    }
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    vector<int> score(n+1, LONG_LONG_MIN/4); score[n] = 0;
    for (int i = x-1; i >= 0; i--) {
        vector<int> newscore(n+1);
        deque<pair<int, int>> de;
        for (int j = n-1; j >= 0; j --) {
            int l = j + 1, r = min(n, j + k);
            int pos = n; if (!de.empty()) pos = de[0].second-1;
            while (pos >= l) {
                while (!de.empty() && de[0].first < score[pos]) {
                    de.pop_front();
                }
                de.push_front({score[pos], pos});
                pos--;
            }
            while (!de.empty() && de[de.size()-1].second > r) {
                de.pop_back();
            }
            newscore[j] = de[de.size()-1].first + arr[j];
        }
        newscore[n] = LONG_LONG_MIN/4;
        score = newscore;
    }
    int maxval = LONG_LONG_MIN;
    for (int i = 0; i < k; i++) {
        maxval = max(maxval, score[i]);
    }
    cout<<maxval<<'\n';
}
