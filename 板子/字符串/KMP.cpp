// KMP — 前缀函数 next/pi + KMP 匹配，在文本串中找模式串的所有出现位置
#include <bits/stdc++.h>
using namespace std;

// 求模式串 p 的前缀函数（也叫 next 数组）。
// pi[i] 表示子串 p[0..i] 的最长「真前缀」同时也是「真后缀」的长度。
// 复杂度：O(|p|)
vector<int> get_pi(const string& p) {
    int n = (int)p.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];          // 继承上一个位置的匹配长度
        while (j > 0 && p[i] != p[j]) j = pi[j - 1]; // 失配则回退到上一个可匹配的前缀
        if (p[i] == p[j]) ++j;      // 能匹配，长度加 1
        pi[i] = j;                  // 记录当前最长公共前后缀
    }
    return pi;
}

// KMP 匹配：在文本串 t 中查找模式串 p 的所有出现位置（0 基下标）。
// 复杂度：O(|t| + |p|)
vector<int> kmp_match(const string& t, const string& p) {
    vector<int> pi = get_pi(p);
    vector<int> ans;
    int j = 0;                       // 当前已匹配的模式串长度
    for (int i = 0; i < (int)t.size(); ++i) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1]; // 失配回退
        if (t[i] == p[j]) ++j;       // 匹配成功一个字符
        if (j == (int)p.size()) {    // 匹配到完整模式串
            ans.push_back(i - j + 1); // 记录起始下标
            j = pi[j - 1];           // 回退以寻找重叠出现的模式串
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string t = "abababcabab", p = "aba"; // 演示：文本串与模式串
    cout << "文本串: " << t << "\n模式串: " << p << "\n";
    cout << "前缀函数 pi: ";
    for (int v : get_pi(p)) cout << v << ' ';
    cout << "\n模式串出现的位置(0基): ";
    vector<int> ans = kmp_match(t, p);
    if (ans.empty()) cout << "无";
    for (int pos : ans) cout << pos << ' ';
    cout << "\n";
    return 0;
}
