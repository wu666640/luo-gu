//https://www.luogu.com.cn/problem/P1396
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> fa;

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a != b) fa[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.w < b.w; });

    fa.resize(n + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;

    for (const auto& e : edges) {
        unite(e.u, e.v);
        if (find(s) == find(t)) {      
            cout << e.w << '\n';
            return 0;
        }
    }


    return 0;
}