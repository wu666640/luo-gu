// 单调队列 — 求定长滑动窗口的最大值（窗口大小 k）
#include <bits/stdc++.h>
using namespace std;

// 用双端队列 deque 维护一个单调递减的序列，存储的是元素下标
// 队列里下标对应的值从左到右单调递减，队头始终是当前窗口最大值
// 复杂度：每个元素最多进队/出队一次，总体 O(n)
const int MAXN = 100005;
int a[MAXN];          // 原数组，1-indexed
int ans[MAXN];        // ans[i] 存储以 i 为右端点的窗口最大值

// 求所有长度为 k 的滑动窗口的最大值，窗口右端点为 i（i 从 k 到 n）
// 结果写入 ans[i]
void slidingWindowMax(int n, int k) {
    deque<int> dq;
    for (int i = 1; i <= n; ++i) {
        // 1) 弹出队尾所有值 <= 当前元素的（它们不再可能成为最大值，因为更靠前且更小）
        while (!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();
        // 2) 当前元素入队
        dq.push_back(i);
        // 3) 弹出队头中已经滑出窗口（下标 < i-k+1）的元素
        while (!dq.empty() && dq.front() < i - k + 1)
            dq.pop_front();
        // 4) 窗口形成（i >= k）时，队头即该窗口最大值
        if (i >= k)
            ans[i] = a[dq.front()];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：窗口大小为 3 的滑动窗口最大值
    int n = 8, k = 3;
    int data[9] = {0, 1, 3, -1, -3, 5, 3, 6, 7};  // a[1]..a[8]
    for (int i = 1; i <= n; ++i) a[i] = data[i];

    slidingWindowMax(n, k);

    cout << "原数组 a[1..8]:" << endl;
    for (int i = 1; i <= n; ++i)
        cout << a[i] << " \n"[i == n];

    cout << "窗口大小 k=" << k << "，各窗口最大值（窗口的右端点对应值）:" << endl;
    for (int i = k; i <= n; ++i)
        cout << "窗口[" << i - k + 1 << "," << i << "] 最大值 = " << ans[i] << endl;

    return 0;
}
