// 完全背包 — 完全背包：一维正序循环求最大价值
#include <bits/stdc++.h>
using namespace std;

// 物品数上限与体积上限（可按题目调整）
const int MAXN = 105;
const int MAXV = 1005;

int v[MAXN];  // v[i]：第 i 种物品的体积
int w[MAXN];  // w[i]：第 i 种物品的价值
int dp[MAXV]; // dp[c]：容量为 c 时的最大价值

/*
 * 完全背包（一维滚动数组，容量正序循环）
 * 状态定义：dp[c] 表示背包容量为 c 时的最大价值。
 * 转移方程（容量正序更新）：
 *   dp[c] = max(dp[c], dp[c - v[i]] + w[i]),  c: v[i] -> V
 * 因为每种物品不限件数，正序更新时 dp[c - v[i]] 可能已经取过当前物品，
 * 从而允许同一物品被重复选取（完全背包特性）。
 * 与 0-1 背包唯一的区别即循环顺序（0-1 逆序，完全背包正序）。
 * 复杂度：O(n * V)，空间 O(V)。
 */
int knapComplete(int n, int V) {
    for (int i = 1; i <= n; ++i)
        for (int c = v[i]; c <= V; ++c)   // 容量正序
            dp[c] = max(dp[c], dp[c - v[i]] + w[i]);
    return dp[V];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：3 种物品（每种无限），背包容量 10，求最大价值
    int n = 3, V = 10;
    int vv[] = {2, 3, 4};
    int ww[] = {3, 4, 5};
    for (int i = 1; i <= n; ++i) { v[i] = vv[i - 1]; w[i] = ww[i - 1]; }

    cout << "完全背包最大价值：" << knapComplete(n, V) << '\n';
    // 输出每个容量下的最优价值
    for (int c = 1; c <= V; ++c)
        cout << "容量" << c << "=" << dp[c] << (c == V ? '\n' : ' ');
    return 0;
}
