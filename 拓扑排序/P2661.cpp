#include<bits/stdc++.h>
using namespace std;
const int N = 2e5;
int edge[N],indegree[N];
bool loop[N];
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>edge[i];
        indegree[edge[i]]++;
    }
    
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(indegree[i] == 0) q.push(i);
        loop[i] = true;
    }

    while(!q.empty()){
        int u = q.front();  q.pop();
        loop[u] = false;
        int v = edge[u];
        if(--indegree[v] == 0) q.push(v);
    }

    int ans = 1e9;
    for(int i=1;i<=n;i++){
        if(loop[i]) {
            int cur = i,len = 0;
            while(loop[cur]){
                loop[cur] = false;
                cur = edge[cur];
                len++;
            }
            ans = min(ans,len);
        }
    }
    cout<<ans<<'\n';
    return 0;
}