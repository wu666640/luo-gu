#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct TrieNode{
    int next[26];
    int less_count;
    int end_count;
    TrieNode(){
        memset(next,0,sizeof(next));
        less_count = end_count = 0;
    }
};

vector<TrieNode>trie(1);

void insert(const string& s){
    int u = 0;
    for(char c : s){
        int d = c -'a';
        if(trie[u].next[d] == 0){
            trie[u].next[d] = (int)trie.size();
            trie.emplace_back();
        }
        u = trie[u].next[d];
        trie[u].less_count ++;
    }
    
    trie[u].end_count++;
}

bool contains(const string& s){
    int u = 0;
    for(char c : s){
        int d = c -'a   ';
        if(trie[u].next[d] == 0) return false;
        u = trie[u].next[d];
    }
    return trie[u].end_count>0;
}

int countPrefix(const string& s){
    int u = 0;
    for(char c : s){
        int d = c -'a';
        if(trie[u].next[d] == 0) return false;
        u = trie[u].next[d];
    }
    return trie[u].less_count;
}


bool removeWord(const string&s){
    if(!contains(s)) return false;
    int u = 0;
    for(char c : s){
        int d = c -'a';
        u = trie[u].next[d];
        trie[u].less_count--;
    }
    trie[u].end_count--;
    return true;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
        // 演示：插入若干单词并查询
    vector<string> words = {"apple", "apply", "app", "application", "banana"};
    cout << "依次插入:" << endl;
    for (const auto& w : words) {
        insert(w);
        cout << "  " << w << endl;
    }

    cout << "contains(\"apple\")   = " << contains("apple") << " (应为 1)" << endl;
    cout << "contains(\"appl\")    = " << contains("appl") << " (应为 0,appl 不是完整单词)" << endl;
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