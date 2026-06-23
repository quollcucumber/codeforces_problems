// #pragma optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma target("avx2")
#define int long long
using namespace std;
bool seen[1005][1005][2];
int cached[1005][1005][2];
pair<int, int> arr[1005][1005];
int n;
int dp(int row, int col, bool two) {
    if(seen[row][col][two]) return cached[row][col][two];
    seen[row][col][two] = true;
    if(row == n-1 && col == n-1) return cached[row][col][two] = 0;
    int minval = INT_MAX;
    if(two) {
        if(row != n - 1) minval = min(minval, dp(row + 1, col, two) + arr[row + 1][col].first);
        if(col != n - 1) minval = min(minval, dp(row, col + 1, two) + arr[row][col + 1].first);
    }else {
        if(row != n - 1) minval = min(minval, dp(row + 1, col, two) + arr[row + 1][col].second);
        if(col != n - 1) minval = min(minval, dp(row, col + 1, two) + arr[row][col + 1].second);
    }
    return cached[row][col][two] = minval;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    bool one = false;
    int rone,cone;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int a;
            cin >> a;
            if(a == 0) {
                one = true;
                rone=i,cone=j;
            }
            if(a != 0) {
                while(a % 2ll == 0) {
                    arr[i][j].first++;
                    a/=2ll;
                }
                while(a % 5ll == 0) {
                    arr[i][j].second++;
                    a /= 5ll;
                }
            }
        }
    }
    int two = dp(0, 0, true) + arr[0][0].first;
    int five = dp(0, 0, false) + arr[0][0].second;
    if(min(two, five) >= 1 && one) {
        cout<<1<<'\n';
        for(int k = 0; k < rone; k ++) cout<<'D';
        for(int k = 0; k < cone; k ++) cout<<'R';
        for(int k = 0; k < n - rone - 1; k++) cout<<'D';
        for(int k = 0; k < n -cone - 1; k++) cout<<'R';
        cout<<'\n';
        return 0;
    }
    cout<<min(two, five)<<'\n';
    if(two < five) {
        int current = arr[0][0].first;
        int row = 0, col = 0;
        for(int i = 0; i < n * 2 - 2; i++) {
            if(row == n-1 || (col != n-1 && dp(row + 1,col, true) + arr[row + 1][col].first  + current != two)) {
                cout<<'R';
                col++;
            }else {
                cout<<'D';
                row++;
            }
            current += arr[row][col].first;
        }
    }else {
        int current = arr[0][0].second;
        int row = 0, col = 0;
        for(int i = 0; i < n * 2 - 2; i++) {
            if(row == n-1 || (col != n-1 && dp(row + 1,col, false)+ arr[row + 1][col].second + current != five)) {
                cout<<'R';
                col++;
            }else {
                cout<<'D';
                row++;
            }
            current += arr[row][col].second;
        }
    }
    cout<<'\n';
    return 0;
}
