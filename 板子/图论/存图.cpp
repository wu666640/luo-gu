// 存图 — 邻接表存图：vector<pair> 邻接表 与 链式前向星(head/ver/next) 两种风格
#include <bits/stdc++.h>
using namespace std;

/*
 * 两种常用存图方式对比：
 * （1）vector<pair<int,int>> 邻接表 —— 写法简单、易遍历、易扩展（可加额外信息），
 *       适合边数较大且遍历次数多的场合；常数略大，但通常足够。
 * （2）链式前向星（head/ver/next） —— 用静态数组模拟链表，常数小、内存连续，
 *       适合边数大、卡时间的场合；经典竞赛写法，需要手动加边函数。
 * 本文件演示两种风格，均读入同一张带权小图并输出边长。
 */

const int MAXN = 1005;
const int MAXM = 2005; // 无向图边数 = 2 * 输入边数，这里留足余量

// ---------- 风格一：vector<pair<int,int>> 邻接表 ----------
// table[u] 中每个元素为 (v, w)，表示 u--v 有一条权为 w 的边
struct Adj {
    vector<pair<int,int>> table[MAXN];
    void addEdge(int u, int v, int w) { table[u].push_back({v, w}); }
    // 遍历 u 的所有出边：for (auto [v,w] : table[u]) ...
};

// ---------- 风格二：链式前向星 ----------
struct ForwardStar {
    int head[MAXN];   // head[u] 指向 u 的第一条边的下标，-1 表示没有边
    int ver[MAXM];    // ver[i] 第 i 条边指向的点 v
    int nxt[MAXM];    // nxt[i] 第 i 条边的下一条边（同一起点的下一条）
    int w[MAXM];      // w[i] 第 i 条边的权
    int tot;          // 当前已加的边数（边下标从 0 开始）

    void init(int n) {
        tot = 0;
        for (int i = 1; i <= n; ++i) head[i] = -1; // 用 -1 表示空
    }
    // 加一条有向边 u->v，权为 w。若要无向，则再倒着加一条 v->u。
    void addEdge(int u, int v, int val) {
        ver[tot] = v;
        w[tot]   = val;
        nxt[tot] = head[u]; // 头插法，新边插到最前面
        head[u]  = tot++;
    }
    // 遍历 u 的所有出边：for (int e = head[u]; e != -1; e = nxt[e]) ...
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：读入一张带权小图并分别用两种存图方式输出每条边
    // 输入格式：
    //   第一行 n m（点数、边数，无向图）
    //   接下来 m 行：u v w
    int n, m;
    cin >> n >> m;

    Adj a;                 // 邻接表
    ForwardStar fs;        // 链式前向星
    fs.init(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        a.addEdge(u, v, w);  // 邻接表加一条（此处按无向演示可双向加）
        a.addEdge(v, u, w);
        fs.addEdge(u, v, w); // 链式前向星同理加双向
        fs.addEdge(v, u, w);
    }

    // 输出风格一：邻接表
    cout << "--- 邻接表 (vector<pair>) ---\n";
    for (int u = 1; u <= n; ++u) {
        cout << u << ":";
        for (auto [v, w] : a.table[u]) cout << " -> (" << v << ", " << w << ")";
        cout << "\n";
    }

    // 输出风格二：链式前向星
    cout << "--- 链式前向星 (head/ver/next) ---\n";
    for (int u = 1; u <= n; ++u) {
        cout << u << ":";
        for (int e = fs.head[u]; e != -1; e = fs.nxt[e])
            cout << " -> (" << fs.ver[e] << ", " << fs.w[e] << ")";
        cout << "\n";
    }
    return 0;
}
