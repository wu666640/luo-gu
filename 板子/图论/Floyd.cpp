// Floyd — Floyd-Warshall 全源最短路（O(n^3)）
#include <bits/stdc++.h>
using namespace std;

/*
 * Floyd-Warshall 算法：
 *   求任意两点间的最短路（全源最短路），支持负权边（但不能有负环）。
 *   核心思想：dp[k][i][j] = 只经过前 k 个点中转时 i->j 的最短路。
 *   滚动掉第一维后即经典的 d[i][j] = min(d[i][j], d[i][k] + d[k][j])。
 *   复杂度 O(n^3)，通常 n <= 500 时可用；n 大时改用 Dijkstra(n 次) 或 Johnson。
 */

const int MAXN = 505;
const int INF = 0x3f3f3f3f;  // 足够大的"无穷大"，保证两倍仍不溢出

int d[MAXN][MAXN];           // d[i][j] = i 到 j 的最短路（也是距离矩阵）

// n: 点数。调用前需先初始化 d（见 main），之后 floyd 求出全源最短路。
void floyd(int n) {
    // 第一维滚动：先枚举中转点 k，再枚举 i、j
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：一张带权小图，用距离矩阵初始化并求全源最短路
    // 输入：第一行 n m（点数、边数），接下来 m 行 u v w
    // 不存在的边用 INF 表示；自己到自己为 0
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            d[i][j] = (i == j ? 0 : INF);  // 对角为 0，其余为 INF

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = min(d[u][v], w);  // 有向边，取最短以防重边
    }

    floyd(n);

    cout << "全源最短路（距离矩阵）：\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) cout << "0 ";
            else if (d[i][j] == INF) cout << "INF ";
            else cout << d[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
