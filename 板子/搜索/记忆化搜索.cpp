// 记忆化搜索 — 带 memo 数组的递归，消除重复子问题（以斐波那契为例）
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100;
ll memo[MAXN];     // memo[i]：已算好的 f(i)，-1 表示尚未计算
bool computed[MAXN]; // 标记 f(i) 是否已计算（也可直接用 memo 初值判空）

// 记忆化求斐波那契第 n 项：f(0)=0, f(1)=1, f(n)=f(n-1)+f(n-2)。
// 朴素递归会指数级重复计算；记忆化后每个状态只算一次，复杂度 O(n)。
ll fib(int n) {
    if (n <= 1) return n;           // 边界：f(0)=0, f(1)=1
    if (computed[n]) return memo[n]; // 已算过，直接返回（这就是记忆化的核心）
    memo[n] = fib(n - 1) + fib(n - 2); // 计算并记录
    computed[n] = true;
    return memo[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：计算斐波那契第 n 项并说明记忆化如何避免重复
    memset(computed, false, sizeof(computed));
    int n = 30;
    cout << "计算斐波那契第 " << n << " 项\n";
    cout << "fib(" << n << ") = " << fib(n) << "\n";
    cout << "说明：朴素递归会重复计算大量相同的子问题（如 fib(28)、fib(29) 各被调用多次），"
            "而记忆化搜索把每个结果存入 memo，之后遇到同样参数直接用，"
            "因此总计算量从指数级降到 O(n)。\n";
    return 0;
}
