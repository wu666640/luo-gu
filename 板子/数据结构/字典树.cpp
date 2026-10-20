// 字典树（Trie）— 字符串 Trie（插入/查找/前缀计数/删除）+ 01-Trie（最大异或）
#include <bits/stdc++.h>
using namespace std;

/*
 * 两种字典树，骨架一模一样：把 key 拆成一位一位，沿路径边走边建节点。
 *   (1) 字符串 Trie：按字符拆，解决单词存在性 / 前缀计数 / 删除
 *   (2) 01-Trie   ：按二进制位拆（高位 -> 低位），求与 x 异或最大的数 / 最大异或对
 *
 * 三个易错点：
 *   - 节点用 vector 动态开（总节点数 = 所有 key 长度之和 + 1），别写死 MAXN
 *   - pass_count（经过该节点 = 以该路径为前缀的单词数）和 end_count（以该节点结尾的单词数）
 *     语义不同：判断"单词是否存在"看 end_count，"以 s 为前缀的单词数"看 pass_count
 *   - 多组数据必须 clear()：全局 trie 不清空，第二组会带着上一组的计数
 */

// ==================== (1) 字符串 Trie ====================
struct TrieNode {
    int next[26];      // 子节点下标，0 表示不存在（0 号节点是根，不用）
    int pass_count;    // 经过该节点的单词数 = 以该节点路径为前缀的单词数
    int end_count;     // 以该节点结尾的单词数
    TrieNode() {
        memset(next, 0, sizeof(next));
        pass_count = end_count = 0;
    }
};

vector<TrieNode> trie(1);   // 0 号节点为根

// 清空（多组数据用）
void clearTrie() { trie.assign(1, TrieNode()); }

// 插入单词，O(len)
void insertWord(const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (trie[u].next[d] == 0) {          // 没有这条边就新建节点
            trie[u].next[d] = (int)trie.size();
            trie.emplace_back();
        }
        u = trie[u].next[d];
        trie[u].pass_count++;                // 经过该节点
    }
    trie[u].end_count++;                     // 单词在此结尾
}

// 是否存在这个单词（完整匹配），O(len)
bool contains(const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (trie[u].next[d] == 0) return false;
        u = trie[u].next[d];
    }
    return trie[u].end_count > 0;
}

// 以 s 为前缀的单词数量，O(len)
int countPrefix(const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (trie[u].next[d] == 0) return 0;
        u = trie[u].next[d];
    }
    return trie[u].pass_count;
}

// 删除一个单词（不存在就返回 false）；只清理计数，不回收节点，O(len)
bool removeWord(const string& s) {
    if (!contains(s)) return false;
    int u = 0;
    for (char c : s) {
        u = trie[u].next[c - 'a'];
        trie[u].pass_count--;
    }
    trie[u].end_count--;
    return true;
}

// 说明：字母表不是 26 个小写字母时（大写/数字/任意字符），
//       把 next[26] 换成 map<int,int> 或 unordered_map<int,int>，其余逻辑不变。

// ==================== (2) 01-Trie：最大异或 ====================
struct BinaryTrie {
    static constexpr int BITS = 31;   // 支持 [0, 2^31) 的非负整数；要 2^62 就改 62（用 long long 插入）
    vector<array<int, 2>> ch;         // ch[u][b]：从 u 走 b 这条边的子节点

    BinaryTrie() { ch.push_back({0, 0}); }
    void clear() { ch.assign(1, {0, 0}); }

    // 插入非负整数 x，O(BITS)
    void insert(long long x) {
        int u = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            int d = (int)((x >> b) & 1);
            if (!ch[u][d]) { ch[u][d] = (int)ch.size(); ch.push_back({0, 0}); }
            u = ch[u][d];
        }
    }

    // 返回 trie 中与 x 异或最大的那个数（不是下标）；空树返回 -1，O(BITS)
    long long maxXor(long long x) const {
        if (ch.size() == 1) return -1;
        int u = 0;
        long long res = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            int d = (int)((x >> b) & 1);
            int want = d ^ 1;                  // 想走相反位，异或后这一位才是 1
            if (ch[u][want]) { res |= 1LL << b; u = ch[u][want]; }
            else u = ch[u][d];                 // 只能走相同位
        }
        return res;
    }
    // 应用：最大异或对 = 把每个数都查一遍 maxXor 取最大；
    //       洛谷 P4551「最长异或路径」= 先求根到每点的异或和，再对这些值求最大异或对
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ---------- (1) 字符串 Trie ----------
    vector<string> words = {"apple", "apply", "app", "application", "banana"};
    for (const string& w : words) insertWord(w);

    cout << "contains(\"apple\")   = " << contains("apple") << " (应为 1)\n";
    cout << "contains(\"appl\")    = " << contains("appl") << " (应为 0：appl 只是前缀，不是单词)\n";
    cout << "countPrefix(\"app\")  = " << countPrefix("app") << " (应为 4：app/apple/apply/application)\n";
    cout << "countPrefix(\"appl\") = " << countPrefix("appl") << " (应为 3)\n";
    cout << "countPrefix(\"ban\")  = " << countPrefix("ban") << " (应为 1)\n";
    cout << "removeWord(\"app\")   = " << removeWord("app")
         << "，之后 countPrefix(\"app\") = " << countPrefix("app") << " (应为 1 和 3)\n";
    cout << "removeWord(\"xyz\")   = " << removeWord("xyz") << " (应为 0：本来就没有)\n";
    clearTrie();
    cout << "clearTrie() 后 countPrefix(\"app\") = " << countPrefix("app")
         << " (应为 0：多组数据必须清空)\n";

    // ---------- (2) 01-Trie：最大异或 ----------
    BinaryTrie bt;
    vector<long long> nums = {3, 10, 5, 25, 2, 8};
    for (long long x : nums) bt.insert(x);

    long long mx = 0;
    for (long long x : nums) mx = max(mx, bt.maxXor(x));
    cout << "01-Trie 最大异或对 = " << mx << " (应为 28 = 5 ^ 25)\n";
    cout << "maxXor(10)        = " << bt.maxXor(10) << " (应为 19 = 10 ^ 25)\n";
    bt.clear();
    cout << "clear() 后 maxXor(10) = " << bt.maxXor(10) << " (应为 -1：空树)\n";
    return 0;
}
