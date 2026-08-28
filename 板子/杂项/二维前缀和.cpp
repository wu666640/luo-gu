// 二维前缀和 — 二维前缀和 O(1) 求任意子矩阵和
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 1000 + 5;   // 单个维度最大容量

int  n, m;          // 行数、列数（均从 1 开始编号）
int  a[MAXN][MAXN]; // 原矩阵
ll   s[MAXN][MAXN]; // 二维前缀和：s[i][j] = 左上角 (1,1) 到 (i,j) 子矩阵的元素和

// 预处理二维前缀和，O(n*m)
// 容斥原理：s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j]
void build() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
}

// O(1) 求子矩阵 (x1, y1)-(x2, y2) 的和（含边界）
// 也是容斥：总面积减去左右两块，再加上被重复减去的角落
ll sub_sum(int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：3 行 4 列的矩阵，求子矩阵 (2,2)-(3,4) 的和
    n = 3;
    m = 4;
    int val[4][5] = {
        {0, 0,  0,  0,  0},
        {0, 1,  2,  3,  4},
        {0, 5,  6,  7,  8},
        {0, 9, 10, 11, 12}
    };
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = val[i][j];

    build();
    cout << "子矩阵 (2,2)-(3,4) 的和 = " << sub_sum(2, 2, 3, 4) << "\n";
    // 手算：(6+7+8) + (10+11+12) = 21 + 33 = 54

    return 0;
}
