// LIS — 最长上升子序列：O(n logn) 用 tails + 二分；附 O(n^2) 版本注释
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int a[MAXN]; // 输入序列

/*
 * 严格最长上升子序列（O(n log n)）。
 * tails[len] 维护"所有长度为 len 的上升子序列中结尾元素的最小值"。
 * 对每个 a[i]，在 tails 中二分查找第一个 >= a[i] 的位置 pos：
 *   - 若 pos == tails.size()（a[i] 大于所有结尾），说明能延长最长上升子序列，
 *     将 a[i] 追加到尾部；
 *   - 否则用 a[i] 替换 tails[pos]（更小的结尾元素永远更优，不改变长度）。
 * 最终 tails 的长度就是 LIS 长度。
 * 复杂度：O(n log n)，空间 O(n)。
 */
int lis(int n) {
    vector<int> tails;
    for (int i = 1; i <= n; ++i) {
        auto it = lower_bound(tails.begin(), tails.end(), a[i]);
        if (it == tails.end()) tails.push_back(a[i]);
        else *it = a[i];
    }
    return (int)tails.size();
}

/*
 * O(n^2) 版本（供参考）：
 * 状态：f[i] 表示以 a[i] 结尾的最长上升子序列长度。
 * 转移：f[i] = max(1, max_{j < i 且 a[j] < a[i]} f[j] + 1)。
 * 答案：max(f[i])。复杂度 O(n^2)。
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：求序列的严格 LIS 长度
    int n = 8;
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    for (int i = 1; i <= n; ++i) a[i] = arr[i - 1];

    cout << "LIS 长度：" << lis(n) << '\n'; // 如 2,3,7,101 或 2,3,7,18 -> 4
    return 0;
}
