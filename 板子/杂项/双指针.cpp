// 双指针/滑动窗口 — 「元素和 <= k 的最长子数组」+ 有序数组两数之和
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 滑动窗口：正整数数组 a，求「元素和 <= k」的最长子数组长度
// 复杂度：O(n)，每个元素至多进窗口一次、出窗口一次
int longest_subarray_sum_le_k(const vector<int>& a, int k) {
    int  n = (int)a.size();
    int  l = 0, best = 0;
    ll   cur = 0;                       // 当前窗口 [l, r] 的元素和
    for (int r = 0; r < n; r++) {
        cur += a[r];                    // 右端点右移，把 a[r] 加入窗口
        while (cur > k) {               // 和超出 k，左端点右移收缩窗口
            cur -= a[l];
            ++l;
        }
        best = max(best, r - l + 1);    // 更新当前窗口长度
    }
    return best;
}

// 两数之和：在【有序】数组 a 中找和为 target 的两个下标（返回 {i, j}，无解返回 {-1,-1}）
// 复杂度：O(n)
pair<int, int> two_sum(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        int s = a[l] + a[r];
        if (s == target) return {l, r};
        else if (s < target) ++l;   // 和太小，让左指针右移增大和
        else                 --r;   // 和太大，让右指针左移减小和
    }
    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示 1：滑动窗口 —— 和 <= 8 的最长子数组
    {
        vector<int> a = {1, 3, 2, 5, 1, 1, 4, 2};
        int k = 8;
        cout << "和 <= 8 的最长子数组长度 = "
             << longest_subarray_sum_le_k(a, k) << "\n";
        // 最优区间为 [1,1,4,2]，长度 4
    }

    // 演示 2：两数之和（数组必须有序）
    {
        vector<int> b = {1, 3, 5, 7, 9};
        int target = 12;
        auto p = two_sum(b, target);
        cout << "两数之和为 12 的下标：" << p.first << " " << p.second << "\n";
        // 3 + 9 = 12 → 下标 1 和 4
    }

    return 0;
}
