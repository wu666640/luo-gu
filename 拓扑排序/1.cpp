#include <bits/stdc++.h>
using namespace std;

const int N = 100010; // 根据题目数据范围设定 N

vector<int> e[N]; // e[x] 存点 x 的邻点（出边）
vector<int> tp;   // tp 存拓扑序列
int din[N];       // din[x] 存点 x 的入度
int n, m, a, b;

bool toposort() {
    queue<int> q;
    // 1. 初始化：将所有入度为0的点入队
    for (int i = 1; i <= n; i++) {
        if (din[i] == 0) q.push(i);
    }
    
    // 2. 不断处理队列中的点
    while (q.size()) {
        int x = q.front();
        q.pop();
        tp.push_back(x); // 加入拓扑序列
        
        // 3. 删除出边，更新邻点入度
        for (auto y : e[x]) {
            if (--din[y] == 0) {
                q.push(y); // 入度变为0则入队
            }
        }
    }
    
    // 5. 判断是否有拓扑序
    return tp.size() == n;
}

int main() {
    cin >> n >> m;
    // 建图
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        e[a].push_back(b);
        din[b]++;
    }
    
    if (!toposort()) {
        puts("-1"); // 有环，无拓扑序
    } else {
        for (auto x : tp) {
            printf("%d ", x); // 输出拓扑序列
        }
    }
    return 0;
}