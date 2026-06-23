#include <bits/stdc++.h>
using namespace std;
bool seen[505][505];

int main(){
    int r, c;
    cin >>r >> c;
    char arr[r][c];
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> arr[i][j];
        }
    }
    int a, b, cq, d;
    cin >> a >> b>> cq >> d;
    a--;
    b--;
    cq--;
    d--;
    pair<int, int> s= {a, b};
    pair<int, int> e = {cq, d};
    if(s==e) {
        if((s.first != 0 && arr[s.first-1][s.second] == '.') || (s.second != 0 && arr[s.first][s.second-1] == '.') || (s.first != r-1 && arr[s.first+1][s.second] == '.') || (s.second != c-1 && arr[s.first][s.second+1] == '.')) cout<<"YES\n";
        else cout<<"NO\n";
        return 0;
    }
    if(abs(s.first - e.first) + abs(s.second - e.second) == 1) {
        if(arr[e.first][e.second] == 'X' || (e.first != 0 && arr[e.first-1][e.second] == '.') || (e.second != 0 && arr[e.first][e.second-1] == '.') || (e.first != r-1 && arr[e.first+1][e.second] == '.') || (e.second != c-1 && arr[e.first][e.second+1] == '.')) cout<<"YES\n";
        else cout<<"NO\n";
        return 0;
    }
    queue<pair<int, int>> q;
    q.push({a, b});
    while(!q.empty()){
//        seen[q.front().first][q.front().second] = true;
        if(q.front().first != r - 1 &&!seen[q.front().first + 1][q.front().second]&&arr[q.front().first + 1][q.front().second] == '.'){
            q.push({q.front().first + 1, q.front().second});
            seen[q.front().first + 1][q.front().second] = true;
        }
        if(q.front().second != c - 1 &&!seen[q.front().first][q.front().second+1]&&arr[q.front().first][q.front().second+1] == '.'){
            q.push({q.front().first, q.front().second+1});
            seen[q.front().first][q.front().second+1] = true;
        }
        if(q.front().first != 0 &&!seen[q.front().first - 1][q.front().second]&&arr[q.front().first - 1][q.front().second] == '.'){
            q.push({q.front().first - 1, q.front().second});
            seen[q.front().first - 1][q.front().second] = true;
        }
        if(q.front().second != 0 &&!seen[q.front().first][q.front().second-1]&&arr[q.front().first ][q.front().second-1] == '.'){
            q.push({q.front().first , q.front().second-1});
            seen[q.front().first][q.front().second-1] = true;
        }
        q.pop();
    }
    int around = 0;
    if(cq != 0){ // cq = y
        around += (arr[cq-1][d]=='.');
    }
    if(d != 0){ // cq = y
        around += (arr[cq][d-1]=='.');
    }
    if(cq != r-1){ // cq = y
        around += (arr[cq+1][d]=='.');
    }
    if(d != c-1){ // cq = y
        around += (arr[cq][d+1]=='.');
    }
    if(arr[cq][d] == 'X') {
        if(cq != 0 && seen[cq-1][d]){ // cq = y
            cout<<"YES\n";
            return 0;
        }
        if(d != 0 && seen[cq][d-1]){ // cq = y
            cout<<"YES\n";
            return 0;
        }
        if(cq != r-1&&seen[cq+1][d]){ // cq = y
            cout<<"YES\n";
            return 0;
        }
        if(d != c-1&&seen[cq][d+1]){ // cq = y
            cout<<"YES\n";
            return 0;
        }
        cout<<"NO\n";
    }else{
        if (around > 1 && seen[cq][d]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
