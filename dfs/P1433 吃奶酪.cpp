//https://www.luogu.com.cn/problem/P1433
// P1433 吃奶酪 — 记忆化 DFS（状压 TSP）
// 题意：老鼠从原点 (0,0) 出发，要吃遍所有 n 块奶酪（n 个点），
//       求走遍所有点的最短总距离。任一两点可直达，距离为欧氏距离。
// 思路：TSP，状态为 (mask, last)：已访问的点集 mask，当前停在 last。
//       用记忆化搜索 dfs(mask, last) 表示「从当前位置出发还要走完剩余点」的最短总距离。
//       转移：从 last 再走到一个未访问点 j。O(2^n * n^2)，n<=15 可过。
#include <bits/stdc++.h>
using namespace std;

const int N = 16;
int n;
double x[N], y[N];          // 各点坐标，0..n-1；原点为 (0,0) 单独处理
double dist[N][N];          // 预处理任意两点距离
double memo[1 << N][N];     // memo[mask][last]：已访问 mask、停在 last 的剩余最短距离（-1 表示未算）

double dis(int a, int b) {
    double dx = x[a] - x[b], dy = y[a] - y[b];
    return sqrt(dx * dx + dy * dy);
}

double dfs(int mask, int last) {
    if (mask == (1 << n) - 1) return 0;             // 所有奶酪都吃完了
    if (memo[mask][last] >= 0) return memo[mask][last];  // 记忆化
    double best = 1e18;
    for (int j = 0; j < n; ++j) {
        if (mask >> j & 1) continue;                // j 已访问过
        best = min(best, dist[last][j] + dfs(mask | (1 << j), j));
    }
    return memo[mask][last] = best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    // 预处理点与点之间的距离
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = dis(i, j);

    memset(memo, -1, sizeof(memo));

    // 从原点第一次走到某块奶酪，取最小
    double ans = 1e18;
    for (int i = 0; i < n; ++i) {
        double fromOrigin = sqrt(x[i] * x[i] + y[i] * y[i]);
        ans = min(ans, fromOrigin + dfs(1 << i, i));
    }

    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}
