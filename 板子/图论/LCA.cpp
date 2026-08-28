// LCA — 树上最近公共祖先，倍增思想（depth、up[N][LOG]）
#include <bits/stdc++.h>
using namespace std;

/*
 * 倍增法求 LCA（最近公共祖先）：
 *   预处理：一次 DFS/BFS 求出每个点的深度 depth[u]，
 *          以及 up[u][k] = 从 u 向上跳 2^k 步到达的祖先。
 *   查询 lca(u,v)：
 *        1) 先把较深的点向上跳到与另一个同深度；
 *        2) 再从大到小尝试一起向上跳，若跳 2^k 步后不相等则跳；
 *        3) 最终父节点即为 LCA。
 *   预处理 O(n log n)，每次查询 O(log n)。
 */

const int MAXN = 1005;
const int LOG = 11; // > log2(最大深度)，对 n<=1000 取 11 足够

vector<int> G[MAXN];   // 邻接表（存子结点）
int depth[MAXN];       // depth[u] = u 的深度（根为 1）
int up[MAXN][LOG];     // up[u][k] = u 向上 2^k 步的祖先

// 从根开始 DFS 预处理 depth 与 up
void dfs(int u, int parent) {
    up[u][0] = parent;
    for (int k = 1; k < LOG; ++k) up[u][k] = up[up[u][k - 1]][k - 1];

    for (int v : G[u]) {
        if (v == parent) continue; // 不再走回父结点
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

// 查询 u, v 的最近公共祖先
int lca(int u, int v) {
    // 1) 让 u 是较深的那个
    if (depth[u] < depth[v]) swap(u, v);

    // 2) 把 u 上跳到和 v 同深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; ++k)
        if (diff >> k & 1) u = up[u][k];

    // 已经相遇
    if (u == v) return u;

    // 3) 一起向上跳，跳到 LCA 正下方
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0]; // 父结点即 LCA
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：一棵小树，求若干对点的 LCA
    // 输入：第一行 n（点数，根为 1），接下来 n-1 行 u v 表示一条树边
    //       之后若干组查询，每行两个点，直到文件结束：求其 LCA
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    depth[1] = 0;
    dfs(1, 0);

    int u, v;
    while (cin >> u >> v) {
        cout << "LCA(" << u << ", " << v << ") = " << lca(u, v) << "\n";
    }
    return 0;
}
