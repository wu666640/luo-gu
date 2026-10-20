#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;
const int N = 100010;

vector<int> e[N];
int din[N];
ll f[N], g[N];

ll qpow(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin>>n>>m;
    
    for (int i = 1; i <= n; ++i) {
        f[i] = 1; 
        g[i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        din[y]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (din[i] == 0) q.push(i);
    }
    
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (int v : e[u]) {
            if (--din[v] == 0) q.push(v);
        }
    }
    
    for (int i = topo.size() - 1; i >= 0; --i) {
        int u = topo[i];
        for (int v : e[u]) {
            f[u] = (f[u] + f[v]) % MOD;
            g[u] = (g[u] + f[v] + g[v]) % MOD;
        }
    }
    
    ll total_paths = 0;
    ll total_length = 0;
    for (int i = 1; i <= n; ++i) {
        total_paths = (total_paths + f[i]) % MOD;
        total_length = (total_length + g[i]) % MOD;
    }
    
    ll ans = total_length * qpow(total_paths, MOD - 2, MOD) % MOD;
    cout << ans << "\n";
    
    return 0;
}