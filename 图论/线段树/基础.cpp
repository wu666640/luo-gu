#include<bits/stdc++.h>
using namespace std;


const int MAXN = 500005;

long long tree[4*MAXN];
long long arr[MAXN];

void build(int p,int l,int r){
    if(l == r) {tree[p] = arr[l]; return ;}
    int mid = (l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    tree[p] = tree[p<<1] + tree[p<<1|1]; 
}

void update(int p,int l,int r,int pos,int val){
    if(l==r){
        tree[p] = val;
        return ;
    }
    int mid = (l+r)>>1;
    if(pos<=mid) update(p<<1,l,r,pos,val);
    else update(p<<1|1,l,r,pos,val);

    tree[p] = tree[p<<1] + tree[p<<1|1];
}

int query(int p,int l,int r,int ql,int qr){
    if(ql <= l && r<=qr) return tree[p];
    int mid = (l+r) >> 1 ,res = 0;
    if(ql <= mid) res += query(p<<1,l,mid,ql,qr);
    if(qr > mid)  res += query(p<<1|1,mid+1,r,ql,qr);
    return res;
}

long long lazy[MAXN * 4];   // 懒标记（用 long long 防溢出）
long long seg[MAXN * 4];    // 区间和

void buildLazy(int p,int l,int r){
    lazy[p] = 0;
    if(l == r){ seg[p] = arr[l];return ;}
    int mid = (l+r) >> 1;
    buildLazy(p << 1,l,mid);
    buildLazy(p << 1|1,mid+1,r);
    seg[p] = seg[p<<1] + seg[p<<1|1];
}

void pushDown(int p,int l,int r){
    if(lazy[p] == 0) return;
    int mid = (l+r) >> 1;
    lazy[p<<1]   += lazy[p];
    seg[p<<1]    += lazy[p]*(mid-l+1);
    lazy[p<<1|1] += lazy[p];
    seg[p<<1|1]  += lazy[p]*(r-mid);
    lazy[p] = 0;
}

void rangeAdd(int p,int l,int r,int ql,int qr,long long val){
    if(ql <= l&& r <= qr) {
        seg[p] += val * (r - l + 1);
        lazy[p] += val;
        return ;
    }      
    pushDown(p,l,r);
    int mid = (l + r) >> 1;
    if (ql <= mid) rangeAdd(p << 1, l, mid, ql, qr, val);
    if (qr > mid)  rangeAdd(p << 1 | 1, mid + 1, r, ql, qr, val);
    seg[p] = seg[p << 1] + seg[p << 1 | 1];
}

long long rangeSum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[p];
    pushDown(p, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) res += rangeSum(p << 1, l, mid, ql, qr);
    if (qr > mid)  res += rangeSum(p << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    buildLazy(1,1,n);
    while(m--){
        int q;
        cin>>q;
        if(q==1){
            long long x,y,k;
            cin>>x>>y>>k;
            rangeAdd(1,1,n,x,y,k);
        }
        else {
            int x,y;
            cin>>x>>y;
            cout<<rangeSum(1,1,n,x,y)<<'\n';
        }
    }


    return 0;
}