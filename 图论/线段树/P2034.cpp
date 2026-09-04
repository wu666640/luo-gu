#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 100010;
const ll INF = 1e18;

int n,k;
ll a[MAXN],dp[MAXN],sum[MAXN];

ll tree[4*MAXN];

void build(int p,int l,int r){
    tree[p] = -INF;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}

void update(int p,int l,int r,int pos,ll val){
    if(l==r){
        tree[p] = val;
        return;
    }
    int mid = (l+r)>>1;
    if(pos<=mid) update(p<<1,l,mid,pos,val);
    else update(p<<1|1,mid+1,r,pos,val);

    tree[p] = max(tree[p<<1],tree[p<<1|1]);
}

ll query(int p,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return tree[p];
    int mid = (l+r)>>1;
    ll res = -INF;
    if(mid >= ql) res = max(res,query(p<<1,l,mid,ql,qr));
    if(mid < qr)  res = max(res,query(p<<1|1,mid+1,r,ql,qr));
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i] = sum[i-1]+a[i];
    }

    n++,a[n]=0,sum[n]=sum[n-1];
    build(1,0,n);
    update(1,0,n,0,dp[0]-sum[0]);

    for(int i=1;i<=n;i++){
        int L =max(0,i-k-1);
        int R = i-1;
        ll best = query(1,0,n,L,R);
        dp[i] = sum[i-1] + best;
        update(1,0,n,i,dp[i] - sum[i]);
    }

    cout<<dp[n]<<'\n';
    return 0;
}
