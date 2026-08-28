// DFS — 深度优先搜索回溯模板，以全排列为例（idx + vis + 回溯）
#include <bits/stdc++.h>
using namespace std;

int n;                       // 要排列的元素个数
vector<int> path;            // 当前排好的序列（全局变量，避免栈爆）
bool vis[20];                // vis[i] 标记数字 i 是否已被使用

// 递归回溯函数：正在确定排列的第 step 个位置（0 基）。
// 复杂度：O(n!)（枚举了所有排列）
void dfs(int step) {
    if (step == n) {         // 已填满 n 个位置，输出一个完整排列
        for (int i = 0; i < n; ++i) cout << path[i] << (i + 1 == n ? "\n" : " ");
        return;
    }
    for (int i = 1; i <= n; ++i) { // 尝试把数字 i 放到当前位
        if (vis[i]) continue;      // 该数字已被使用，跳过
        vis[i] = true;             // 标记使用
        path.push_back(i);         // 填入当前位
        dfs(step + 1);             // 递归确定下一个位置
        path.pop_back();           // 回溯：撤销填入
        vis[i] = false;            // 回溯：撤销标记
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    n = 3; // 演示：输出 [1,2,3] 的全排列
    cout << "1.." << n << " 的全排列:\n";
    dfs(0);
    return 0;
}
