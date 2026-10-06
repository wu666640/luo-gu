#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//费马小定理 mod为素数时
ll mod;
ll qpow(ll base,ll exp){
    ll res=1;
    base%=mod;
    while(exp>0){
        if(exp&1) res=res*base%mod;
        base = base*base%mod;
        exp>>1;
    }
}

ll inv(ll a,ll mod){
    return qpow(a,mod-2);
}

//扩展欧几里得 mod为任意数
ll ex_gcd(int a,int b,int& x,int& y){
    if(b == 0) {x=1,y=0;return a;}
    int d = ex_gcd(b,a%b,x,y);
    int temp=x;
    x = y;
    y = temp - (a/b)*y;
    return d;
}

int main(){
    int n;
    cin>>n>>mod;
    int x,y;
    for(int i=1;i<=n;i++){
        
        ll c = ex_gcd(i,mod,x,y);
        x %= mod;
        x += mod;
        x %= mod;
        cout<<x<<endl;
    }
}