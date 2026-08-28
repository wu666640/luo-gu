// 状压DP — 状态压缩 DP：TSP（类 P1433 吃奶酪）求最短回路
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;        // 点数上限（n 较小时使用状压）
const double INF = 1e18;
double x[MAXN], y[MAXN];         // 各点坐标
double dis[MAXN][MAXN];          // dis[i][j]：点 i 到 j 的欧氏距离
double dp[1 << MAXN][MAXN];      // dp[mask][i]：已访问点集 mask，停在 i 的最短路径长

/*
 * 状态压缩 TSP（哈密顿回路：从点 0 出发遍历所有点并回到点 0）。
 * 状态：dp[mask][i] = 已访问的点集合为 mask（二进制位 1 表示已访问），
 *       且当前最后一次停靠在点 i 时的最短路径长度。
 * 转移：枚举下一个未访问的点 j：
 *   dp[mask | (1<<j)][j] = min(dp[mask|(1<<j)][j], dp[mask][i] + dis[i][j])
 * 初始：dp[1<<0][0] = 0（只访问过起点 0，停在 0）。
 * 答案：min_{i} dp[full][i] + dis[i][0]（遍历完所有点后回到起点）。
 * 复杂度：O(2^n * n^2)，仅适合 n <= 20 左右。
 */
double tsp(int n) {
    int full = (1 << n) - 1;
    for (int mask = 0; mask <= full; ++mask)
        for (int i = 0; i < n; ++i) dp[mask][i] = INF;
    dp[1][0] = 0;

    for (int mask = 1; mask <= full; ++mask) {
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) continue;    // i 必须已在集合中
            if (dp[mask][i] >= INF) continue;
            for (int j = 0; j < n; ++j) {
                if (mask & (1 << j)) continue;   // j 必须未访问
                int nmask = mask | (1 << j);
                dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + dis[i][j]);
            }
        }
    }
    double ans = INF;
    for (int i = 1; i < n; ++i)                  // 最后停靠点 i，回到起点 0
        ans = min(ans, dp[full][i] + dis[i][0]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：4 个点（单位正方形顶点），求最短哈密顿回路长度
    int n = 4;
    double xs[] = {0, 0, 1, 1};
    double ys[] = {0, 1, 0, 1};
    for (int i = 0; i < n; ++i) { x[i] = xs[i]; y[i] = ys[i]; }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dis[i][j] = hypot(x[i] - x[j], y[i] - y[j]);

    cout << "最短回路长度：" << tsp(n) << '\n'; // 正方形周长 4
    return 0;
}
