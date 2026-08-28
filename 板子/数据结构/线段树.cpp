// 线段树 — 单点修改 + 区间求和（另附懒标记版：区间加 + 区间求和）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

// ============ 基础版：单点修改 + 区间求和 ============
// tree[x] 存储节点 x 所代表区间的和
int tree[MAXN * 4];  // 4 倍空间足够容纳所有节点
int arr[MAXN];       // 原数组，1-indexed

// 建树：递归区间 [l, r]，节点编号 p
// 复杂度：O(n)
void build(int p, int l, int r) {
    if (l == r) {                 // 叶子节点
        tree[p] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);        // 左子节点
    build(p << 1 | 1, mid + 1, r);// 右子节点
    tree[p] = tree[p << 1] + tree[p << 1 | 1];  // 左右子树之和
}

// 单点修改：把下标 pos 的值改为 val，从根向下更新路径
// 复杂度：O(log n)
void update(int p, int l, int r, int pos, int val) {
    if (l == r) {                 // 找到目标叶
        tree[p] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(p << 1, l, mid, pos, val);
    else            update(p << 1 | 1, mid + 1, r, pos, val);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];  // 回溯更新
}

// 区间求和：求 [ql, qr] 的和，递归覆盖查询区间
// 复杂度：O(log n)
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];        // 当前区间被完全覆盖
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query(p << 1, l, mid, ql, qr);    // 左区间有交集
    if (qr > mid)  res += query(p << 1 | 1, mid + 1, r, ql, qr);  // 右区间有交集
    return res;
}

// ============ 懒标记版：区间加 + 区间求和 ============
// lazy[x] 表示节点 x 的区间上还有多少"未下传"的加值
long long lazy[MAXN * 4];   // 懒标记（用 long long 防溢出）
long long seg[MAXN * 4];    // 区间和

// 下传懒标记：把 lazy[p] 分给左右子节点，并清空自身
void pushDown(int p, int l, int r) {
    if (lazy[p] == 0) return;
    int mid = (l + r) >> 1;
    // 左子节点长度 mid-l+1，右子节点长度 r-mid
    lazy[p << 1]     += lazy[p];
    seg[p << 1]      += lazy[p] * (mid - l + 1);
    lazy[p << 1 | 1] += lazy[p];
    seg[p << 1 | 1]  += lazy[p] * (r - mid);
    lazy[p] = 0;   // 标记已下传
}

// 建树（懒标记版）：初始化为 arr
void buildLazy(int p, int l, int r) {
    lazy[p] = 0;
    if (l == r) { seg[p] = arr[l]; return; }
    int mid = (l + r) >> 1;
    buildLazy(p << 1, l, mid);
    buildLazy(p << 1 | 1, mid + 1, r);
    seg[p] = seg[p << 1] + seg[p << 1 | 1];
}

// 区间加：给 [ql, qr] 每个数加上 val
// 复杂度：O(log n)
void rangeAdd(int p, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {                 // 完全覆盖，打懒标记即可
        seg[p] += val * (r - l + 1);
        lazy[p] += val;
        return;
    }
    pushDown(p, l, r);                        // 有交集才先下传
    int mid = (l + r) >> 1;
    if (ql <= mid) rangeAdd(p << 1, l, mid, ql, qr, val);
    if (qr > mid)  rangeAdd(p << 1 | 1, mid + 1, r, ql, qr, val);
    seg[p] = seg[p << 1] + seg[p << 1 | 1];
}

// 区间求和（懒标记版）
// 复杂度：O(log n)
long long rangeSum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[p];
    pushDown(p, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) res += rangeSum(p << 1, l, mid, ql, qr);
    if (qr > mid)  res += rangeSum(p << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：建树、单点修改、区间求和
    int n = 6;
    int data[6] = {1, 3, 5, 7, 9, 11};
    for (int i = 1; i <= n; ++i) arr[i] = data[i - 1];

    build(1, 1, n);
    cout << "基础版区间和:" << endl;
    cout << "query(2,5) = " << query(1, 1, n, 2, 5) << " (应为 3+5+7+9=24)" << endl;

    update(1, 1, n, 3, 10);   // 把 a[3] 改为 10
    cout << "把 a[3] 改为 10 后 query(1,4) = " << query(1, 1, n, 1, 4)
         << " (应为 1+3+10+7=21)" << endl;

    // 懒标记版：区间加 + 区间求和
    cout << "\n懒标记版（区间加 + 区间求和）:" << endl;
    buildLazy(1, 1, n);
    rangeAdd(1, 1, n, 2, 4, 2);    // 给 a[2..4] 各 +2
    cout << "rangeAdd(2,4,+2) 后 rangeSum(1,5) = " << rangeSum(1, 1, n, 1, 5)
         << " (应为 (1+3+5+7+9)+(2*3)=31)" << endl;
    rangeAdd(1, 1, n, 1, 6, -1);   // 再给全部各 -1
    cout << "rangeAdd(1,6,-1) 后 rangeSum(1,6) = " << rangeSum(1, 1, n, 1, 6)
         << " (应为 36，即第一次后数组为 1,5,7,9,9,11 和 42，再整体 -1 得 42-6=36)" << endl;

    return 0;
}
