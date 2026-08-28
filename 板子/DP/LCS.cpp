// LCS — 最长公共子序列：O(n*m) 二维 DP
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
char s1[MAXN], s2[MAXN]; // 两个序列（下标从 1 开始）
int f[MAXN][MAXN];       // f[i][j]：s1[1..i] 与 s2[1..j] 的 LCS 长度

/*
 * 最长公共子序列 LCS（O(n * m)）。
 * 状态：f[i][j] 表示 s1 的前 i 个字符与 s2 的前 j 个字符的 LCS 长度。
 * 转移方程（按最后一个字符是否相等分类）：
 *   f[i][j] = f[i-1][j-1] + 1                 （s1[i] == s2[j]，匹配）
 *           = max(f[i-1][j], f[i][j-1])       （不匹配，取删除一方的最优）
 * 边界：f[0][*] = f[*][0] = 0。
 * 复杂度：O(n * m)，空间 O(n * m)。
 * 若只需长度可用滚动数组优化空间为 O(min(n,m))。
 */
int lcs(int n, int m) {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (s1[i] == s2[j]) f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        }
    return f[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：求两个字符串的 LCS 长度
    string a = "abcde", b = "ace";
    int n = (int)a.size(), m = (int)b.size();
    for (int i = 1; i <= n; ++i) s1[i] = a[i - 1];
    for (int i = 1; i <= m; ++i) s2[i] = b[i - 1];

    cout << "LCS 长度：" << lcs(n, m) << '\n'; // "ace" -> 3
    return 0;
}
