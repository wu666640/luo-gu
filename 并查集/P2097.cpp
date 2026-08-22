#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int fa[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);   // 路径压缩
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    if (n == 0) { cout << 0 << '\n'; return 0; }

    for (int i = 1; i <= n; i++) fa[i] = i;

    for (int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        int x = find(p), y = find(q);
        if (x != y) fa[x] = y;      // 合并：把两台电脑连入同一连通块
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i) ans++;    // 根节点个数 = 连通块个数
    cout << ans << '\n';
    return 0;
}