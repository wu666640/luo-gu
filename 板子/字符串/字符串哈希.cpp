// 字符串哈希 — 滚动哈希（无符号自然溢出），快速判断两个子串是否相等
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

// 字符串哈希结构体。
// 原理：把字符串看作 base 进制的大整数；这里用 unsigned long long 自然溢出，
// 相当于自动对 2^64 取模，避免手动写模运算。由前缀哈希 h[i] 可 O(1) 求任意子串 [l, r) 的哈希。
// 若想进一步降低冲突概率，可额外用一个大质数（如 1e9+7）做第二哈希。
struct StrHash {
    int n;
    vector<ull> h;   // h[i]：s[0..i-1] 的哈希
    vector<ull> pw;  // pw[i]：base 的 i 次方
    StrHash(const string& s, ull base) {
        n = (int)s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            h[i + 1] = h[i] * base + (ull)(s[i] - 'a' + 1); // 字符映射为 1..26
            pw[i + 1] = pw[i] * base;
        }
    }
    // 返回子串 s[l..r) 的哈希
    ull get(int l, int r) const {
        return h[r] - h[l] * pw[r - l];
    }
    // 判断两个子串 s[l1..r1) 与 s[l2..r2) 是否相等
    bool equal(int l1, int r1, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false; // 长度不同必然不等
        return get(l1, r1) == get(l2, r2);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s = "banana"; // 演示：比较字符串中两个子串是否相等
    string base = "abcdefghijklmnopqrstuvwxyz";
    cout << "字符串: " << s << "\n";

    const ull BASE = 131;          // 常用进制
    StrHash hash(s, BASE);

    // 比较 s[0..2) = "ban" 与 s[3..6) = "ana"（应不等）
    cout << "子串[0,3)=\"" << s.substr(0, 3) << "\" 与 [3,6)=\"" << s.substr(3, 3)
         << "\" 是否相等: " << (hash.equal(0, 3, 3, 6) ? "是" : "否") << "\n";
    // 比较 s[1..4) = "ana" 与 s[3..6) = "ana"（应相等）
    cout << "子串[1,4)=\"" << s.substr(1, 3) << "\" 与 [3,6)=\"" << s.substr(3, 3)
         << "\" 是否相等: " << (hash.equal(1, 4, 3, 6) ? "是" : "否") << "\n";
    return 0;
}
