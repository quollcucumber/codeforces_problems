#include <bits/stdc++.h>
#define int long long
using namespace std;

int cached[75][75][40][75];
int arr[75][75];
bool seen[75][75][40][75];
int n, m, k;
int dp(int r, int c, int left, int kmod) {
    if (seen[r][c][left][kmod]) return cached[r][c][left][kmod];
    seen[r][c][left][kmod] = true;
    if (c == m) {
        if (r == n-1) {
            if (kmod == 0) return  cached[r][c][left][kmod] = 0;
            else return  cached[r][c][left][kmod] = INT_MIN;
        }else {
            return  cached[r][c][left][kmod] = dp(r+1, 0, m/2, kmod);
        }
    }
    int maxval = INT_MIN;
    if (left != 0) maxval = max(maxval, dp(r, c+1, left-1, (kmod + arr[r][c]) % k) + arr[r][c]);
    maxval = max(maxval, dp(r, c + 1, left, kmod));
    return cached[r][c][left][kmod] = maxval;
}
signed main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
   cout<<dp(0, 0, m/2, 0)<<'\n';
} 
