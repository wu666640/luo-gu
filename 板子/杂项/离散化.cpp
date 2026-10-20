// 离散化 — 把大范围/负数数值压缩成 1..k 的排名（配树状数组、离线、逆序对）
#include <bits/stdc++.h>
using namespace std;

/*
 * 离散化：只关心元素之间的大小关系时，把数值映射成「排名」。
 *   例：{5, 1, 9, 3, 3} -> {3, 1, 4, 2, 2}
 *   重复元素得到相同排名；排名从 1 开始，方便直接当树状数组/线段树的下标。
 *   复杂度 O(n log n)。
 * 典型场景：值域 1e9 但只有 1e5 个数（前缀和、树状数组、离线排序）。
 */

// 返回 a 的排名数组，排名范围 1..k（k 为不同值的个数）
vector<int> compress(const vector<int>& a) {
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end()); // 去重后 b 即「值域」
    vector<int> r(a.size());
    for (size_t i = 0; i < a.size(); ++i)
        r[i] = (int)(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) + 1;
    return r;
}

// ---------- 应用：树状数组求逆序对 ----------
// 逆序对：满足 i < j 且 a[i] > a[j] 的 (i, j) 个数。
// 做法：把 a 离散化后，从右往左扫，用 BIT 统计「右边已出现且严格小于 a[i]」的个数。
struct BIT {
    int n;
    vector<int> t;
    explicit BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, int v) { for (; i <= n; i += i & -i) t[i] += v; }
    int sum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }
};

long long countInversions(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> r = compress(a);
    BIT bit(n);
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        ans += bit.sum(r[i] - 1);   // 右边比 a[i] 小的个数
        bit.add(r[i], 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int> a = {5, 1, 9, 3, 3};
    vector<int> r = compress(a);

    cout << "原数组 : ";
    for (int x : a) cout << x << ' ';
    cout << "\n离散化 : ";
    for (int x : r) cout << x << ' ';
    cout << "\n逆序对数 = " << countInversions(a)
         << " (应为 5：(5,1)(5,3)(5,3)(9,3)(9,3))\n";
    return 0;
}
