// 质因数分解与判素 — 试除法判素、分解质因数、枚举约数（数论题起手式）
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * 试除法三件套（n <= 1e12 都够用；n 到 1e18 要用 Miller-Rabin / Pollard-Rho）：
 *   isPrime(n)     判素，O(sqrt n)
 *   factorize(n)   分解质因数，返回 {(质因子, 指数)}，O(sqrt n)
 *   divisors(n)    枚举全部约数，由质因数分解推出
 *   divisorCount(n) 约数个数 = prod(e_i + 1)
 */

// 判素：试除到 sqrt(n)
bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll d = 2; d * d <= n; ++d)
        if (n % d == 0) return false;
    return true;
}

// 分解质因数，按质因子升序
vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> f;
    for (ll d = 2; d * d <= n; ++d) {
        if (n % d) continue;
        int c = 0;
        while (n % d == 0) { n /= d; ++c; }
        f.push_back({d, c});
    }
    if (n > 1) f.push_back({n, 1});   // 剩下的一定是 > sqrt(原 n) 的质因子
    return f;
}

// 枚举全部约数（升序）
vector<ll> divisors(ll n) {
    vector<ll> ds{1};
    for (auto [p, e] : factorize(n)) {
        int sz = (int)ds.size();
        ll pw = 1;
        for (int k = 1; k <= e; ++k) {
            pw *= p;
            for (int i = 0; i < sz; ++i) ds.push_back(ds[i] * pw);
        }
    }
    sort(ds.begin(), ds.end());
    return ds;
}

// 约数个数
ll divisorCount(ll n) {
    ll c = 1;
    for (auto [p, e] : factorize(n)) c *= (e + 1);
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n = 360;
    cout << n << " = ";
    auto f = factorize(n);
    for (size_t i = 0; i < f.size(); ++i) {
        if (i) cout << " * ";
        cout << f[i].first;
        if (f[i].second > 1) cout << "^" << f[i].second;
    }
    cout << "  (应为 2^3 * 3^2 * 5)\n";

    cout << "isPrime(97) = " << isPrime(97) << "  (应为 1)\n";
    cout << "isPrime(1)  = " << isPrime(1) << "  (应为 0)\n";
    cout << "isPrime(91) = " << isPrime(91) << "  (应为 0，91 = 7 * 13)\n";

    auto ds = divisors(n);
    cout << "360 的约数共 " << ds.size() << " 个 (应为 24)，前 8 个: ";
    for (size_t i = 0; i < ds.size() && i < 8; ++i) cout << ds[i] << ' ';
    cout << "\ndivisorCount(360) = " << divisorCount(n) << "  (应为 24)\n";
    return 0;
}
