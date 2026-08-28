// BFS — 网格广度优先搜索，求起点到终点的最短步数（'.' 为通道，'#' 为障碍）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int n, m;                              // 网格行数、列数
char grid[MAXN][MAXN];               // 网格
int dist[MAXN][MAXN];                 // 到起点的最短步数，-1 表示未访问
const int dx[4] = {-1, 1, 0, 0};      // 上下左右
const int dy[4] = {0, 0, -1, 1};      // 上下左右

// BFS：从 (sx, sy) 出发求到 (ex, ey) 的最短步数，不可达返回 -1。
// 网格无边权且每步代价为 1，BFS 按层扩展，首次到达即为最短。
int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, -1, sizeof(dist));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == ex && y == ey) return dist[x][y]; // 到达终点
        for (int k = 0; k < 4; ++k) {              // 尝试四个方向
            int nx = x + dx[k], ny = y + dy[k];
            // 越界、撞墙、已访问的都跳过
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;         // 步数 +1
            q.push({nx, ny});
        }
    }
    return -1; // 无法到达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：5x5 小网格，起点 (0,0)，终点 (4,4)
    n = 5; m = 5;
    vector<string> g = {
        ". . . # .",
        "# . . . .",
        ". # . # .",
        ". . . . .",
        ". # . . ."
    };
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            grid[i][j] = g[i][j * 2]; // 每行以空格分隔，取第 2j 个字符

    cout << "网格(" << n << "x" << m << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << grid[i][j] << ' ';
        cout << "\n";
    }
    int step = bfs(0, 0, 4, 4);
    if (step == -1) cout << "起点无法到达终点\n";
    else cout << "起点(0,0)到终点(4,4)最短步数: " << step << "\n";
    return 0;
}
