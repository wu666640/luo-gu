// Manacher — 马拉车算法求所有回文子串半径，用于求最长回文子串
#include <bits/stdc++.h>
using namespace std;

// 马拉车算法。
// d1[i]：以 i 为中心、长度为奇数的最长回文半径（含中心），即回文串是 s[i-d1[i]+1 .. i+d1[i]-1]。
// d2[i]：以 s[i-1] 与 s[i] 之间为中心、长度为偶数的最长回文半径，即回文串是 s[i-d2[i] .. i+d2[i]-1]。
// 复杂度：O(n)，每个字符最多被扩展一次。
void manacher(const string& s, vector<int>& d1, vector<int>& d2) {
    int n = (int)s.size();
    d1.assign(n, 0);
    d2.assign(n, 0);

    // 处理奇数长度的回文
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1); // 利用已有信息初始化长度
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k; // 向外扩展
        d1[i] = k;
        if (i + k - 1 > r) { l = i - k + 1; r = i + k - 1; }          // 更新最右回文区间
    }

    // 处理偶数长度的回文
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1); // 初始化长度
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k; // 向外扩展
        d2[i] = k;
        if (i + k - 1 > r) { l = i - k; r = i + k - 1; }                // 更新最右回文区间
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s = "aabacacaa"; // 演示：计算最长回文子串长度
    cout << "字符串: " << s << "\n";

    vector<int> d1, d2;
    manacher(s, d1, d2);

    int best = 1; // 最长回文长度至少为 1（单个字符）
    for (int i = 0; i < (int)s.size(); ++i) {
        best = max(best, 2 * d1[i] - 1); // 奇数回文：长度 = 2*d1 - 1
        best = max(best, 2 * d2[i]);     // 偶数回文：长度 = 2*d2
    }
    cout << "最长回文子串长度: " << best << "\n";
    return 0;
}
