// 树的直径与重心 — 两遍 BFS 求直径 + 逆序累加子树大小求重心（全迭代，不爆栈）
#include <bits/stdc++.h>
using namespace std;

/*
 * 树的直径：树上最远两点间的距离。
 *   做法：任取一点 s 出发 BFS 找最远点 u；再从 u 出发 BFS 找最远点 v，
 *         dist(u, v) 就是直径。复杂度 O(n)。
 * 树的重心：删掉该点后，剩余各连通块大小的最大值最小。
 *   求法：以 1 为根 BFS 定序，逆序累加出子树大小 sub[]，
 *         再枚举每个点 u，其「最大连通块」= max(n - sub[u], max sub[v])（v 是 u 的儿子）。
 *   性质：重心最多两个（相邻）；把树按重心分开，每块大小 <= n/2。
 * 说明：这里的图用 vector 动态开，不写死 MAXN；全程 BFS/迭代，链长 2e5 也不爆栈。
 */

int n;                          // 点数（1-indexed）
vector<vector<int>> g;          // 邻接表
vector<int> par;                // BFS 生成树的父节点
vector<int> order;              // BFS 遍历序（父一定在子前面）

// 从 s 出发 BFS，返回 {最远点, 到最远点的距离}
pair<int, int> bfsFarthest(int s) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    int far = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] > dist[far]) far = u;
        for (int v : g[u])
            if (dist[v] < 0) { dist[v] = dist[u] + 1; q.push(v); }
    }
    return {far, dist[far]};
}

// 树的重心（若有多个，返回下标较小的那个）
int treeCentroid() {
    par.assign(n + 1, 0);
    order.clear();
    vector<int> sub(n + 1, 1);
    vector<int> vis(n + 1, 0);

    queue<int> q;
    q.push(1);
    vis[1] = 1;
    order.push_back(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u])
            if (!vis[v]) { vis[v] = 1; par[v] = u; order.push_back(v); q.push(v); }
    }

    // 逆序遍历：儿子的 sub 已经算好，才轮到父亲累加
    for (int i = (int)order.size() - 1; i > 0; --i)
        sub[par[order[i]]] += sub[order[i]];

    int best = 1, bestVal = INT_MAX;
    for (int u = 1; u <= n; ++u) {
        int mx = n - sub[u];                                  // 往父亲方向那块
        for (int v : g[u]) if (par[v] == u) mx = max(mx, sub[v]); // 每个儿子子树
        if (mx < bestVal) { bestVal = mx; best = u; }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示用的树：1-2, 2-3, 2-4, 4-5
    n = 5;
    g.assign(n + 1, {});
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {2, 4}, {4, 5}};
    for (auto [u, v] : edges) { g[u].push_back(v); g[v].push_back(u); }

    int u = bfsFarthest(1).first;          // 一个端点
    auto [v, d] = bfsFarthest(u);          // 另一个端点 + 直径
    cout << "直径端点 = " << u << " 和 " << v << "，直径 = " << d
         << "  (端点为 1 和 5，长度 3)\n";
    cout << "重心 = " << treeCentroid() << "  (应为 2：删掉 2 后最大块是 {1} 之外还有 {3},{4,5}，最大 2)\n";
    return 0;
}
