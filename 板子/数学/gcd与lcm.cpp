// gcd与lcm — 欧几里得最大公约数与最小公倍数
#include <bits/stdc++.h>
using namespace std;

/*
 * 最大公约数 gcd —— 欧几里得算法（辗转相除法）
 * 原理：gcd(a,b) = gcd(b, a % b)，不断递归直到余数为 0。
 * 时间复杂度：O(log min(a,b))。
 * 参数需为正（或至少不为 0）；对 a==0 返回 |b|。
 */
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

/*
 * 最小公倍数 lcm
 * 原理：lcm(a,b) = a / gcd(a,b) * b。
 * 先除后乘避免 a*b 溢出 long long（当 a、b 很大时）。
 */
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：输出 gcd(12,18) 与 lcm(12,18)
    cout << "gcd(12,18) = " << gcd(12, 18) << "\n";   // 期望 6
    cout << "lcm(12,18) = " << lcm(12, 18) << "\n";   // 期望 36

    // 额外演示一组
    cout << "gcd(3,7) = " << gcd(3, 7) << "\n";       // 期望 1
    cout << "lcm(3,7) = " << lcm(3, 7) << "\n";       // 期望 21
    return 0;
}
