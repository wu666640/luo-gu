// ST 表（稀疏表 / Sparse Table）— 静态区间 RMQ，查询区间最大值
#include <bits/stdc++.h>
using namespace std;

// st[j][i]：从下标 i 开始、长度为 2^j 的区间的最大值
// 由于每行长度不同，这里用 vector 动态建表
// 复杂度：预处理 O(n log n)，单次查询 O(1)
const int MAXN = 100005;
int a[MAXN];                 // 原数组，1-indexed
vector<int> st[20];          // log2(1e5) < 17，开 20 足够
int lg[MAXN];                // lg[i] = floor(log2(i))

// 预处理：先求每个数的 log2，再逐层递推 ST 表
void buildST(int n) {
    // 预处理 log2 表
    lg[1] = 0;
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;

    // 第 0 层：长度为 1 的区间，最大值即原数组
    st[0].resize(n + 1);
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];

    // 递推：st[j][i] = max(st[j-1][i], st[j-1][i + 2^(j-1)])
    for (int j = 1; (1 << j) <= n; ++j) {
        int len = 1 << j;                 // 当前区间长度 2^j
        st[j].resize(n + 1);
        for (int i = 1; i + len - 1 <= n; ++i)
            st[j][i] = max(st[j - 1][i], st[j - 1][i + (len >> 1)]);
    }
}

// 查询区间 [l, r] 的最大值
// 取两个可重叠的长度为 2^k 的区间覆盖 [l,r]，k = floor(log2(r-l+1))
// 复杂度：O(1)
int queryMax(int l, int r) {
    int k = lg[r - l + 1];
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：对数组建 ST 表，查询若干区间最大值
    int n = 10;
    int data[12] = {0, 5, 2, 9, 3, 7, 1, 8, 6, 4, 10};  // a[1]..a[10]
    for (int i = 1; i <= n; ++i) a[i] = data[i];

    buildST(n);

    cout << "原数组 a[1..10]:" << endl;
    for (int i = 1; i <= n; ++i)
        cout << a[i] << " \n"[i == n];

    cout << "queryMax(1,10) = " << queryMax(1, 10) << " (应为 10)" << endl;
    cout << "queryMax(2,6)  = " << queryMax(2, 6) << " (应为 9，区间 2,9,3,7,1)" << endl;
    cout << "queryMax(7,9)  = " << queryMax(7, 9) << " (应为 8，区间 8,6,4)" << endl;
    cout << "queryMax(4,4)  = " << queryMax(4, 4) << " (应为 3，单点)" << endl;

    return 0;
}
