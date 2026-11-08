#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    multiset<int> s;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s.insert(a);
    }
    int lowest = *s.begin();
    int numlow = 0;
    while(!s.empty() && *s.begin() == lowest) {
        numlow++;
        s.erase(s.begin());
    }
    if(s.empty()) {
        cout<<0<<'\n';
        return 0;
    }
    int highest = *prev(s.end());
    int numh = 0;
    while(!s.empty() && *prev(s.end()) == highest) {
        numh++;
        s.erase(prev(s.end()));
    }
    while(true) {
        if(lowest == highest) {
            cout<<0<<'\n';
            return 0;
        }
        if(numlow < numh) {
            int low = highest;
            if(!s.empty()) low = *s.begin();
            int dif = abs(lowest - low);
            if(dif * numlow <= k) {
                k -= dif * numlow;
                lowest += dif;
                while(!s.empty() && *s.begin() == low) {
                    numlow ++;
                    s.erase(s.begin());
                }
            }else {
                int len = k / numlow;
                lowest += len;
                cout<<highest - lowest<<'\n';
                return 0;
            }
        }else {
            int high = lowest;
            if(!s.empty()) high = *prev(s.end());
            int dif = abs(highest - high);
            if(dif * numh <= k) {
                k -= dif * numh;
                highest -= dif;
                while(!s.empty() && *prev(s.end()) == high) {
                    numh ++;
                    s.erase(prev(s.end()));
                }
            }else {
                int len = k / numh;
                highest -= len;
                cout<<highest - lowest<<'\n';
                return 0;
            }
        }
    }
    return 0;
}
