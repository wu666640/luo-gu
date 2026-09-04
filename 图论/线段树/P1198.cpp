#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 200005;
const ll INF = LONG_LONG_MIN;
ll tree[2*MAXN];
ll t = 0;
int len = 0;
ll D;

void pushup(int p){
    tree[p] = max(tree[p<<1],tree[p<<1|1]);
}

void build(int p,int l,int r){
    tree[p] = INF;
    if(l == r) return;

    int mid = (l + r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}

void modify(int p,int l,int r,int pos,int val){
    if(l == r){
        tree[p] = val;
        return ;
    }

    int mid = (l + r)>>1;
    if(pos <= mid) modify(p<<1,l,mid,pos,val);
    else modify(p<<1|1,mid+1,r,pos,val);
    pushup(p);
}

ll query(int p,int l,int r,int ql,int qr){
    if(ql <= l && r<= qr) return tree[p];
    int mid =(l + r) >> 1;
    ll res = INF;
    if(ql<=mid) res=max(res,query(p<<1,l,mid,ql,qr));
    if(qr > mid ) res = max(res,query(p<<1|1,mid+1,r,ql,qr));
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int M;
    cin>>M>>D;
    build(1,1,M);
    while(M--){
        char op;
        ll x;
        cin>>op>>x;
        if(op == 'A'){
            ll val = ((x+t)%D+D)%D;
            len ++;
            
        }
    }
}