// Dijkstra — 堆优化 Dijkstra（非负权单源最短路）：dist 数组 + 优先队列
#include <bits/stdc++.h>
using namespace std;

/*
 * Dijkstra 算法：
 *   适用于【边权非负】的单源最短路。本质是贪心 + 松弛。
 *   用优先队列 (小根堆) 每次取出当前距离最小的未确定点来扩展，
 *   复杂度 O((n+m) log n)。
 * 注意：如果存在负权边，贪心会出错，应改用 SPFA / Bellman-Ford。
 */

typedef long long ll;
const int MAXN = 1005;
const ll INF = 0x3f3f3f3f3f3f3f3f; // 足够大的"无穷大"

struct Edge { int to; int w; };              // 目标点 + 边权
vector<Edge> G[MAXN];                        // 邻接表存图
ll dist[MAXN];                               // dist[i] = 源点到 i 的最短距离
bool vis[MAXN];                              // vis[i] = 点 i 是否已确定最短路

// s: 源点, n: 点数。跑完 dist[1..n] 即为答案，不可达的点保持 INF。
void dijkstra(int s, int n) {
    // pair<距离, 点>，默认按 first 从小到大 -> 小根堆
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;

    for (int i = 1; i <= n; ++i) { dist[i] = INF; vis[i] = false; }
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;   // 这个点已经确定了最短路，跳过
        vis[u] = true;

        // 松弛 u 的所有出边
        for (auto &e : G[u]) {
            int v = e.to;
            // 通过 u 走到 v 更短 -> 更新
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：一张小图，求 1 号点到其它所有点的最短路
    // 输入：第一行 n m（点数、边数），接下来 m 行 u v w
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w}); // 有向边
    }

    dijkstra(1, n);

    cout << "从 1 到各点的最短路：\n";
    for (int i = 1; i <= n; ++i) {
        cout << "  dist[" << i << "] = ";
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }
    return 0;
}
