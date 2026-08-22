// P2097 资料分发 1 —— 答案 = 连通块个数
// 每个连通块只需输入 1 台电脑，数据即可传遍全块
// 解法：DFS（迭代栈，防止 n=1e5 时递归爆栈）
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    if (n == 0) { cout << 0 << '\n'; return 0; }

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        g[p].push_back(q);
        g[q].push_back(p);          // 双向数据线
    }

    vector<char> vis(n + 1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        ans++;                      // 新发现一个连通块
        vector<int> stk;
        stk.push_back(i);
        vis[i] = 1;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            for (int v : g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    stk.push_back(v);
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}