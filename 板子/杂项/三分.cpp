// 三分 — 实数域三分法求单峰函数极值（迭代逼近极点）
#include <bits/stdc++.h>
using namespace std;

// 单峰函数示例：f(x) = -(x-2)^2 + 5，在 [l, r] 上先增后减，顶点在 x = 2，最大值 5
// 实际使用时把 f 替换成具体的目标函数即可
double f(double x) {
    return -(x - 2) * (x - 2) + 5;
}

// 三分法在闭区间 [l, r] 上求单峰函数 f 的【最大值】所在位置
// 每次把区间缩短约 1/3，直到区间宽度小于 eps，收敛到极点
// 复杂度：O(log((r-l)/eps))，eps 为精度
// 说明：求最大值时比较 f(m1) 与 f(m2)，舍去函数值较? 一侧；求最小值则反之。
double ternary_search(double l, double r) {
    const double eps = 1e-9;
    while (r - l > eps) {
        double m1 = l + (r - l) / 3.0;   // 左三分点
        double m2 = r - (r - l) / 3.0;   // 右三分点
        if (f(m1) < f(m2))
            l = m1;   // 峰值在右侧三分段内，收缩左界
        else
            r = m2;   // 峰值在左侧三分段内（或 m1 处），收缩右界
    }
    return (l + r) / 2.0;   // 返回极值点 x
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：求 f(x) = -(x-2)^2 + 5 在 [-10, 10] 上的最大值
    double x = ternary_search(-10, 10);
    cout << fixed << setprecision(6);
    cout << "极值点 x ≈ " << x << "\n";          // 应接近 2
    cout << "最大值 f(x) ≈ " << f(x) << "\n";     // 应接近 5

    return 0;
}
