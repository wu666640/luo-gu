# luo-gu 洛谷刷题记录

> OI / ACM / XCPC 学习与刷题仓库，全部使用 **C++17** 编写，按知识点分类整理，每道题附完整代码与注释。仓库结构与题解列表由脚本自动生成、GitHub Actions 自动维护。

<p>
  <img src="https://github.com/wu666640/luo-gu/actions/workflows/c-cpp.yml/badge.svg" alt="C++ CI">
  <img src="https://img.shields.io/github/stars/wu666640/luo-gu?label=stars&logo=github" alt="stars">
  <img src="https://img.shields.io/github/last-commit/wu666640/luo-gu?label=last%20commit&logo=github" alt="last commit">
</p>

## 📚 文档导航

| 文档 | 用途 |
| --- | --- |
| [操作指南.md](操作指南.md) | 加题 / 提交 / CI 的日常操作 |
| [dp题单.md](dp题单.md) | DP 刷题进度（待完成计划） |
| [图论建图打卡.md](图论建图打卡.md) | 图论建模「四问」打卡 |
| [板子/README.md](板子/README.md) | 可复用 C++17 算法模板库（考场速查） |
| [百度之星冲刺/README.md](百度之星冲刺/README.md) | 百度之星预选赛冲刺计划 |
| [笔记/README.md](笔记/README.md) | 算法学习笔记（图论 / CF / 考点速查 / 知识总表） |

> 📓 算法学习笔记见 [笔记/](笔记/README.md)（图论学习与建图、CF 刷题路线、百度之星考点速查等）。

## 📊 仓库统计

<!-- 本统计由 gen-readme.js 自动生成，请勿手动编辑 -->

| 指标 | 数值 |
| --- | --- |
| 已收录题目 | 14 |
| 分类数 | 5 |
| 题解文件数 | 16 |
| 板子模板数 | 43 |


## 仓库结构

<!-- 本结构由 gen-readme.js 自动生成，请勿手动编辑；新建分类文件夹后运行 `node gen-readme.js` -->

```
.
├── bfs/         # BFS相关题解（1 题）
├── dfs/         # DFS相关题解（3 题）
├── dp/          # DP相关题解（5 题）
├── 图论/          # 图论相关题解（6 题）
├── 并查集/         # 并查集相关题解（1 题）
├── gen-readme.js # README 自动生成脚本（新增题目后运行）
└── .github/      # CI 工作流（编译检查 + 自动更新 README）
```


## 题解列表

<!-- 本表由 gen-readme.js 自动生成，请勿手动编辑；新增题目后运行 `node gen-readme.js` -->

| 题目 | 知识点 | 题解 | 状态 |
| --- | --- | --- | --- |
| [P121 数字三角形Number Triangles](https://www.luogu.com.cn/problem/P121) | DP | [DP版](dp/P121%20%E6%95%B0%E5%AD%97%E4%B8%89%E8%A7%92%E5%BD%A2Number%20Triangles.cpp) | ✅ 已完成 |
| [P1004 [NOIP 2000 提高组] 方格取数](https://www.luogu.com.cn/problem/P1004) | DP | [DP版](dp/P1004%20%5BNOIP%202000%20%E6%8F%90%E9%AB%98%E7%BB%84%5D%20%E6%96%B9%E6%A0%BC%E5%8F%96%E6%95%B0.cpp) | ✅ 已完成 |
| [P1037 [NOIP 2002 普及组] 产生数](https://www.luogu.com.cn/problem/P1037) | DFS | [DFS版](dfs/P1037%20%5BNOIP%202002%20%E6%99%AE%E5%8F%8A%E7%BB%84%5D%20%E4%BA%A7%E7%94%9F%E6%95%B0.cpp) | ✅ 已完成 |
| [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) | DP | [DP版](dp/P1115%20%E6%9C%80%E5%A4%A7%E5%AD%90%E6%AE%B5%E5%92%8C.cpp) | ✅ 已完成 |
| [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162) | DFS | [DFS版](dfs/P1162%20%E5%A1%AB%E6%B6%82%E9%A2%9C%E8%89%B2.cpp) | ✅ 已完成 |
| [P1198](https://www.luogu.com.cn/problem/P1198) | 图论/线段树 | [图论/线段树版](%E5%9B%BE%E8%AE%BA/%E7%BA%BF%E6%AE%B5%E6%A0%91/P1198.cpp) | ✅ 已完成 |
| [P1396 营救](https://www.luogu.com.cn/problem/P1396) | 图论 | [图论版](%E5%9B%BE%E8%AE%BA/P1396%20%E8%90%A5%E6%95%91.cpp) | ✅ 已完成 |
| [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433) | DFS / dp/状压dp | [DFS版](dfs/P1433%20%E5%90%83%E5%A5%B6%E9%85%AA.cpp) · [dp/状压dp版](dp/%E7%8A%B6%E5%8E%8Bdp/P1433%20%E5%90%83%E5%A5%B6%E9%85%AA.cpp) | ✅ 已完成 |
| [P2034](https://www.luogu.com.cn/problem/P2034) | 图论/线段树 | [图论/线段树版](%E5%9B%BE%E8%AE%BA/%E7%BA%BF%E6%AE%B5%E6%A0%91/P2034.cpp) | ✅ 已完成 |
| [P2097 资料分发 1](https://www.luogu.com.cn/problem/P2097) | BFS / 并查集 | [BFS版](bfs/P2097%20%E8%B5%84%E6%96%99%E5%88%86%E5%8F%91%201.cpp) · [并查集版](%E5%B9%B6%E6%9F%A5%E9%9B%86/P2097.cpp) | ✅ 已完成 |
| [P3879 [TJOI2010] 阅读理解](https://www.luogu.com.cn/problem/P3879) | 图论/字典树 | [图论/字典树版](%E5%9B%BE%E8%AE%BA/%E5%AD%97%E5%85%B8%E6%A0%91/P3879%20%5BTJOI2010%5D%20%E9%98%85%E8%AF%BB%E7%90%86%E8%A7%A3.cpp) | ✅ 已完成 |
| [P3916 图的遍历](https://www.luogu.com.cn/problem/P3916) | 图论 | [图论版](%E5%9B%BE%E8%AE%BA/P3916%20%E5%9B%BE%E7%9A%84%E9%81%8D%E5%8E%86.cpp) | ✅ 已完成 |
| [P5318 查找文献(洛谷【深基18.例3】)](https://www.luogu.com.cn/problem/P5318) | 图论 | [图论版](%E5%9B%BE%E8%AE%BA/P5318%20%E6%9F%A5%E6%89%BE%E6%96%87%E7%8C%AE(%E6%B4%9B%E8%B0%B7%E3%80%90%E6%B7%B1%E5%9F%BA18.%E4%BE%8B3%E3%80%91).cpp) | ✅ 已完成 |
| [P11430 [COCI 20242025 #2] 游戏](https://www.luogu.com.cn/problem/P11430) | DP | [DP版](dp/P11430%20%5BCOCI%2020242025%20#2%5D%20%E6%B8%B8%E6%88%8F.cpp) | ✅ 已完成 |

## 🧰 板子（算法模板）

> 见 **[板子/README.md](板子/README.md)**（本仓库自带，不进入上方题解列表）。按知识点整理的可复用 C++17 模板，含基础/数学/数据结构/图论/字符串/搜索/DP/杂项，每个文件夹一个 `.cpp`，均带演示 `main()` 且可独立编译。

```bash
# 以线段树为例：编译 + 运行看演示
g++ -std=c++17 -O2 "板子/数据结构/线段树.cpp" -o main && ./main
```

## 本地编译运行

```bash
# 以 P1162 为例：编译 + 运行
g++ -std=c++17 -O2 "dfs/P1162 填涂颜色.cpp" -o main && ./main
```

## 环境

- 语言：C++17
- 平台：洛谷（luogu.com.cn）
- CI：GitHub Actions 自动编译检查仓库内所有 `.cpp` 文件，绿勾 = 编译通过

## 🎯 训练计划

> 按主线推进，详细题单见各文档。

| 主线 | 计划 | 题单 / 进度 |
| --- | --- | --- |
| **动态规划** | 线性DP → 背包 → LIS → 区间 / 记忆化 | [dp题单.md](dp题单.md) |
| **图论** | 存图 → 最短路 → 生成树 → 拓扑 → 缩点 → 建模 | [图论建图打卡.md](图论建图打卡.md) |
| **竞赛** | 百度之星预选赛（9.19）→ CF / ICPC | [百度之星冲刺/README.md](百度之星冲刺/README.md) |
| **备战** | CF 1058 → 1600 提升路线 | [CF刷题路线.md](笔记/CF刷题路线.md) |
| **数据结构** | 线段树模板 → 单点改/区间查 → 进阶变形 | [线段树题单.md](线段树题单.md) |
