// exgcd — 扩展欧几里得算法，求 ax+by=gcd(a,b) 的一组整数解
#include <bits/stdc++.h>
using namespace std;

/*
 * 扩展欧几里得 exgcd
 * 输入 a，b；输出 x，y 使得 ax + by = gcd(a,b)。
 * 返回值是最大公约数 g。
 *
 * 原理：由欧几里得 gcd(a,b)=gcd(b,a%b) 递归。
 * 设下一层已求出 bx' + (a%b)y' = g，
 * 而 a%b = a - (a/b)*b，代入可得：
 *   bx' + (a - (a/b)*b)y' = g
 *   整理得 a*y' + b*(x' - (a/b)*y') = g
 * 所以本层解为 x = y'，y = x' - (a/b)*y'。
 *
 * 时间复杂度：O(log min(a,b))。
 * 说明：求得的只是一组特解，通解为
 *   x + k*(b/g)，y - k*(a/g)（k 为任意整数）。
 */
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long g = exgcd(b, a % b, y, x); // 交换并递归：下一层 x'=y, y'=x
    y -= (a / b) * x;                    // 调整本层 y
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：解 3x + 7y = 1
    long long a = 3, b = 7, x, y;
    long long g = exgcd(a, b, x, y);
    cout << "gcd(3,7) = " << g << "\n";
    cout << "x = " << x << ", y = " << y << "\n";
    cout << "验证: 3*" << x << " + 7*" << y << " = "
         << (a * x + b * y) << "\n";  // 期望输出 1
    return 0;
}
