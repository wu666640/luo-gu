#include <bits/stdc++.h>
using namespace std;

// 记忆之书：左边生成/右边消除 = 在字典树上上下移动
// 只要每个单词的终止节点被走到即可。
// 最小代价 = 2 * (树中非根节点数) - 最长单词长度

struct Node {
    vector<pair<char,int>> ch;   // 每个节点的子边：(字符, 子节点下标)
};
vector<Node> trie(1);            // 0 号 = 根（空串）

// 找节点 u 沿字符 c 指向的子节点；没有返回 -1
int findChild(int u, char c) {
    for (auto& p : trie[u].ch)
        if (p.first == c) return p.second;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    long long nodeCnt = 0;   // 除根外的节点数 = 不同前缀数 E
    int maxLen = 0;          // 最长单词长度

    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int u = 0;
        for (char c : s) {
            int v = findChild(u, c);
            if (v == -1) {                     // 新前缀，需要新建节点
                v = (int)trie.size();
                trie.emplace_back();
                trie[u].ch.push_back({c, v});
                ++nodeCnt;
            }
            u = v;
        }
        maxLen = max(maxLen, (int)s.size());
    }

    cout << 2 * nodeCnt - maxLen << '\n';
    return 0;
}