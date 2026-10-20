// 逆元 — 四种求法：费马小定理(素数模) / exgcd(任意互质模) / 线性递推 O(n) / 前缀积批量
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * 乘法逆元：满足 a * inv(a) ≡ 1 (mod m) 的 inv(a)，记作 a^{-1}。
 *   存在条件：gcd(a, m) = 1。m 是素数时，1..m-1 都有逆元（构成乘法群）。
 *   用途：模意义下的除法 -> 乘逆元；组合数 C(n,k) = n! * inv(k!) * inv((n-k)!)。
 *
 * 数学上只有两条路：
 *   (A) exgcd 解 a*x + m*y = 1          —— 任意 m，只要 gcd(a,m)=1
 *   (B) 欧拉定理 a^(φ(m)-1) mod m       —— m 为素数时退化成费马小定理 a^(m-2)
 * 工程上按「要几个逆元」分成四种写法（本文件 1~4），
 * 第五种「阶乘逆元」见 组合数与逆元.cpp（求组合数用）：
 *   1) 只求一两个，且 m 是素数           -> 费马小定理 + 快速幂，O(log m)
 *   2) m 是合数（只要 gcd(a,m)=1 就行）   -> exgcd，O(log m)
 *   3) 要求 1..n 所有数的逆元（P3811）    -> 线性递推，O(n)，正解
 *   4) 一次要一大批「任意」数的逆元       -> 前缀积 + 一次快速幂 + 后缀回推，O(n)
 */

// ---------- 1) 快速幂 + 费马小定理：m 必须是素数，O(log m) ----------
ll qpow(ll a, ll b, ll m) {
    ll res = 1 % m;                 // m = 1 时 res = 0，直接返回 0
    a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;              // 注意：m 超过 3e9 时这里会溢出，要换 __int128
        b >>= 1;
    }
    return res;
}

ll invPrime(ll a, ll m) {           // 要求 m 是素数
    return qpow(a % m, m - 2, m);   // a^(m-2) ≡ a^{-1} (mod m)
}

// ---------- 2) exgcd：m 任意（合数也行），只要 gcd(a, m) = 1 ----------
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll d = exgcd(b, a % b, y, x);   // 交换引用的紧凑写法
    y -= (a / b) * x;
    return d;
}

// 返回 a 在模 m 下的逆元；不互质（无逆元）时返回 -1
ll invExgcd(ll a, ll m) {
    ll x, y;
    ll d = exgcd(a, m, x, y);       // a*x + m*y = d
    if (d != 1) return -1;          // gcd(a, m) != 1 -> 不存在
    return (x % m + m) % m;         // 负数取模要修正回 [0, m)
}

// ---------- 3) 线性递推：求 1..n 在素数模 p 下的全部逆元，O(n) ----------
// 推导：设 p = k*i + r（k = p/i, r = p%i, 0 <= r < i），两边 mod i 得 k*i + r ≡ 0
//       => i^{-1} ≡ -k * r^{-1} (mod p)
//       => inv[i] = (p - p/i) * inv[p % i] % p     （p - p/i 恒正，省掉负数取模）
// 条件：p 是素数且 n < p（否则 inv[p % i] 可能取到 0）
vector<ll> invSieve(int n, ll p) {
    vector<ll> inv(n + 1, 0);
    if (n >= 1) inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = (p - p / i) * inv[p % i] % p;
    return inv;
}

// ---------- 4) 批量求任意 n 个数的逆元：前缀积 + 一次快速幂 + 后缀回推，O(n) ----------
// 场景：一堆互不相同的分母 a[1..n] 都要取逆元（例如期望 DP、多次除法）。
// 做法：pre[i] = a[1]*...*a[i]
//       invPre = (pre[n])^{-1}（一次快速幂/exgcd）
//       从右往左回推：a[i]^{-1} = invPre * pre[i-1]，然后 invPre *= a[i] 得到 (pre[i-1])^{-1}
// 条件：所有 a[i] 都与 m 互质（m 为素数时即 a[i] % m != 0）
// 注意：a 用 1-indexed（a[0] 占位），返回的 res 也是 1-indexed
vector<ll> invAll(const vector<ll>& a, ll m) {
    int n = (int)a.size() - 1;
    vector<ll> pre(n + 1, 1), res(n + 1, 0);
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * (a[i] % m) % m;
    ll invPre = invPrime(pre[n], m);        // m 是素数；合数模换成 invExgcd(pre[n], m)
    for (int i = n; i >= 1; --i) {
        res[i] = invPre * pre[i - 1] % m;   // a[i]^{-1} = (a[1..i])^{-1} * a[1..i-1]
        invPre = invPre * (a[i] % m) % m;   // 回推 (a[1..i-1])^{-1}
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 1) 素数模：费马小定理
    const ll P = 1000000007LL;
    ll ip = invPrime(3, P);
    cout << "费马:   3 * " << ip << " mod 1e9+7 = " << 3 * ip % P << "  (应为 1)\n";

    // 2) 合数模：exgcd（10 不是素数，照样能求）
    ll ie = invExgcd(3, 10);
    cout << "exgcd:  3 * " << ie << " mod 10 = " << 3 * ie % 10 << "  (应为 1，合数模也行)\n";
    cout << "exgcd:  inv(6, 10) = " << invExgcd(6, 10) << "  (应为 -1：gcd(6,10)=2，无逆元)\n";

    // 3) 线性递推：小素数模，方便肉眼验算
    int n = 10;
    ll p = 13;
    vector<ll> inv = invSieve(n, p);
    cout << "递推:   inv[1..10] (mod 13) = ";
    for (int i = 1; i <= n; ++i) cout << inv[i] << " \n"[i == n];
    bool ok = true;
    for (int i = 1; i <= n; ++i) ok = ok && (i * inv[i] % p == 1);
    cout << "        (应为 1 7 9 10 8 11 2 5 3 4；逐个验算 i*inv[i]%13==1 -> "
         << (ok ? "全部成立" : "有错") << ")\n";

    // 4) 前缀积批量：任意几个数一起求（这里 3,4,5 在模 7 下）
    vector<ll> a = {0, 3, 4, 5};           // 1-indexed
    vector<ll> ia = invAll(a, 7);
    cout << "批量:   inv(3,4,5) mod 7 = " << ia[1] << " " << ia[2] << " " << ia[3]
         << "  (应为 5 2 3)\n";
    bool ok2 = true;
    for (int i = 1; i <= 3; ++i) ok2 = ok2 && (a[i] * ia[i] % 7 == 1);
    cout << "        (逐个验算 a[i]*inv[i]%7==1 -> " << (ok2 ? "全部成立" : "有错") << ")\n";
    return 0;
}
