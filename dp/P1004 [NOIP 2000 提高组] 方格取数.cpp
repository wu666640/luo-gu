//https://www.luogu.com.cn/problem/P1004
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
int a[MAXN][MAXN];
int f[MAXN][MAXN][MAXN][MAXN];   // f[i][j][k][l]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    while (true) {
        int x, y, v;
        cin >> x >> y >> v;
        if (x == 0 && y == 0 && v == 0) break;
        a[x][y] = v;
    }

    memset(f, -0x3f, sizeof(f));
    f[1][1][1][1] = a[1][1];   // 起点两人都在 (1,1)

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int l = 1; l <= n; l++) {
                    if (i == 1 && j == 1 && k == 1 && l == 1) continue;  // 起点已初始化

                    // 四种转移：两人分别从 上/左 过来
                    int best = max({
                        f[i-1][j][k-1][l],   // 上 上
                        f[i-1][j][k][l-1],   // 上 左
                        f[i][j-1][k-1][l],   // 左 上
                        f[i][j-1][k][l-1]    // 左 左
                    });
                    if (best < 0) continue;

                    f[i][j][k][l] = best + a[i][j] + a[k][l];
                    if (i == k && j == l) f[i][j][k][l] -= a[i][j];  // 同格只算一次
                }
            }
        }
    }

    cout << f[n][n][n][n] << endl;   // 终点两人都在 (n,n)
    return 0;
}