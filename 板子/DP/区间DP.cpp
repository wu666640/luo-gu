// 区间DP — 区间 DP：石子合并（线性弱化版）求最小合并代价
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int INF = 0x3f3f3f3f;
int a[MAXN];       // a[i]：第 i 堆石子数
int sum[MAXN];     // 前缀和：sum[i] = a[1] + ... + a[i]
int f[MAXN][MAXN]; // f[l][r]：把第 l..r 堆合并成一堆的最小代价

/*
 * 区间 DP（石子合并，线性，只能合并相邻两堆）。
 * 状态：f[l][r] 表示把区间 [l, r] 的石子合并成一堆所需的最小代价。
 * 转移（枚举最后一步合并的分界点 k，k 属于 [l, r-1]）：
 *   f[l][r] = min_{k} ( f[l][k] + f[k+1][r] ) + sum[r] - sum[l-1]
 * 其中 sum[r] - sum[l-1] 为本区间石子总数，也就是最后一次合并的代价。
 * 边界：f[i][i] = 0（单堆已是一堆，无需代价）。
 * 枚举顺序：按区间长度 len 从小到大枚举（保证子区间先算好）。
 * 复杂度：O(n^3)，空间 O(n^2)。
 * 换成环形石子合并时，将数组复制一份拼接成长度 2n，做同样的线性合并，
 * 最后取 min_{i=1..n} f[i][i+n-1] 即可。
 */
int stoneMerge(int n) {
    // 前缀和
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    // 初始化：单堆代价 0，其余为无穷大
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) f[i][j] = (i == j) ? 0 : INF;

    for (int len = 2; len <= n; ++len) {          // 枚举区间长度
        for (int l = 1; l + len - 1 <= n; ++l) {  // 枚举左端点
            int r = l + len - 1;
            for (int k = l; k < r; ++k)           // 枚举分界点
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
            f[l][r] += sum[r] - sum[l - 1];       // 加上本次合并代价
        }
    }
    return f[1][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：4 堆石子，求最小合并代价
    int n = 4;
    int arr[] = {1, 2, 3, 4};
    for (int i = 1; i <= n; ++i) a[i] = arr[i - 1];

    cout << "最小合并代价：" << stoneMerge(n) << '\n';
    return 0;
}
