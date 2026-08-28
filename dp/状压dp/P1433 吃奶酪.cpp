//https://www.luogu.com.cn/problem/P1433
#include<bits/stdc++.h>
using namespace std;

const int N = 16;
int n;
double x[N], y[N], dist[N][N];
double dp[1<<N][N];

double dis(int a, int b) {
    return sqrt((x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]));
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = dis(i, j);
    
 
    for (int i = 0; i < (1<<n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 1e18;
    
    for (int i = 0; i < n; i++)
        dp[1<<i][i] = sqrt(x[i]*x[i] + y[i]*y[i]);
    

    for (int mask = 1; mask < (1<<n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1<<i))) continue;  
        
            for (int j = 0; j < n; j++) {
                if (mask & (1<<j)) continue; 
                int nxt = mask | (1<<j);
                dp[nxt][j] = min(dp[nxt][j], dp[mask][i] + dist[i][j]);
            }
        }
    }
    
    double ans = 1e18;
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[(1<<n)-1][i]);
    cout << fixed << setprecision(2) << ans << endl;
}