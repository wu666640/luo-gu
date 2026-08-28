// 拓扑排序 — Kahn 算法（入度 + 队列），附是否成环判定
#include <bits/stdc++.h>
using namespace std;

/*
 * Kahn 拓扑排序：
 *   每次取出一个入度为 0 的点加入拓扑序列，并把它的所有出边"删掉"
 *   （即对应终点入度 -1），若某点入度归零则再入队。
 *   若最终能取出的点数 < n，说明图中存在环，无法拓扑排序。
 *   复杂度 O(n + m)。适用于有向无环图 (DAG)。
 */

const int MAXN = 1005;

vector<int> G[MAXN];   // 邻接表（存出边终点）
int indeg[MAXN];       // indeg[i] = 点 i 的入度

// 返回拓扑序列；若存在环则 vector 为空。
// n: 点数。
vector<int> topoSort(int n) {
    vector<int> ans;
    queue<int> q;

    for (int i = 1; i <= n; ++i)
        if (indeg[i] == 0) q.push(i); // 先把所有入度为 0 的点入队

    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans.push_back(u);
        for (int v : G[u]) {
            if (--indeg[v] == 0) q.push(v); // 删边后入度归零则入队
        }
    }

    // 若取出的点数不足 n，说明有环
    if ((int)ans.size() != n) return {}; // 返回空表示有环
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：一张有向无环图（DAG），输出其拓扑序列
    // 输入：第一行 n m（点数、边数），接下来 m 行 u v（u->v）
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        ++indeg[v]; // v 的入度 +1
    }

    vector<int> ans = topoSort(n);
    if (ans.empty()) {
        cout << "该图存在环，无法拓扑排序\n";
    } else {
        cout << "拓扑序列：";
        for (int i = 0; i < (int)ans.size(); ++i)
            cout << (i ? " " : "") << ans[i];
        cout << "\n";
    }
    return 0;
}
