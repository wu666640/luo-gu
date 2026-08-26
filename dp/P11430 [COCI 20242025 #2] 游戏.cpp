#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5010;
int n, m;
int p[N], t[N], o[N];
int f[N], dp[N];

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> t[i] >> o[i];
    }

    for (int i = 1; i <= n; i++) {
        
        for (int j = m; j >= p[i]; j--) {
            dp[j] = f[j - p[i]];
        }
        //花费p[i]学习，t[i]游玩,获得o[i]得分
        for (int j = p[i] + t[i]/*提前预留p[i]+t[i]时间 */; j <= m; j++) {
            dp[j] = max(dp[j], dp[j - t[i]] + o[i]);
        }
        for (int j = 1; j <= m; j++) {
            f[j] = max(f[j], dp[j]);
        }
    }

    int ans = 0;
    for (int j = 0; j <= m; j++) ans = max(ans, f[j]);
    cout << ans << endl;
    return 0;
}