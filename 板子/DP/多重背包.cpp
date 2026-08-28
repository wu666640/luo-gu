// 多重背包 — 多重背包：二进制拆分转化为 0-1 背包求最大价值
#include <bits/stdc++.h>
using namespace std;

// 体积上限与拆分后物品数上限
const int MAXN = 105;
const int MAXV = 2005;
const int MAXK = MAXN * 20; // 拆分后物品总数（原物品数 * log 数量）

struct Good { int v, w; } a[MAXK]; // 拆分后的每个"新物品"
int dp[MAXV];
int cnt = 0; // 拆分后的物品件数

/*
 * 多重背包：每种物品有数量限制 num。
 * 二进制拆分思想：把 num 拆成 1, 2, 4, ..., 2^k 以及剩余 r 若干组，
 * 每组作为一个"新物品"（体积 = 组数 * 原体积，价值 = 组数 * 原价值）。
 * 这样 0..num 的任意取法都能由若干组组合出来，且每组最多取一次，
 * 于是原多重背包问题等价于 0-1 背包。
 * 拆分复杂度 O(log num)，总复杂度 O(n * log num * V)。
 */
void addItem(int v, int w, int num) {
    for (int k = 1; num > 0; k <<= 1) {
        int take = min(k, num);
        a[++cnt] = {take * v, take * w};
        num -= take;
    }
}

// 对拆分后得到的 cnt 个 0-1 物品做 0-1 背包（体积逆序）
int knapMultiple(int n, int V) {
    for (int i = 1; i <= cnt; ++i)
        for (int c = V; c >= a[i].v; --c)
            dp[c] = max(dp[c], dp[c - a[i].v] + a[i].w);
    return dp[V];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(dp, 0, sizeof(dp));
    cnt = 0;

    // 演示：4 种物品（体积、价值、数量），背包容量 10
    int n = 4, V = 10;
    int vv[] = {2, 3, 4, 5};
    int ww[] = {3, 4, 5, 6};
    int cc[] = {3, 2, 1, 2};
    for (int i = 1; i <= n; ++i)
        addItem(vv[i - 1], ww[i - 1], cc[i - 1]);

    cout << "多重背包最大价值：" << knapMultiple(n, V) << '\n';
    return 0;
}
