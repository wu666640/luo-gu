// 字典树（Trie）— 插入、查找、统计前缀数量、删除单词
#include <bits/stdc++.h>
using namespace std;

// 每个节点：next 指向 26 个字母子节点，less_count 统计"经过该节点"的单词数，
// end_count 统计"以该节点结尾"的单词数
// 节点总数 = 单词总长度 + 1，用 vector / 数组动态分配
struct TrieNode {
    int next[26];      // 子节点下标，0 表示不存在
    int less_count;    // 以该节点为前缀的单词个数
    int end_count;     // 以该节点结尾的单词个数
    TrieNode() {
        memset(next, 0, sizeof(next));
        less_count = end_count = 0;
    }
};

vector<TrieNode> trie(1);  // 0 号节点为根

// 插入一个单词：沿路径建立节点并累加计数
// 复杂度：O(len)，len 为单词长度
void insert(const string& s) {
    int u = 0;   // 当前节点，从根出发
    for (char c : s) {
        int d = c - 'a';
        if (trie[u].next[d] == 0) {          // 没有该子节点则新建
            trie[u].next[d] = (int)trie.size();
            trie.emplace_back();
        }
        u = trie[u].next[d];
        trie[u].less_count++;                // 经过该节点，前缀计数 +1
    }
    trie[u].end_count++;                     // 单词结尾计数 +1
}

// 判断是否存在某个单词（完全匹配）
// 复杂度：O(len)
bool contains(const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (trie[u].next[d] == 0) return false;   // 路径断了
        u = trie[u].next[d];
    }
    return trie[u].end_count > 0;                 // 存在以该节点结尾的单词
}

// 统计以字符串 s 为前缀的单词数量
// 复杂度：O(len)
int countPrefix(const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (trie[u].next[d] == 0) return 0;       // 前缀不存在
        u = trie[u].next[d];
    }
    return trie[u].less_count;
}

// 删除一个单词：若能找到，则沿路径减少 less_count，并减少结尾计数
// 若删掉的节点不再被任何单词使用，这里只做计数清理（保留结构），
// 为简洁不失正确性，此处不回收节点内存
// 注意：函数命名用 removeWord，避免与 <cstdio> 里的 ::remove(const char*)（删除文件）同名冲突
// 复杂度：O(len)
bool removeWord(const string& s) {
    if (!contains(s)) return false;               // 单词不存在则无须删除
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        u = trie[u].next[d];
        trie[u].less_count--;
    }
    trie[u].end_count--;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：插入若干单词并查询
    vector<string> words = {"apple", "apply", "app", "application", "banana"};
    cout << "依次插入:" << endl;
    for (const auto& w : words) {
        insert(w);
        cout << "  " << w << endl;
    }

    cout << "contains(\"apple\")   = " << contains("apple") << " (应为 1)" << endl;
    cout << "contains(\"appl\")    = " << contains("appl") << " (应为 0，appl 不是完整单词)" << endl;
    cout << "contains(\"banana\")  = " << contains("banana") << " (应为 1)" << endl;

    cout << "countPrefix(\"app\")        = " << countPrefix("app") << " (应为 4: apple/apply/app/application)" << endl;
    cout << "countPrefix(\"appl\")       = " << countPrefix("appl") << " (应为 3: apple/apply/application)" << endl;
    cout << "countPrefix(\"ban\")        = " << countPrefix("ban") << " (应为 1: banana)" << endl;

    // 删除演示
    cout << "删除 \"app\" 后 countPrefix(\"app\") = " << (removeWord("app") ? countPrefix("app") : -1)
         << " (应为 3，删掉 app 后剩 apple/apply/application)" << endl;
    cout << "再次删除不存在的 \"xyz\" 返回 " << removeWord("xyz") << " (应为 0)" << endl;

    return 0;
}
