// 线性筛素数 — 欧拉（线性）筛，求 [1,N] 内所有素数
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000; // 筛的上限（按需调整，数组用全局避免栈爆）

int primes[MAXN]; // 素数表，下标从 1 开始（或从 0 记录个数）
int primeCnt = 0; // 素数个数
bool isComp[MAXN + 1]; // isComp[i]=true 表示 i 是合数（非素数），否则为素数

/*
 * 线性筛（欧拉筛）: 求 [1,N] 内所有素数
 * 原理：从小到大枚举 i，若 i 未被标记为合数则为素数，加入表。
 *       然后用最小质因子去标记合数：枚举已有素数 p，标记 i*p，
 *       一旦 p 是 i 的最小质因子（i % p == 0）就停止。
 * 这样每个合数都会被其【最小质因子】唯一标记一次，故总复杂度 O(N)（线性）。
 *
 * 关键：isComp[i*p]=true 时，若 i%p==0 则说明 p 已经是 i 的最小质因子，
 *       更大的素数对应的 i*p 已由更小的质因子覆盖，不必再标记。
 */
void linear_sieve(int N) {
    isComp[1] = true;         // 1 不是素数
    for (int i = 2; i <= N; ++i) {
        if (!isComp[i]) primes[++primeCnt] = i; // i 是素数
        for (int j = 1; j <= primeCnt && i * primes[j] <= N; ++j) {
            isComp[i * primes[j]] = true;       // 标记 i*primes[j] 为合数
            if (i % primes[j] == 0) break;      // 最小质因子已到，停止
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：输出 100 以内所有素数
    int N = 100;
    linear_sieve(N);
    cout << "100 以内的素数 (" << primeCnt << " 个):\n";
    for (int i = 1; i <= primeCnt; ++i) {
        cout << primes[i];
        if (i < primeCnt) cout << ' ';
    }
    cout << "\n";
    return 0;
}
