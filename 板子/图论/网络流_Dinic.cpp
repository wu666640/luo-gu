// 网络最大流 — Dinic（分层图 + 多路增广）
#include <bits/stdc++.h>
using namespace std;

/*
 * Dinic 求最大流：
 *   1) BFS 建立分层图（dep[v] = 从 S 到 v 的最短边数）
 *   2) DFS 沿分层图一次找多条增广路，借助当前弧 cur[] 优化
 *   3) 重复上面两步，直到 BFS 到不了 T
 *
 *   复杂度 O(V^2 E)，实际常数小、性能很好，通常是网络流首选。
 *
 *   本模板用 P3376 的输入格式；用 long long 存容量。
 *   二分图最大匹配建模：S 连所有左部点(cap=1)，左部点连右部点(cap=1)，
 *   右部点连 T(cap=1)，答案即为最大流。
 */

typedef long long ll;
const int MAXN = 10005;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct Edge { int to; ll cap; int rev; };
vector<Edge> G[MAXN];

int dep[MAXN], cur[MAXN]; // dep=分层深度, cur=当前弧

// 加一条有向边 u->v，并补上反向边（用于"退流"）
void addEdge(int u, int v, ll cap) {
    G[u].push_back({v, cap, (int)G[v].size()});
    G[v].push_back({u, 0,   (int)G[u].size() - 1});
}

// BFS 建分层图，返回能否到达汇点 T
bool bfs(int s, int t) {
    memset(dep, -1, sizeof(dep));
    queue<int> q;
    dep[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : G[u]) {
            if (e.cap > 0 && dep[e.to] < 0) {
                dep[e.to] = dep[u] + 1;
                q.push(e.to);
            }
        }
    }
    return dep[t] >= 0;
}

// DFS 多路增广，返回本次增广的流量；f 为流入 u 的限制
ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    for (int &i = cur[u]; i < (int)G[u].size(); ++i) {
        Edge &e = G[u][i];
        if (e.cap > 0 && dep[e.to] == dep[u] + 1) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d; // 反向边增加，可"退流"
                return d;
            }
        }
    }
    return 0;
}

ll dinic(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) {
        memset(cur, 0, sizeof(cur));
        ll f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // P3376 输入：n m s t，接下来 m 行 u v c
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    cout << dinic(s, t) << "\n";
    return 0;
}
