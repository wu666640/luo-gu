// 单调栈 — 求每个元素 左边/右边 第一个更大/更小元素
#include <bits/stdc++.h>
using namespace std;

// 用栈维护一个单调递增/递减的序列，栈中存放的是元素下标
// 复杂度：每个元素最多入栈/出栈一次，总体 O(n)
const int MAXN = 100005;
int a[MAXN];    // 原数组，1-indexed
int n;

// 求每个元素右边第一个严格更大元素的（下标），不存在则为 0
// 单调递减栈：栈底到栈顶单调递减（存下标，值递减）
// 当当前元素大于栈顶时，栈顶的"下一个更大"就是当前元素
void nextGreaterElement(int res[]) {
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && a[st.top()] < a[i]) {  // 栈顶被当前更大值弹出
            res[st.top()] = i;                        // 记录"下一个更大"下标
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) {                             // 剩余元素右侧没有更大值
        res[st.top()] = 0;
        st.pop();
    }
}

// 求每个元素左边第一个更大元素（下标），不存在则为 0
// 从左往右扫，维护单调递减栈：栈顶就是左边最近的更大者
void prevGreaterElement(int res[]) {
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && a[st.top()] < a[i]) st.pop();
        res[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }
}

// 求每个元素右边第一个更小元素（下标），不存在则为 0
// 单调递增栈：栈顶被当前更小值弹出
void nextSmallerElement(int res[]) {
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && a[st.top()] > a[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) { res[st.top()] = 0; st.pop(); }
}

// 求每个元素左边第一个更小元素（下标），不存在则为 0
void prevSmallerElement(int res[]) {
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && a[st.top()] > a[i]) st.pop();
        res[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：下一个更大元素
    n = 7;
    int data[8] = {0, 2, 1, 5, 3, 4, 6, 7};  // a[1]..a[7]
    for (int i = 1; i <= n; ++i) a[i] = data[i];

    int nge[MAXN];
    nextGreaterElement(nge);

    cout << "原数组 a[1..7]:" << endl;
    for (int i = 1; i <= n; ++i)
        cout << a[i] << " \n"[i == n];

    cout << "每个元素右边第一个更大元素(下标) : 值" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "i=" << i << " (" << a[i] << ") -> "
             << (nge[i] ? to_string(nge[i]) + " (" + to_string(a[nge[i]]) + ")" : "没有")
             << endl;
    }

    return 0;
}
