// 组合数与逆元 — 预处理阶乘与阶乘逆元，求 C(n,r) mod p（p 为大素数）
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007; // 大素数
const int MAXN = 1000000;   // n 的上限（约 1e6）

ll fact[MAXN + 1];  // fact[i] = i! mod p
ll ifact[MAXN + 1]; // ifact[i] = (i!)^{-1} mod p（i! 的逆元）

/*
 * 费马小定理快速幂：求 a^b mod p
 * 用于计算逆元：inv(a) = a^(p-2) mod p（p 为大素数）。
 */
ll qpow(ll a, ll b, ll p) {
    ll res = 1 % p;
    a %= p;
    while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

/*
 * 预处理阶乘与阶乘逆元
 * fact[0..N]，其中 fact[0]=1。
 * ifact[N]=fact[N] 的逆元，然后用 ifact[i-1]=ifact[i]*i 递推回去。
 * 复杂度：O(N + log p)。
 */
void precompute(int N) {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % MOD;
    ifact[N] = qpow(fact[N], MOD - 2, MOD);       // 用费马小定理求 N! 的逆元
    for (int i = N; i >= 1; --i) ifact[i - 1] = ifact[i] * i % MOD;
}

/*
 * 组合数 C(n,r) mod p
 * C(n,r) = n! / (r! * (n-r)!) = fact[n] * ifact[r] * ifact[n-r] (mod p)
 * 根据费马小定理，除以 r! 即乘以其逆元。
 * 要求 0 <= r <= n <= N。
 */
ll C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    precompute(MAXN);

    // 演示：输出 C(5,2) mod 1e9+7
    cout << "C(5,2) mod 1e9+7 = " << C(5, 2) << "\n"; // 10

    // 额外演示
    cout << "C(10,3) mod 1e9+7 = " << C(10, 3) << "\n"; // 120
    cout << "C(1000000,1) mod 1e9+7 = " << C(1000000, 1) << "\n"; // 1000000
    return 0;
}
