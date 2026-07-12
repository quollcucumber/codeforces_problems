    #include <bits/stdc++.h>
    #define int long long
    using namespace std;
     
    signed main() {
        int n;
        cin >> n;
        multiset<pair<int, int>> s;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];
        int total = 0;
        for (int i = n-1; i >= 0; i--) {
            while (!s.empty() && s.rbegin()->second == 0) s.erase(*s.rbegin());
            if (!s.empty() && s.rbegin()->first > arr[i]) {
                total  += s.rbegin()->first - arr[i];
                if (s.rbegin()->second == 1) {
                    s.erase(s.find(*s.rbegin()));
                }else {
                    int val = s.rbegin()->first;
                    s.erase(s.find(*s.rbegin()));
                    s.insert({val, 1});
                }
                s.insert({arr[i], 2});
            }else {
                s.insert({arr[i], 1});
            }
        }
        cout<<total<<'\n';
    }
