// 二分 — 有序数组二分查找 + 二分答案（对单调谓词 check(mid) 判定）
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ---- 1. 二分查找：在有序数组 a[0..n-1] 中找 >= x 的第一个位置（等价于 std::lower_bound） ----
// 复杂度：O(log n)
int lower_bound_custom(const vector<int>& a, int x) {
    int l = 0, r = (int)a.size();   // 候选答案区间 [l, r)
    while (l < r) {
        int mid = l + (r - l) / 2;  // 避免 (l+r) 溢出
        if (a[mid] >= x) r = mid;   // mid 有可能就是答案，收缩右界
        else             l = mid + 1; // mid 太小，答案必在其右侧
    }
    return l;   // 返回第一个不小于 x 的下标；若都小于 x，则返回 a.size()
}

// ---- 2. 二分答案：对单调谓词 check(mid) 二分，求最小可行 x ----
// 判定函数能否把 b 分成不超过 k 段，且每段元素和 <= x
// 单调性：x 越大越容易成立（check 随 x 单调不减，是「假的→真的」）
// 复杂度：O(n log 值域)
bool check(const vector<int>& b, ll x, int k) {
    ll  cur = 0;   // 当前段累计和
    int cnt = 1;   // 已用段数（至少 1 段）
    for (int v : b) {
        if (v > x) return false;          // 单个元素已超限，必然不可行
        if (cur + v > x) { ++cnt; cur = v; } // 超出 x，开新段
        else               cur += v;
    }
    return cnt <= k;   // 能否用不超过 k 段装下全部元素
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示 1：二分查找第一个 >= x 的下标
    {
        vector<int> a = {1, 3, 3, 5, 7, 9};
        int x = 4;
        int pos = lower_bound_custom(a, x);
        cout << "第一个 >= " << x << " 的下标 = " << pos << "，其值 = "
             << (pos < (int)a.size() ? a[pos] : -1) << "\n";
        // 下标 3，a[3] = 5
    }

    // 演示 2：二分答案——「最小化最大值」
    // 把数组分成不超过 k 段，求「各段和最大值」的最小可能值
    {
        vector<int> b = {2, 4, 1, 7, 3, 5};
        int k = 3;                 // 最多 3 段
        ll lo = 0, hi = 0;         // 答案一定在 [lo, hi] 内
        for (int v : b) {
            lo = max(lo, (ll)v);   // 至少是最大元素
            hi += v;               // 至多是全部之和（1 段）
        }
        // 找最小的可行 x。check 随 x 单调不减 → 用「向上取整的 mid」
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (check(b, mid, k)) hi = mid;   // mid 可行，尝试更小的 x
            else                 lo = mid + 1; // mid 不可行，必须更大
        }
        cout << "分成不超过 " << k << " 段时，最大段和的最小值 = " << lo << "\n";
    }

    return 0;
}
