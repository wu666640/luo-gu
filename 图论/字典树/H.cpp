#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct TrieNode{
    int next[52];
    int less_count;
    int end_count;
    TrieNode(){
        memset(next,0,sizeof(next));
        less_count = end_count = 0;
    }
};

vector<TrieNode>Trie(1);

void insert(const string& s){
    int u = 0;
    for(char c : s){
        int d = (c >= 'a') ? (c - 'a') : (c - 'A' + 26);
        if(Trie[u].next[d] == 0){
            Trie[u].next[d] = (int)Trie.size();
            Trie.emplace_back();
        }
        u = Trie[u].next[d];
        Trie[u].less_count++;
    }
    Trie[u].end_count++;
}

bool dfs(int u, int depth, int& total_edges, int& max_depth) {
    bool has = (Trie[u].end_count > 0);
    if (has) max_depth = max(max_depth, depth);

    for (int i = 0; i < 52; ++i) {
        int v = Trie[u].next[i];
        if (v) {
            if (dfs(v, depth + 1, total_edges, max_depth)) {
                has = true;
                total_edges++; 
            }
        }
    }
    return has;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<string>vec(n);
    for(int i=0;i<n;i++){
        cin>>vec[i];
    }

    for(const auto& word : vec){
        insert(word);
    }

    int total_edges = 0, max_depth = 0;
    dfs(0, 0, total_edges, max_depth);
    ll ans = 2LL * total_edges - max_depth;
    cout<<ans<<'\n';
    return 0;
}
