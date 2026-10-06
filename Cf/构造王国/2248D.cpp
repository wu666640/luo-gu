#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        string s,t;
        cin>>s>>t;
        vector<ll>cnt00(n+1),cnt10(n+1),cnt01(n+1),cnt11(n+1);
        for(int i=0;i<n;i++){
            if(s[i]=='0'&& t[i] == '0') {
                 cnt00[i+1] = cnt00[i] + 1;
                 cnt01[i+1] = cnt01[i] ;
                 cnt10[i+1] = cnt10[i] ;
                 cnt11[i+1] = cnt11[i] ;
            }
            else if(s[i]=='0'&& t[i] == '1'){
                 cnt00[i+1] = cnt00[i] ;
                 cnt01[i+1] = cnt01[i] +1;
                 cnt10[i+1] = cnt10[i] ;
                 cnt11[i+1] = cnt11[i] ;
            }
            else if(s[i]=='1'&& t[i] == '0'){
                  cnt00[i+1] = cnt00[i] ;
                 cnt01[i+1] = cnt01[i] ;
                 cnt10[i+1] = cnt10[i] +1;
                 cnt11[i+1] = cnt11[i] ;
            }
            else if(s[i]=='1'&& t[i] == '1'){
                  cnt00[i+1] = cnt00[i] ;
                 cnt01[i+1] = cnt01[i] ;
                 cnt10[i+1] = cnt10[i] ;
                 cnt11[i+1] = cnt11[i] +1;
            }
        }

        while(q--){
            ll l,r;
            cin>>l>>r;
            int x,y,u,v;
            x = cnt10[r]-cnt10[l-1];
            y = cnt01[r] - cnt01[l-1];
            u = cnt00[r] - cnt00[l-1];
            v = cnt11[r] - cnt11[l-1];
            if(abs(x-y)<=u+v) cout<<"YES"<<endl;
            else cout<<"NO"<<'\n';
            
        }
    }
    return 0;
}