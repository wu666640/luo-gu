#include<bits/stdc++.h>
using namespace std;
using ll =long long;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin>>n>>m;

    vector<vector<ll>>g(n+1);

    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<bool>vis(n+1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        ans++;
        vector<ll>stack;
        stack.push_back(i);
        vis[i] = true;
        while(!stack.empty()){
            int u = stack.back();
            stack.pop_back();
            for(int v:g[u]){
                if(!vis[v]){
                    vis[v] = true;
                    stack.push_back(v);
                }
            }
        }
    }

    cout<<ans<<'\n';
    return 0;
}
