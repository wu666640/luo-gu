// Kruskal — 最小生成树 Kruskal（边按权排序 + 并查集）
#include <bits/stdc++.h>
using namespace std;

/*
 * Kruskal 最小生成树：
 *   把所有边按权值从小到大排序，依次考虑每条边 (u,v,w)，
 *   若 u、v 尚未连通（不在同一并查集），则选入生成树并合并。
 *   选到 n-1 条边即得到最小生成树；若遍历完仍不足 n-1 条，说明图不连通。
 *   复杂度 O(m log m)（主要是排序）。适用于求边权和最小的生成树。
 *   并查集用于动态判断两点是否连通，接近 O(1)。
 */

const int MAXN = 1005;

struct Edge {
    int u, v, w;
    // 按权值从小到大排序
    bool operator<(const Edge &o) const { return w < o.w; }
};
vector<Edge> edges; // 所有边

int fa[MAXN]; // 并查集父节点

// 并查集初始化
void initDSU(int n) { for (int i = 1; i <= n; ++i) fa[i] = i; }

// 查找根 + 路径压缩
int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

// 合并两集合，成功返回 true，已在同一集合返回 false
bool unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    fa[rx] = ry;
    return true;
}

// n: 点数。返回最小生成树边权和；若图不连通返回 -1。
long long kruskal(int n) {
    initDSU(n);
    sort(edges.begin(), edges.end()); // 边按权排序

    long long sum = 0;
    int cnt = 0; // 已选入的边数
    for (auto &e : edges) {
        if (unite(e.u, e.v)) {
            sum += e.w;
            if (++cnt == n - 1) break; // 选够了 n-1 条边
        }
    }
    if (cnt < n - 1) return -1; // 不连通，不存在生成树
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：一张连通带权小图，求最小生成树边权和
    // 输入：第一行 n m（点数、边数），接下来 m 行 u v w（无向边）
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    long long sum = kruskal(n);
    if (sum == -1) cout << "图不连通，没有最小生成树\n";
    else cout << "最小生成树边权和 = " << sum << "\n";
    return 0;
}
