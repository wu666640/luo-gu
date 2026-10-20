#include <bits/stdc++.h>
using namespace std;

const int N = 1005; 
const int M = 100005; 

struct Edge {
    int u, v, t;
    // bool operator<(const Edge& other) const {
    //     return t < other.t;
    // }
} e[M];

int fa[N]; 

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].t;
    }

    sort(e, e + m,[](const Edge& a,Edge& b){
        return a.t<b.t;
    });

    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }

    int cnt = n; 
    int ans = -1;

    for (int i = 0; i < m; ++i) {
        int ru = find(e[i].u);
        int rv = find(e[i].v);
        
        if (ru != rv) {
            fa[ru] = rv;
            cnt--;
            if (cnt == 1) {
                ans = e[i].t;
                break; 
            }
        }
    }

    if (n == 1) ans = 0;

    cout << ans << "\n";

    return 0;
}