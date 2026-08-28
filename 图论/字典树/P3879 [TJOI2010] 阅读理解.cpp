//https://www.luogu.com.cn/problem/P3879
// P3879 [TJOI2010] 阅读理解 — 字典树解法
// 题意：给 n 篇文章，每篇是一行若干单词；m 次询问，每次给出一个单词，
//       输出包含该单词的所有文章编号（1-based，升序），没有则输出空行。
// 做法：把所有书的单词插入字典树，每个「单词终止节点」记录它出现在哪些文章里
//       （用 vector 记录，插入时按文章编号递增且去重，天然升序）。
//       查询时在树里走到终止节点，直接输出记录的文章编号。
#include <bits/stdc++.h>
using namespace std;

// 字典树：ch[u][c] 表示从节点 u 沿字符 c 走到哪个子节点（0 表示无）
vector<array<int, 26>> ch(1);      // 0 号节点是根
vector<vector<int>> arts(1);       // 每个节点对应的「包含该单词的文章编号」列表

// 插入单词 s，它属于文章 idx（1-based）。返回终止节点编号
int insertWord(const string& s, int idx) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (!ch[u][d]) {                    // 没有该子节点，新建
            ch.push_back({});               // 补一个新节点（各子指针清零）
            arts.push_back({});
            ch[u][d] = (int)ch.size() - 1;
        }
        u = ch[u][d];
    }
    // 去重：同一篇文章里同一个词只记一次（文章按 1..n 递增插入，故列表天然升序）
    if (arts[u].empty() || arts[u].back() != idx) arts[u].push_back(idx);
    return u;
}

// 查询单词 s 出现在哪些文章里；若不存在返回空列表
const vector<int>& queryWord(const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (!ch[u][d]) {                    // 走不下去，没这个词
            static vector<int> empty;       // 返回一个全局空列表
            return empty;
        }
        u = ch[u][d];
    }
    return arts[u];                         // 终止节点的文章列表
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ---- 读入 n 篇文章 ----
    int n;
    cin >> n;
    string line, w;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 吃掉第一行的换行
    for (int i = 1; i <= n; ++i) {
        getline(cin, line);
        stringstream ss(line);
        while (ss >> w) insertWord(w, i);   // 把这篇文章的所有单词插入
    }

    // ---- 读入 m 次询问 ----
    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int q = 0; q < m; ++q) {
        string query;
        cin >> query;
        const vector<int>& res = queryWord(query);
        if (res.empty()) {
            cout << "\n";                   // 没有文章包含该词
        } else {
            for (size_t k = 0; k < res.size(); ++k) {
                if (k) cout << ' ';
                cout << res[k];
            }
            cout << "\n";
        }
    }
    return 0;
}
