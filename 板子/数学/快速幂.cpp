// 快速幂 — 二进制快速幂（含取模）与费马小定理求逆元
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
 * 二进制快速幂：计算 a^b mod p
 * 原理：把指数 b 按二进制拆解，base 逐次自乘（base, base^2, base^4, ...），
 *       每当 b 对应位为 1 就把当前 base 乘进答案。
 * 时间复杂度：O(log b)。
 */
ll qpow(ll a, ll b, ll p) {
    ll res = 1 % p;
    a %= p;
    while (b > 0) {
        if (b & 1) res = res * a % p; // 当前位为 1，乘进答案
        a = a * a % p;                // base 平方
        b >>= 1;                      // 指数右移一位
    }
    return res;
}

/*
 * 费马小定理求逆元
 * 当 p 为大素数且 gcd(a,p)=1 时：a^(p-1) ≡ 1 (mod p)，
 * 所以 a 的逆元为 a^(p-2) mod p。
 * 时间复杂度：O(log p)。
 */
ll inv(ll a, ll p) {
    return qpow(a, p - 2, p);
}

const ll MOD = 1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：2^10 mod 1000
    ll base = 2, exp = 10;
    cout << "2^10 mod 1000 = " << qpow(base, exp, MOD) << "\n"; // 1024 % 1000 = 24

    // 演示费马小定理求逆元：求 3 在模 1e9+7 下的逆元
    const ll PM = 1000000007LL;
    ll ainv = inv(3, PM);
    cout << "3 * inv(3) mod 1e9+7 = " << (3LL * ainv % PM) << "\n"; // 期望 1
    return 0;
}
