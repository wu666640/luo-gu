// 树状数组（Fenwick / BIT）— 单点加、前缀和、区间和
#include <bits/stdc++.h>
using namespace std;

// bit[i] 维护原数组的一个区间和，区间长度为 lowbit(i)
// lowbit(x) = x & -x，即 x 二进制里最低位的 1 对应的值
const int MAXN = 100005;
int bit[MAXN];
int n;  // 元素个数

// 单点加：把下标 pos 的值加上 delta，向上更新所有包含 pos 的树状节点
// 复杂度：O(log n)
void add(int pos, int delta) {
    for (; pos <= n; pos += pos & -pos)
        bit[pos] += delta;
}

// 前缀和：求 a[1..pos] 的和，向下沿 lowbit 累加
// 复杂度：O(log n)
int sumPrefix(int pos) {
    int res = 0;
    for (; pos > 0; pos -= pos & -pos)
        res += bit[pos];
    return res;
}

// 区间和：求 a[l..r] 的和 = 前缀和(r) - 前缀和(l-1)
// 复杂度：O(log n)
int rangeSum(int l, int r) {
    return sumPrefix(r) - sumPrefix(l - 1);
}

// 由数组 a（1-indexed）建树状数组：对每个位置做一次单点加
// 复杂度：O(n log n)
void build(const vector<int>& a) {
    for (int i = 1; i <= n; ++i)
        add(i, a[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：由数组建树状数组，并查询前缀和与区间和
    vector<int> a = {0, 1, 3, 5, 7, 9, 11};  // a[0] 占位不用，有效下标 1..6
    n = (int)a.size() - 1;                    // n = 6
    build(a);

    cout << "原数组 a[1..6]:" << endl;
    for (int i = 1; i <= n; ++i)
        cout << a[i] << " \n"[i == n];

    cout << "前缀和 sumPrefix(4) = " << sumPrefix(4) << " (应为 1+3+5+7=16)" << endl;
    cout << "区间和 rangeSum(2,5) = " << rangeSum(2, 5) << " (应为 3+5+7+9=24)" << endl;

    // 单点加演示：a[3] += 10
    add(3, 10);
    cout << "add(3,10) 后 rangeSum(1,3) = " << rangeSum(1, 3) << " (应为 1+13+5=19)" << endl;

    return 0;
}
