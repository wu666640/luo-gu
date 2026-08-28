// 并查集 — 路径压缩 + 按大小合并 的 DSU（Find / Unite / 判定连通）
#include <bits/stdc++.h>
using namespace std;

// fa[x]：x 的父节点（根节点满足 fa[x]==x）
// sz[x]：x 作为根时子树的大小（仅在根上有意义），用于按大小合并
const int MAXN = 100005;
int fa[MAXN], sz[MAXN];

// 带路径压缩的查找：返回 x 所在集合的根，并把沿途节点直接挂在根上
// 均摊复杂度：O(alpha(n))，近似常数
int find(int x) {
    if (fa[x] == x) return x;             // 自己是根
    return fa[x] = find(fa[x]);           // 路径压缩：递归找根并直接接根
}

// 初始化：每个元素自成一个集合，大小为 1
void init(int n) {
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        sz[i] = 1;
    }
}

// 合并两个元素所在的集合，返回是否发生了真正的合并
// 按大小（sz）合并：把小集合接到大集合上，避免树过深
bool unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;            // 已在同一集合，无需合并
    if (sz[rx] < sz[ry]) swap(rx, ry);     // 保证 rx 是较大的那棵
    fa[ry] = rx;                           // 把 ry 接到 rx 上
    sz[rx] += sz[ry];                      // 更新新根的大小
    return true;
}

// 判定两个元素是否连通（是否在同一集合）
bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：10 个元素，依次合并若干对，输出每个元素所在集合的根
    int n = 10;
    init(n);

    unite(1, 2);
    unite(2, 3);
    unite(4, 5);
    unite(6, 7);
    unite(7, 8);
    unite(8, 9);
    unite(3, 5);  // 把 {1,2,3} 与 {4,5} 连成 {1,2,3,4,5}

    cout << "每个元素的集合根:" << endl;
    for (int i = 1; i <= n; ++i)
        cout << i << " -> " << find(i) << (i == n ? "\n" : "\n");

    // 判定连通性演示
    cout << "same(1,4) = " << same(1, 4) << " (应为 1，同属集合)" << endl;
    cout << "same(4,9) = " << same(4, 9) << " (应为 0，不同集合)" << endl;
    cout << "same(6,10) = " << same(6, 10) << " (应为 0，不同集合)" << endl;

    return 0;
}
