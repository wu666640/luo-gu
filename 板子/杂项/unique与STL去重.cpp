// unique与去重 — sort+unique+erase 三步走，unique 的真实语义与四种搭配
#include <bits/stdc++.h>
using namespace std;

/*
 * std::unique(first, last) 的真实语义（最容易用错的地方）：
 *   它只处理【相邻】的重复元素：把要留下的元素依次挪到前面，返回「新逻辑结尾」的迭代器。
 *   **它既不删除元素，也不改变容器大小** —— 必须自己 erase，否则尾巴上还留着垃圾数据。
 *   推论：
 *     - 要全局去重，必须先 sort（否则只能去掉连续重复）；
 *     - 只想去掉「连续重复」（如字符串压缩），就【不要】sort。
 *
 * 四种常用搭配：
 *   1) 全局去重        ：sort -> unique -> erase                 O(n log n)
 *   2) 只求不同元素个数 ：sort -> unique(...) - begin()（不用 erase）O(n log n) 时间、无额外拷贝
 *   3) 消除连续重复    ：不 sort，直接 unique -> erase            O(n)（字符串压缩）
 *   4) 带谓词去重      ：unique(b, e, pred)，如「绝对值相同」算重复
 *
 * 配套：
 *   - 去重后数组天然有序 -> 直接 lower_bound/upper_bound 二分、查排名
 *   - 离散化就是 sort + unique + lower_bound 的组合，见 杂项/离散化.cpp
 */

// 1) 全局去重（原地）
template <class T>
void dedup(vector<T>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

// 2) 只数「不同元素个数」，不改动传入的数组（按值拷贝一份排序）
template <class T>
int distinctCount(vector<T> v) {
    sort(v.begin(), v.end());
    return (int)(unique(v.begin(), v.end()) - v.begin());
}

// 3) 消除连续重复的字符（字符串压缩："aaabbc" -> "abc"）
string compress(const string& s) {
    string t = s;
    t.erase(unique(t.begin(), t.end()), t.end());
    return t;
}

// 4) 带谓词：绝对值相同的只留一个（先按 |x| 排序让同组相邻）
//    用 stable_sort 保证每组保留「原顺序里第一个」，结果才可预期
vector<int> dedupByAbs(vector<int> v) {
    stable_sort(v.begin(), v.end(), [](int a, int b) { return abs(a) < abs(b); });
    v.erase(unique(v.begin(), v.end(), [](int a, int b) { return abs(a) == abs(b); }), v.end());
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 1) 全局去重
    vector<int> v = {3, 1, 3, 2, 1, 3};
    dedup(v);
    cout << "去重后 -> ";
    for (int x : v) cout << x << " ";
    cout << " (应为 1 2 3)\n";

    // 2) 不同元素个数
    cout << "distinctCount({3,1,3,2,1,3}) = " << distinctCount(vector<int>{3, 1, 3, 2, 1, 3})
         << " (应为 3)\n";

    // 3) unique 不 erase 会怎样：元素个数不变，只有「逻辑结尾」提前
    vector<int> raw = {1, 1, 2, 3, 3, 3, 4};
    auto it = unique(raw.begin(), raw.end());
    cout << "unique 后 size = " << raw.size() << "，逻辑结尾下标 = " << (it - raw.begin())
         << " (应为 7 和 4)\n";
    raw.erase(it, raw.end());
    cout << "再 erase 后 size = " << raw.size() << "，内容 = ";
    for (int x : raw) cout << x << " ";
    cout << " (应为 4 和 1 2 3 4)\n";

    // 4) 字符串压缩（不排序，只去连续重复）
    cout << "compress(\"aaabbc\") -> \"" << compress("aaabbc") << "\" (应为 \"abc\")\n";

    // 5) 带谓词去重（按绝对值）
    vector<int> w = dedupByAbs({-3, 1, 3, -1, 2});
    cout << "dedupByAbs({-3,1,3,-1,2}) -> ";
    for (int x : w) cout << x << " ";
    cout << " (应为 1 2 -3：每组 |x| 只留原序第一个)\n";

    // 6) 去重 + 二分的搭配
    vector<int> q = {5, 3, 5, 1};
    dedup(q);
    cout << "去重后 q -> ";
    for (int x : q) cout << x << " ";
    cout << "；lower_bound(q, 3) 下标 = " << (lower_bound(q.begin(), q.end(), 3) - q.begin())
         << " (应为 1 3 5；下标 1)\n";
    return 0;
}
