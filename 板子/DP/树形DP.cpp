// 树形DP — 树上最大独立集（没有上司的舞会）：f[u][0/1]
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> g[MAXN]; // 邻接表存树（父 -> 子）
int val[MAXN];       // 每个结点的权值
int f[MAXN][2];      // f[u][0/1]：u 不选 / 选时，u 子树的最大权值和
bool hasFa[MAXN];    // 是否有父结点（用于找根）

/*
 * 树上最大独立集（相邻点不能同时选，经典"没有上司的舞会"）。
 * 状态定义：
 *   f[u][0] = u 不选时，以 u 为根的子树能取到的最大权值和；
 *   f[u][1] = u  选时，以 u 为根的子树能取到的最大权值和。
 * 转移（对每个子结点 v，后序遍历累加进来）：
 *   f[u][0] += max(f[v][0], f[v][1]);   // u 不选，子结点可选可不选
 *   f[u][1] += f[v][0];                 // u  选，子结点必须不选
 * 边界：叶子 f[u][0] = 0，f[u][1] = val[u]（初始化时令 f[u][1] = val[u]）。
 * 答案：max(f[root][0], f[root][1])。
 * 复杂度：O(n)。
 */
void dfs(int u) {
    f[u][1] = val[u];
    for (int v : g[u]) {
        dfs(v);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：7 个结点的树，求最大选点权值和（相邻不能同时选）
    int n = 7;
    int w[] = {0, 1, 2, 3, 4, 5, 6, 7}; // val[1..7] = 1..7
    for (int i = 1; i <= n; ++i) val[i] = w[i];

    // 建树（有向：父 -> 子）
    int edge[][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}};
    for (int i = 0; i < n - 1; ++i) {
        int u = edge[i][0], v = edge[i][1];
        g[u].push_back(v);
        hasFa[v] = true;
    }
    int root = 1;
    for (int i = 1; i <= n; ++i)
        if (!hasFa[i]) { root = i; break; }

    dfs(root);
    cout << "最大选点权值和：" << max(f[root][0], f[root][1]) << '\n';
    // 如选 {1,4,5,6,7}: 1+4+5+6+7 = 23
    return 0;
}
