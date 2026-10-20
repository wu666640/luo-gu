// 拓扑排序 — Kahn（判环）+ 字典序最小/最大 + DAG 上 DP（点权最长路 / 路径计数）
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * 拓扑排序：把有向图的点排成一列，使每条边 u->v 都有 u 排在 v 之前。
 * 前提是 DAG（有向无环图）；有环时拓扑序不存在。
 *
 * Kahn 骨架（O(n+m)）：
 *   入度为 0 的点入队 -> 取出一个加进序列 -> "删掉"它的出边（终点入度 -1）
 *   -> 入度归零的点再入队。最后取出的点数 < n 就说明有环。
 *
 * 三个常用变体都是这同一副骨架：
 *   1) 任意拓扑序 + 判环          queue                    O(n+m)
 *   2) 字典序最小 / 最大拓扑序     小根堆 / 大根堆          O((n+m) log n)
 *   3) DAG 上的 DP（最长路/计数）  按拓扑序转移             O(n+m)
 *
 * 两个易错点：
 *   - 别在函数里直接改全局 indeg[]：多组数据或调用两次就会算错（下面改成内部拷贝）
 *   - 图按 n 用邻接表动态开，别写死 MAXN
 */

int n;                        // 点数，编号 1..n
vector<vector<int>> g;        // g[u] = u 的所有出边终点
vector<int> indeg0;           // 原始入度（只读；函数内部拷贝一份再修改）

// 建图：es 中每个 (u, v) 表示一条 u -> v 的边
void buildGraph(int n_, const vector<pair<int, int>>& es) {
    n = n_;
    g.assign(n + 1, {});
    indeg0.assign(n + 1, 0);
    for (auto [u, v] : es) { g[u].push_back(v); ++indeg0[v]; }
}

// 1) 任意拓扑序；有环返回空 vector
vector<int> topoSort() {
    vector<int> deg = indeg0;              // 拷贝！不要动原入度
    vector<int> ans;
    ans.reserve(n);
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans.push_back(u);
        for (int v : g[u])
            if (--deg[v] == 0) q.push(v);
    }
    return (int)ans.size() == n ? ans : vector<int>();   // 取出的点不足 n => 有环
}

// 2) 字典序最小的拓扑序：queue 换成小根堆（每次取编号最小的可选项）
//    把 greater<int> 换成 less<int> 就是字典序最大（两种贪心都可用暴力验证通过）
vector<int> topoSortMin() {
    vector<int> deg = indeg0;
    vector<int> ans;
    ans.reserve(n);
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 0) pq.push(i);
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        ans.push_back(u);
        for (int v : g[u])
            if (--deg[v] == 0) pq.push(v);
    }
    return (int)ans.size() == n ? ans : vector<int>();
}

// 3) DAG 上 DP —— 点权最长路（洛谷 P1113 杂务式）
//    dp[v] = val[v] + max(dp[u])（u 取遍 v 的全部前驱），按拓扑序转移一遍即可
//    返回 {最长长度, 终点}；有环返回 {-1, -1}
pair<ll, int> dagLongestPath(const vector<int>& val) {
    vector<int> ord = topoSort();
    if (ord.empty()) return {-1, -1};
    vector<ll> dp(n + 1, 0);
    ll best = 0;
    int bestV = 0;
    for (int u : ord) {
        dp[u] += val[u];                        // 加上自己的点权
        if (dp[u] > best) { best = dp[u]; bestV = u; }
        for (int v : g[u]) dp[v] = max(dp[v], dp[u]);
    }
    return {best, bestV};
}

// 3') DAG 上 DP —— 路径计数（洛谷 P4017 最大食物链计数式）
//     cnt[v] = sum(cnt[u])（u 取遍 v 的全部前驱）；入度为 0 的源点 cnt = 1
//     汇点（出度为 0）的 cnt 就是"以它为终点的完整链条数"；有环返回空
vector<ll> dagPathCount(ll mod) {
    vector<int> ord = topoSort();
    if (ord.empty()) return {};                 // 有环：无意义
    vector<ll> cnt(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        if (indeg0[i] == 0) cnt[i] = 1;
    for (int u : ord)
        for (int v : g[u]) cnt[v] = (cnt[v] + cnt[u]) % mod;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ---------- 1) 拓扑序 / 字典序最小 / 判环 ----------
    // 图：2 -> 1，点 3 孤立。队列版里 3 早就排在队列中，所以 1 反而排在 3 后面
    buildGraph(3, {{2, 1}});
    cout << "队列版拓扑序    : ";
    for (int x : topoSort()) cout << x << " ";
    cout << " (应为 2 3 1)\n";

    cout << "字典序最小拓扑序 : ";
    for (int x : topoSortMin()) cout << x << " ";
    cout << " (应为 2 1 3：选完 2 后 1 入度归零，1 比 3 小所以先选 1)\n";

    buildGraph(3, {{1, 2}, {2, 3}, {3, 1}});    // 1->2->3->1 成环
    cout << "成环图           : "
         << (topoSort().empty() ? "拓扑序为空 -> 正确判定有环" : "非空 -> 判错了") << "\n";

    // ---------- 2) 点权最长路（P1113 杂务式）----------
    // 图：1->3, 2->3, 3->4, 3->5；点权 val[1..5] = 5 2 6 1 3
    buildGraph(5, {{1, 3}, {2, 3}, {3, 4}, {3, 5}});
    vector<int> val = {0, 5, 2, 6, 1, 3};
    auto [best, endV] = dagLongestPath(val);
    cout << "最长点权路径     : " << best << "（终点 " << endV << "） (应为 14，终点 5：5+6+3)\n";

    // ---------- 3) 路径计数（P4017 最大食物链式）----------
    // 图：1->2, 1->3, 2->3, 3->4（1 是唯一源点，4 是汇点）
    buildGraph(4, {{1, 2}, {1, 3}, {2, 3}, {3, 4}});
    vector<ll> cnt = dagPathCount(1000000007LL);
    cout << "路径数 cnt[1..4] : ";
    for (int i = 1; i <= n; ++i) cout << cnt[i] << " ";
    cout << " (应为 1 1 2 2；到汇点 4 的完整链 = " << cnt[4] << " 条)\n";

    // 要改成输入式：把上面几行 buildGraph 换成读入 n, m 和 m 条边即可
    return 0;
}
