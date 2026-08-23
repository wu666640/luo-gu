# luo-gu 洛谷刷题记录

OI / ACM / XCPC 学习与刷题仓库，全部使用 C++ 编写，按知识点分类整理，每道题附完整代码与注释。

> 📖 日常操作（加题、提交、CI 说明）见 **[操作指南.md](操作指南.md)** —— 该文档由 Agent 持续维护，新学的操作会自动追加，直接照做即可
>
> 🎯 DP 刷题进度见 **[dp题单.md](dp题单.md)**（待完成计划）

## 仓库结构

<!-- 本结构由 gen-readme.js 自动生成，请勿手动编辑；新建分类文件夹后运行 `node gen-readme.js` -->

```
.
├── bfs/         # BFS相关题解（1 题）
├── dfs/         # DFS相关题解（2 题）
├── dp/          # DP相关题解（2 题）
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
| [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162) | DFS | [DFS版](dfs/P1162%20%E5%A1%AB%E6%B6%82%E9%A2%9C%E8%89%B2.cpp) | ✅ 已完成 |
| [P2097 资料分发 1](https://www.luogu.com.cn/problem/P2097) | BFS / 并查集 | [BFS版](bfs/P2097%20%E8%B5%84%E6%96%99%E5%88%86%E5%8F%91%201.cpp) · [并查集版](%E5%B9%B6%E6%9F%A5%E9%9B%86/P2097.cpp) | ✅ 已完成 |

## 本地编译运行

```bash
# 以 P1162 为例：编译 + 运行
g++ -std=c++17 -O2 "dfs/P1162 填涂颜色.cpp" -o main
./main
```

## 环境

- 语言：C++17
- 平台：洛谷（luogu.com.cn）
- CI：GitHub Actions 自动编译检查仓库内所有 `.cpp` 文件，绿勾 = 编译通过

## 刷题计划

- [ ] BFS 基础
- [ ] 最短路（Dijkstra / Floyd）
- [ ] 动态规划入门
- [ ] 字符串与数据结构
