// 分组背包 — 每组物品最多选一个（体积逆序 + 组内枚举物品）
#include <bits/stdc++.h>
using namespace std;

/*
 * 分组背包：有若干组物品，每组内【最多选一个】，容量 V 内最大价值。
 *   状态：dp[c] = 容量 c 时的最大价值（一维滚动，初值 0 = 至多装满）
 *   转移：for 每组  ->  for c = V..0（体积逆序）  ->  for 组内每件 (w, v)
 *             dp[c] = max(dp[c], dp[c - w] + v)
 *   为什么逆序 + 先枚举容量：保证同一组内不会被选两次，
 *   组内多件物品的比较都发生在「上一组的结果」之上。
 *   复杂度 O(组数 * V * 组内物品数)，空间 O(V)。
 * 变体：要求「恰好装满」时把 dp 除了 dp[0] 外初始化成 -INF。
 */

// groups[i] = 第 i 组的所有 {体积, 价值}；返回容量不超过 V 的最大价值
int groupKnapsack(const vector<vector<pair<int, int>>>& groups, int V) {
    vector<int> dp(V + 1, 0);            // 用 V 动态开，换题不用改常量
    for (const auto& gp : groups)
        for (int c = V; c >= 0; --c)     // 体积逆序
            for (auto [w, v] : gp)
                if (c >= w) dp[c] = max(dp[c], dp[c - w] + v);
    return dp[V];                        // 初值 0 且 dp 单调不减，所以 dp[V] 就是答案
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 3 组物品，容量 6
    // 第 1 组：(体积2,价值3) (3,5)
    // 第 2 组：(1,2) (4,6)
    // 第 3 组：(3,4)
    vector<vector<pair<int, int>>> groups = {
        {{2, 3}, {3, 5}},
        {{1, 2}, {4, 6}},
        {{3, 4}},
    };
    int V = 6;
    cout << "分组背包最大价值 = " << groupKnapsack(groups, V)
         << "  (应为 9：如 第1组(3,5) + 第3组(3,4)，或 第1组(2,3)+第2组(1,2)+第3组(3,4))\n";
    return 0;
}
