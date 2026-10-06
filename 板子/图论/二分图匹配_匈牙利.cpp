// 二分图最大匹配 — 匈牙利算法（Kuhn，基于增广路）
#include <bits/stdc++.h>
using namespace std;

/*
 * 匈牙利算法（Kuhn）求二分图最大匹配：
 *   对左部点依次尝试找一条"增广路"（匹配边/非匹配边交替出现，
 *   且两端都是未匹配点的路径），找到则匹配数 +1。
 *
 *   vis 数组记录"本轮"访问过的右部点，每个左部点开始时清空，
 *   用于防止 DFS 死循环；只对右部点打标记。
 *
 *   复杂度 O(nE)，n 为左部点数。对一般模板题足够。
 *   也可用网络流建模求最大匹配（见 网络流_Dinic.cpp）。
 */

const int MAXN = 1005;

int n, m;             // 左部点 1..n，右部点 1..m
vector<int> G[MAXN];  // 左部点 -> 可匹配的右部点
int matchR[MAXN];     // 右部点当前匹配的左部点，0 表示未匹配
int vis[MAXN];        // 本轮右部点访问标记

// 给左部点 u 找增广路，找到返回 true
bool dfs(int u) {
    for (int v : G[u]) {
        if (vis[v]) continue;
        vis[v] = 1;
        // v 未匹配，或 v 当前匹配的点能换到别处
        if (matchR[v] == 0 || dfs(matchR[v])) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

// 返回最大匹配数；匹配方案保存在 matchR 里
int hungarian() {
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) ++ans;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // P3386 输入：n m k，接下来 k 行 u v（左部 u 连向右部 v）
    int k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    cout << hungarian() << "\n";
    return 0;
}
