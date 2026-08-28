// 矩阵快速幂 — 矩阵乘法 + 矩阵快速幂（带取模），用于计算斐波那契
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007; // 常见大素数模
const int SZ = 2;          // 矩阵维度（本题用 2 阶）; 可改为任意 N 阶

// 矩阵结构体，存 n*n 方阵（这里固定 2x2，用小写 n 表示阶数）
struct Matrix {
    ll a[SZ][SZ];
    int n; // 阶数

    // 构造：n 阶矩阵，默认清零；若传 identity 则置为单位阵
    Matrix(int _n = 2, bool identity = false) {
        n = _n;
        memset(a, 0, sizeof(a));
        if (identity) for (int i = 0; i < n; ++i) a[i][i] = 1;
    }
};

/*
 * 矩阵乘法：C = A * B (mod MOD)
 * 经典 O(n^3) 三重循环。n 为阶数。
 */
Matrix matMul(const Matrix &A, const Matrix &B) {
    Matrix C(A.n);
    for (int i = 0; i < A.n; ++i) {
        for (int k = 0; k < A.n; ++k) {
            if (A.a[i][k] == 0) continue; // 稀疏优化，可略
            for (int j = 0; j < A.n; ++j) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}

/*
 * 矩阵快速幂：计算 A^k (mod MOD)
 * 与整数快速幂同理：二进制拆分指数，结果矩阵初始为单位阵。
 * 复杂度：O(n^3 * log k)。
 */
Matrix matPow(Matrix A, ll k) {
    Matrix res(A.n, true); // 单位阵
    while (k > 0) {
        if (k & 1) res = matMul(res, A);
        A = matMul(A, A);
        k >>= 1;
    }
    return res;
}

/*
 * 用矩阵快速幂求斐波那契数 F(k)
 * F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)。
 * 递推式表现为矩阵：
 *   [F(n+1)]   = [1 1]^n   [F(1)]
 *   [F(n)  ]     [1 0]     [F(0)]
 * 取 M = [[1,1],[1,0]]，则 M^n 的第一行第一列即为 F(n+1)，
 * 第一行第二列（或第二行第一列）即为 F(n)。
 * 要求 n>=0。
 */
ll fib(ll n) {
    if (n == 0) return 0;
    Matrix M(2);
    M.a[0][0] = 1; M.a[0][1] = 1;
    M.a[1][0] = 1; M.a[1][1] = 0;
    Matrix Mn = matPow(M, n);
    return Mn.a[0][1] % MOD; // = F(n)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：输出 F(10)（模 1e9+7），期望 55
    ll k = 10;
    cout << "F(" << k << ") mod 1e9+7 = " << fib(k) << "\n";

    // 额外验证几个
    ll test[] = {0, 1, 2, 5, 20};
    for (ll x : test) {
        cout << "F(" << x << ") = " << fib(x) << "\n";
    }
    return 0;
}
