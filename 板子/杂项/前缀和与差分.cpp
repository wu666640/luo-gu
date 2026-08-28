// 前缀和与差分 — 一维前缀和 O(1) 区间和 + 差分数组 O(1) 区间加、O(n) 单点查询
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 100000 + 5;   // 数组最大容量

int  n;          // 元素个数（下标从 1 开始）
ll   a[MAXN];    // 原数组
ll   pre[MAXN];  // 前缀和：pre[i] = a[1] + a[2] + ... + a[i]
ll   diff[MAXN]; // 差分数组：diff[i] = a[i] - a[i-1]（约定 a[0] = 0）

// 构建前缀和，O(n)
void build_pre() {
    pre[0] = 0;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + a[i];
}

// 用前缀和 O(1) 求闭区间 [l, r] 的元素和
ll range_sum(int l, int r) {
    return pre[r] - pre[l - 1];
}

// 构建差分数组：diff[i] = a[i] - a[i-1]（a[0] = 0），O(n)
void build_diff() {
    a[0] = 0;
    diff[0] = 0;
    for (int i = 1; i <= n; i++)
        diff[i] = a[i] - a[i - 1];
}

// 差分数组 O(1)：给闭区间 [l, r] 每个元素加上 val
void range_add(int l, int r, ll val) {
    diff[l] += val;
    if (r + 1 <= n) diff[r + 1] -= val;   // 在区间右侧之外抵消，保证还原时只影响 [l, r]
}

// 从差分数组还原出每个元素（等价于单点/整体查询），O(n)
// 原理：a[i] = a[i-1] + diff[i]，结果写回 a[]
void restore() {
    a[0] = 0;
    for (int i = 1; i <= n; i++)
        a[i] = a[i - 1] + diff[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示 1：前缀和求区间和
    n = 5;
    ll initArr[6] = {0, 1, 2, 3, 4, 5};   // a[1..5] = 1,2,3,4,5
    for (int i = 1; i <= n; i++) a[i] = initArr[i];
    build_pre();
    cout << "a[2..4] 的和 = " << range_sum(2, 4) << "\n";   // 2 + 3 + 4 = 9

    // 演示 2：差分数组做区间加
    build_diff();            // 由当前 a = {1,2,3,4,5} 建立差分
    range_add(3, 5, 10);     // 给 a[3..5] 各 +10
    restore();               // 从差分还原出每个元素的值
    cout << "区间 [3,5] 加 10 后的数组：";
    for (int i = 1; i <= n; i++) {
        cout << a[i];
        if (i < n) cout << ' ';
    }
    cout << "\n";

    return 0;
}
