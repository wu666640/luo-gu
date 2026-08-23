//https://www.luogu.com.cn/problem/P1037
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

bool g[10][10];
bool vis[10];

int dfs(int x){
    vis[x] = true;
    int cnt = 1;
    for(int i=0;i<10;i++){
        if(g[x][i] && !vis[i]){
            cnt += dfs(i);
        }
    }
    return cnt;
}

string mul(string a,int b){
    string res;
    int carry = 0;
    for(int i=a.size()-1;i>=0;i--){
        int tmp = (a[i]-'0')*b+carry;
        res.push_back(tmp%10+'0');
        carry = tmp/10;
    }
    while(carry){
        res.push_back(carry%10+'0');
        carry /= 10;
    }
    reverse(res.begin(),res.end());
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    string n;
    int k;
    cin>>n>>k;
    for(int i=0;i<k;i++){
        int x,y;
        cin>>x>>y;
        g[x][y] = true;
    }

    int cnt[10];
    for(int i=0;i<10;i++){
        memset(vis,0,sizeof(vis));
        cnt[i] = dfs(i);
    }
    string ans = "1";
    for(char c : n){
        ans = mul(ans, cnt[c-'0']);
    }
    cout<<ans<<endl;
    return 0;
}