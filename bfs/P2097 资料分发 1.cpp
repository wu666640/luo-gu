#include <bits/stdc++.h>
using namespace std;

const int N = 100100;
vector<int> g[N];   // 邻接表
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    cout << u << ' ';            // 访问节点
    for (int v : g[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;               // n 个点，m 条边
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);       // 无向图加两条
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i);     // 处理非连通图
    return 0;
}