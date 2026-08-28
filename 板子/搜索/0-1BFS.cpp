// 0-1 BFS — 双端队列求边权仅为 0 或 1 的最短路（复杂度 O(V+E)）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

vector<pair<int, int>> g[MAXN]; // 邻接表：g[u] = {v, w}，边权 w 为 0 或 1
int dist[MAXN];                 // 起点到各点的最短距离

// 0-1 BFS：从 s 出发求到各点的最短距离。
// 关键：因为边权只有 0/1，用双端队列维护——松弛到 0 边放队首，1 边放队尾，
// 保证队列始终按距离非降序，每个点被正确更新且复杂度 O(V+E)。
void bfs01(int s, int n) {
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    deque<int> dq;
    dist[s] = 0;
    dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto& e : g[u]) {
            int v = e.first, w = e.second;
            if (dist[u] + w < dist[v]) {   // 松弛成功
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v); // 0 边放队首（距离不加）
                else dq.push_back(v);         // 1 边放队尾
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：5 个点，边权为 0 或 1 的有向小图
    int n = 5;
    g[1].push_back({2, 0});
    g[1].push_back({3, 1});
    g[2].push_back({3, 0});
    g[2].push_back({4, 1});
    g[3].push_back({4, 0});
    g[3].push_back({5, 1});
    g[4].push_back({5, 0});

    bfs01(1, n); // 从点 1 出发
    cout << "从点 1 出发到各点的最短距离:\n";
    for (int i = 1; i <= n; ++i)
        cout << "到点 " << i << ": " << (dist[i] == INF ? "INF" : to_string(dist[i])) << "\n";
    return 0;
}
