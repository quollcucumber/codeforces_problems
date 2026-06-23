#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n>> m;
    string arr[n][m];
    map<string, pair<int, int>> pos;
    for(int i = 0; i< n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> arr[i][j];
            pos[arr[i][j]] = {i, j};
        }
    }
    bool carrying = false;
    string carryer = "67 liu qi";
    int q;
    cin >> q;
    int rscore = 0, bscore = 0;
    bool bludger = pos.contains(".B");
    for(int i = 0; i < q; i++) {
        string entity;
        cin >> entity;
        char action;
        cin >> action;
        if(action == 'D') {
            pos[entity].first ++;
        }else if(action == 'U') {
            pos[entity].first--;
        }else if(action == 'L') {
            pos[entity].second--;
        }else if(action == 'R') {
            pos[entity].second++;
        }else if(action == 'C') {
            string catchthing;
            cin >> catchthing;
            if(catchthing == ".S") {
                if(entity[0] == 'R') {
                    cout<<i<<' '<<"RED CATCH GOLDEN SNITCH"<<'\n';
                    cout<<"FINAL SCORE: "<<rscore + 10<<' '<<bscore<<'\n';
                    return 0;
                }else {
                    cout<<i<<' '<<"BLUE CATCH GOLDEN SNITCH"<<'\n';
                    cout<<"FINAL SCORE: "<<rscore<<' '<<bscore + 10<<'\n';
                    return 0;
                }
            }else if(catchthing == ".Q") {
                carrying = true;
                carryer = entity;
            }else {
                assert(1==2);
            }
        }else if(action == 'T') {
            if(arr[pos[entity].first][pos[entity].second] == "BG") {
                cout<<i<<' '<<"RED GOAL\n";
                rscore++;
                carrying = false;
                pos[".Q"] = {(n + 1) / 2, (m + 1) / 2};
            }else if(arr[pos[entity].first][pos[entity].second] == "RG") {
                cout<<i<<" BLUE GOAL\n";
                bscore++;
                carrying = false;
                pos[".Q"] = {(n + 1) / 2, (m + 1) / 2};
            }else {
                pos[".Q"] = pos[carryer];
                carrying = false;
            }
        }else {
            assert(1==2);
        }
        if(bludger) {
            if(entity == ".B") {
                for(pair<string, pair<int, int>> j : pos) {
                    if(pos[".B"] == j.second && (j.first[0] == 'B' || j.first[0] == 'R')) {
                        cout<<i <<' '<<j.first << " ELIMINATED\n";
                    }
                }
            }else {
                if((entity[0] == 'B' || entity[0] == 'R')) {
                    if(pos[entity] == pos[".B"]) {
                        cout<<i << ' '<< entity <<' '<<"ELIMINATED\n";
                    }
                }
            }
        }
    }
    cout<<"FINAL SCORE: "<<rscore<<' '<<bscore<<'\n';
    return 0;
}
