#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
vector<int> g[N];
bool visDFS[N], visBFS[N];

// 迭代 DFS（避免递归爆栈）；逆序入栈保证“编号小的先访问”
void dfs(int x) {
    stack<int> st;
    st.push(x);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visDFS[u]) continue;
        visDFS[u] = true;
        cout << u << ' ';
        for (auto it = g[u].rbegin(); it != g[u].rend(); it++) {
            if (!visDFS[*it]) st.push(*it);
        }
    }
}

void bfs(int x) {
    queue<int> q;
    q.push(x);
    visBFS[x] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << ' ';
        for (int v : g[u]) {
            if (!visBFS[v]) {
                q.push(v);
                visBFS[v] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }
    // 编号小的先访问 → 每个点的出边按编号升序
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());

    dfs(1);
    cout << '\n';
    bfs(1);
    cout << '\n';
    return 0;
}
