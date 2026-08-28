// Tarjan强连通分量 — Tarjan 求强连通分量（dfn、low、栈、scc 计数）
#include <bits/stdc++.h>
using namespace std;

/*
 * Tarjan 求强连通分量 (SCC)：
 *   dfn[u] = u 第一次被访问的时间戳（dfs 序）。
 *   low[u] = u 及其子孙能回溯到的最小 dfn。
 *   在 DFS 过程中用一个栈维护"尚未确定属于哪一个 SCC"的点。
 *   当 low[u] == dfn[u] 时，u 是一个强连通分量的根，
 *   把栈顶一直弹到 u，这些点构成一个 SCC。
 *   复杂度 O(n + m)。适用于有向图。
 */

const int MAXN = 1005;

vector<int> G[MAXN];
int dfn[MAXN];     // 时间戳
int low[MAXN];     // 能回溯到的最小 dfn
int scc[MAXN];     // scc[i] = 点 i 所属的 SCC 编号（从 1 开始）
bool inStack[MAXN]; // 是否在栈中
int timer = 0;      // 全局时间戳计数
int sccCnt = 0;     // SCC 总数
stack<int> st;

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    st.push(u);
    inStack[u] = true;

    for (int v : G[u]) {
        if (!dfn[v]) {          // v 尚未访问 -> 递归
            tarjan(v);
            low[u] = min(low[u], low[v]); // 回溯时更新 low
        } else if (inStack[v]) { // v 已在栈中 -> 是回边/横叉边
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 若 u 是所在 SCC 的根，则弹栈收集整个分量
    if (low[u] == dfn[u]) {
        ++sccCnt;
        while (true) {
            int x = st.top(); st.pop();
            inStack[x] = false;
            scc[x] = sccCnt; // 标记归属
            if (x == u) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：一张小有向图，输出每个强连通分量包含的点
    // 输入：第一行 n m（点数、边数），接下来 m 行 u v（u->v）
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    // 图可能不连通，对所有未访问的点都跑一次 tarjan
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);

    cout << "共有 " << sccCnt << " 个强连通分量：\n";
    // 按分量编号归类输出
    vector<vector<int>> comp(sccCnt + 1);
    for (int i = 1; i <= n; ++i) comp[scc[i]].push_back(i);
    for (int c = 1; c <= sccCnt; ++c) {
        cout << "  SCC" << c << ":";
        for (int x : comp[c]) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
