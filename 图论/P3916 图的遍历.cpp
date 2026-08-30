//反向建图dfs
#include<bits/stdc++.h>
using namespace std;
const int N = 10005;
bool vis[N];
int ans[N];
vector<int>g[N];
void bfs(int start,int col){
    queue<int>q;
    q.push(start);
    vis[start] = true; ans[start] = col;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : g[u]){
            if(!vis[v]){
                vis[v] = true;
                ans[v] = col;
                q.push(v);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    while(m--){
        int u,v;
        cin>>u>>v;
        g[v].push_back(u);
    }
    for(int i=n;i>=1;i--){
        if(!vis[i]) bfs(i,i);
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }

    return 0;
}