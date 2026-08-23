//https://www.luogu.com.cn/problem/P1216
#include <bits/stdc++.h>
using namespace std;

const int MAXN =1005;
int a[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int r;
    cin>>r;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=i;j++){
            cin>>a[i][j];
        }
    }

    for(int i=r;i>=1;i--){
        for(int j=1;j<=i;j++){
            if(i==r) dp[i][j]=a[i][j];
            else
            dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+a[i][j];
        }
    }
    cout<<dp[1][1]<<endl;
    return 0;
}