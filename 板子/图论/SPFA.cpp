// SPFA — 队列优化 Bellman-Ford，可判负环（cnt 记录入队次数）
#include <bits/stdc++.h>
using namespace std;

/*
 * SPFA（Shortest Path Faster Algorithm）：
 *   Bellman-Ford 的队列优化版，求单源最短路。
 *   松弛一条边后，若终点 dist 变小则把它加入队列等待再次松弛。
 *   判断负环：记录每个点入队次数 cnt[v]，若某个点入队次数 >= n，
 *   说明图中存在从源点可达的负环（此时没有最短路）。
 *   复杂度理论上界 O(nm)，实际通常很快，但在构造数据下可能退化。
 */

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;

struct Edge { int to; int w; };
vector<Edge> G[MAXN];

int dist[MAXN];
int cnt[MAXN];      // cnt[i] = i 入队次数，用于判负环
bool inQueue[MAXN]; // inQueue[i] = i 是否在队列中

// 返回 true 表示存在负环，false 表示正常求出了最短路。
// 结果保存在 dist[1..n]。
bool spfa(int s, int n) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) { dist[i] = INF; cnt[i] = 0; inQueue[i] = false; }

    dist[s] = 0;
    q.push(s);
    inQueue[s] = true;
    cnt[s] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (auto &e : G[u]) {
            int v = e.to;
            if (dist[v] > dist[u] + e.w) {   // 松弛成功
                dist[v] = dist[u] + e.w;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    if (++cnt[v] >= n) return true; // 入队达到 n 次 => 存在负环
                }
            }
        }
    }
    return false; // 没有负环
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：跑 SPFA 求最短路，并可选地检测负环
    // 输入：第一行 n m（点数、边数），接下来 m 行 u v w
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }

    bool negCycle = spfa(1, n);
    if (negCycle) {
        cout << "存在从 1 可达的负环，无最短路\n";
    } else {
        cout << "从 1 到各点的最短路：\n";
        for (int i = 1; i <= n; ++i) {
            cout << "  dist[" << i << "] = ";
            if (dist[i] == INF) cout << "INF\n";
            else cout << dist[i] << "\n";
        }
    }
    return 0;
}
