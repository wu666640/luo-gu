// string常用操作 — 查找 / 删除 / 替换 / 分割 / 大小写 / 数字互转（文本题速查）
#include <bits/stdc++.h>
using namespace std;

/*
 * std::string 速查（下标从 0 开始；s.size() 是 size_t，与 int 比较要小心符号）
 *
 * 【查找】找不到统一返回 string::npos，判断写法：if (s.find(t) != string::npos)
 *   s.find(t)      第一次出现的位置
 *   s.rfind(t)     最后一次出现的位置
 *   s.find(t, pos) 从 pos 开始找（配合循环可找全部出现位置）
 *   s.find_first_of("abc")      第一个属于该字符集合的位置
 *   s.find_first_not_of(" \t")  第一个不属于该集合的位置（去首尾空白就靠它）
 *   s.find_last_not_of(" \t")   最后一个不属于该集合的位置
 *
 * 【取子串】s.substr(pos, len)，len 省略表示一直到末尾
 *
 * 【删除】
 *   s.erase(pos, len)            按下标删一段
 *   s.erase(remove(s.begin(), s.end(), c), s.end())   删掉所有字符 c（erase-remove 惯用法）
 *   s.pop_back()                 删最后一个字符
 *
 * 【替换 / 插入 / 拼接】
 *   s.replace(pos, len, t)       把 [pos, pos+len) 换成 t
 *   s.insert(pos, t)             在 pos 处插入 t
 *   s.append(t) / s += t / s.push_back(c)
 *
 * 【其他常用】
 *   to_string / stoi / stoll / stod   数字 <-> 字符串
 *   toupper/tolower 逐个字符转换       stringstream + getline 做分割
 *   count(s.begin(), s.end(), c)      统计字符出现次数
 */

// 查找 t 在 s 中所有出现位置（不重叠）；t 为空时直接返回空，防止死循环
vector<size_t> findAll(const string& s, const string& t) {
    vector<size_t> res;
    if (t.empty()) return res;
    for (size_t p = s.find(t); p != string::npos; p = s.find(t, p + t.size()))
        res.push_back(p);
    return res;
}

// 把 s 中所有 from 替换成 to（注意：替换串里若又含 from 不会无限循环，因为下次从 p+to.size() 继续）
void replaceAll(string& s, const string& from, const string& to) {
    if (from.empty()) return;                  // 空串会死循环，直接返回
    for (size_t p = s.find(from); p != string::npos; p = s.find(from, p + to.size()))
        s.replace(p, from.size(), to);
}

// 删掉 s 中所有字符 c：erase-remove 惯用法（remove 把要留的挪到前面，再统一 erase 掉尾巴）
void eraseAll(string& s, char c) {
    s.erase(remove(s.begin(), s.end(), c), s.end());
}

// 按分隔符分割（stringstream + getline 最省事；连续分隔符会产生空串）
vector<string> split(const string& s, char delim) {
    vector<string> out;
    stringstream ss(s);
    string cur;
    while (getline(ss, cur, delim)) out.push_back(cur);
    return out;
}

// 去掉首尾空白（空格 / 制表符 / 回车换行），中间的不动
string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";                    // 全是空白
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// 大小写转换：逐字符转，比 transform + ::toupper 更省心（后者对负 char 是 UB）
string toUpper(string s) { for (char& c : s) c = (char)toupper((unsigned char)c); return s; }
string toLower(string s) { for (char& c : s) c = (char)tolower((unsigned char)c); return s; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s = "hello world hello cpp";

    // 1) 查找所有出现位置
    vector<size_t> pos = findAll(s, "hello");
    cout << "findAll(\"hello\") -> ";
    for (size_t p : pos) cout << p << " ";
    cout << " (应为 0 12)\n";

    // 2) 全部替换
    string t = s;
    replaceAll(t, "hello", "hi");
    cout << "replaceAll(hello->hi) -> \"" << t << "\" (应为 \"hi world hi cpp\")\n";

    // 3) 删掉所有某字符
    string u = "a-b-c-d";
    eraseAll(u, '-');
    cout << "eraseAll('-') -> \"" << u << "\" (应为 \"abcd\")\n";

    // 4) 按下标删除 / 插入 / 替换
    string v = "abcdef";
    v.erase(1, 3);                       // 从下标 1 起删 3 个
    cout << "erase(1,3) -> \"" << v << "\" (应为 \"aef\")\n";
    v.insert(1, "BCD");                  // 在下标 1 处插入
    cout << "insert(1,\"BCD\") -> \"" << v << "\" (应为 \"aBCDef\")\n";
    v.replace(0, 1, "A");                // 用 "A" 换掉下标 0 的 1 个字符
    cout << "replace(0,1,\"A\") -> \"" << v << "\" (应为 \"ABCDef\")\n";

    // 5) 分割
    vector<string> parts = split("1,22,333", ',');
    cout << "split(\"1,22,333\", ',') -> ";
    for (const string& p : parts) cout << "[" << p << "]";
    cout << " (应为 [1][22][333])\n";

    // 6) 大小写 + 去首尾空白
    cout << "toUpper(\"Abc-12\") -> " << toUpper("Abc-12") << " (应为 ABC-12)\n";
    cout << "trim(\"  hi \\t\") -> \"" << trim("  hi \t") << "\" (应为 \"hi\")\n";

    // 7) 数字 <-> 字符串
    int x = stoi("-42");
    string y = to_string(456);
    cout << "stoi(\"-42\") + 2 = " << x + 2 << " (应为 -40)；to_string(456) + \"!\" = " << y + "!" << " (应为 456!)\n";

    // 8) 其他查找写法
    string z = "ab12cd";
    cout << "z.find_first_of(数字) = " << z.find_first_of("0123456789") << " (应为 2)\n";
    cout << "z.find(\"xy\") == npos -> " << (z.find("xy") == string::npos) << " (应为 1)\n";
    cout << "z.substr(2,2) -> \"" << z.substr(2, 2) << "\" (应为 \"12\")\n";
    cout << "count(z, 'b') -> " << count(z.begin(), z.end(), 'b') << " (应为 1)\n";
    return 0;
}
