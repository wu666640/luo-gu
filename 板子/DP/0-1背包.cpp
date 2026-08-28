// 0-1背包 — 0-1 背包：一维滚动数组（体积逆序）求最大价值
#include <bits/stdc++.h>
using namespace std;

// 物品数上限与体积上限（可按题目调整）
const int MAXN = 105;   // 物品个数上限
const int MAXV = 1005;  // 背包容量上限

int v[MAXN];  // v[i]：第 i 件物品的体积
int w[MAXN];  // w[i]：第 i 件物品的价值
int dp[MAXV]; // dp[c]：容量为 c 时能获得的最大价值

/*
 * 0-1 背包（一维滚动数组优化）
 * 状态定义：dp[c] 表示背包容量为 c 时能装下的最大价值。
 * 转移方程（对第 i 件物品，容量逆序更新）：
 *   dp[c] = max(dp[c], dp[c - v[i]] + w[i]),  c: V -> v[i]
 * 逆序更新保证每件物品最多只被选一次（0-1 特性）。
 * 初始：dp[0..V] = 0。
 * 复杂度：O(n * V)，空间 O(V)。
 */
int knap01(int n, int V) {
    for (int i = 1; i <= n; ++i)
        for (int c = V; c >= v[i]; --c)   // 体积逆序
            dp[c] = max(dp[c], dp[c - v[i]] + w[i]);
    // dp[V] 即为容量正好不超过 V 时的最大价值
    return *max_element(dp, dp + V + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：4 件物品，容量 8 的背包，求最大价值
    int n = 4, V = 8;
    int vv[] = {2, 3, 4, 5};
    int ww[] = {3, 4, 5, 6};
    for (int i = 1; i <= n; ++i) { v[i] = vv[i - 1]; w[i] = ww[i - 1]; }

    cout << "0-1 背包最大价值：" << knap01(n, V) << '\n';
    // 输出每个容量下的最优价值（滚动数组最终值）
    for (int c = 1; c <= V; ++c)
        cout << "容量" << c << "=" << dp[c] << (c == V ? '\n' : ' ');
    return 0;
}
