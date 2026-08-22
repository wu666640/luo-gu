//https://www.luogu.com.cn/problem/P1162
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
int a[35][35];
bool visited[35][35];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void dfs(int x,int y){
    visited[x][y] = true;
    for(int i =0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx<0 || nx>n+1 || ny<0 || ny>n+1) continue;
        if(visited[nx][ny]||a[nx][ny]==1) continue;
        dfs(nx,ny);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    
    dfs(0,0);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(visited[i][j]){
                cout<<0<<" ";
            }
            else if(a[i][j]==1){
                cout<<1<<" ";
            }
            else{
                cout<<2<<" ";
            }
        }
        cout<<endl;
    }

    return 0;
}
//同理bfs也可以