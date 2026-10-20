// 欧拉函数 — 单点 φ(n) 试除法 + 线性筛求 φ[1..N]（互质计数、欧拉定理）
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * 欧拉函数 φ(n)：1..n 中与 n 互质的数的个数。
 *   φ(1) = 1；n = p1^e1 * p2^e2 * ... 时 φ(n) = n * prod(1 - 1/pi)
 *
 * 两条常用结论：
 *   欧拉定理：gcd(a, m) = 1 => a^φ(m) ≡ 1 (mod m)
 *   逆元：gcd(a, m) = 1 => a^{-1} ≡ a^(φ(m)-1) (mod m)（m 是素数时就是费马小定理）
 */

// 单点 φ(n)：O(sqrt n)
ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; ++p) {
        if (n % p) continue;
        res = res / p * (p - 1);        // 先除后乘，避免溢出
        while (n % p == 0) n /= p;
    }
    if (n > 1) res = res / n * (n - 1); // 剩下一个大质因子
    return res;
}

// 线性筛求 φ[1..N]：O(N)，顺便得到素数表（phi[i*p] 的两条转移是经典考点）
vector<int> phiSieve(int N) {
    vector<int> phi(N + 1, 0), primes;
    vector<bool> comp(N + 1, false);
    if (N >= 1) phi[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!comp[i]) { primes.push_back(i); phi[i] = i - 1; }
        for (int p : primes) {
            if ((ll)i * p > N) break;
            comp[i * p] = true;
            if (i % p == 0) { phi[i * p] = phi[i] * p; break; } // p 是 i 的最小质因子
            phi[i * p] = phi[i] * (p - 1);
        }
    }
    return phi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "phi(1)  = " << phi(1) << "   (应为 1)\n";
    cout << "phi(12) = " << phi(12) << "   (应为 4: 1,5,7,11)\n";
    cout << "phi(36) = " << phi(36) << "  (应为 12)\n";
    cout << "phi(97) = " << phi(97) << "  (应为 96，97 是素数)\n";

    int N = 10;
    vector<int> ph = phiSieve(N);
    cout << "phi[1.." << N << "] = ";
    for (int i = 1; i <= N; ++i) cout << ph[i] << " \n"[i == N];
    cout << "(应为 1 1 2 2 4 2 6 4 6 4)\n";
    return 0;
}
