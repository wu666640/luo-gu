#!/usr/bin/env node
/**
 * gen-readme.js — 洛谷刷题仓库 README 自动生成器
 *
 * 用法：在仓库根目录运行  node gen-readme.js
 * 功能：扫描所有分类目录下的 .cpp 文件，自动解析题号/题名/知识点，
 *       重新生成 README 的「题解列表」表格。
 * 每次新增/删除题目后运行一次即可，无需手动改表格。
 */
const fs = require('fs');
const path = require('path');

const ROOT = __dirname;
const README = path.join(ROOT, 'README.md');
const SKIP_DIRS = new Set(['.git', '.github', '.cph', 'node_modules', 'assets']);

/** 目录名 → 知识点显示名 */
const CAT_LABEL = {
  dfs: 'DFS',
  bfs: 'BFS',
  并查集: '并查集',
  图论: '图论',
  最短路: '最短路',
  动态规划: '动态规划',
  dp: 'DP',
  贪心: '贪心',
  模拟: '模拟',
  字符串: '字符串',
  数学: '数学',
  二分: '二分',
  分治: '分治',
  数据结构: '数据结构',
};

// ── 1. 扫描所有 .cpp 文件 ─────────────────────────────────────────
const files = [];
function walk(dir, rel = '') {
  for (const entry of fs.readdirSync(dir, { withFileTypes: true })) {
    if (entry.isDirectory()) {
      if (SKIP_DIRS.has(entry.name)) continue;
      walk(path.join(dir, entry.name), path.join(rel, entry.name));
    } else if (entry.name.endsWith('.cpp')) {
      files.push({ rel: path.join(rel, entry.name).replace(/\\/g, '/'), cat: rel.replace(/\\/g, '/') });
    }
  }
}
walk(ROOT);

// ── 2. 解析题号 / 题名 ────────────────────────────────────────────
function parseInfo(file) {
  const base = path.basename(file.rel, '.cpp');
  const m = base.match(/^(P\d+)\s*(.*)$/);
  return {
    pid: m ? m[1] : base,          // P1037
    title: m ? m[2].trim() : '',   // [NOIP 2002 普及组] 产生数
    base,                          // P1037 [NOIP 2002 普及组] 产生数
  };
}

// ── 3. 按题号聚合（同一题可能有多版本：DFS版 / 并查集版）─────────
const byPid = new Map();
for (const f of files) {
  const { pid, title, base } = parseInfo(f);
  if (!byPid.has(pid)) byPid.set(pid, { pid, title, versions: [] });
  const item = byPid.get(pid);
  if (!item.title && title) item.title = title;
  item.versions.push({ cat: f.cat, rel: f.rel, base });
}

const rows = [...byPid.values()].sort((a, b) => parseInt(a.pid.slice(1), 10) - parseInt(b.pid.slice(1), 10));

// ── 4. 生成表格 ───────────────────────────────────────────────────
const lines = [
  '## 题解列表',
  '',
  '<!-- 本表由 gen-readme.js 自动生成，请勿手动编辑；新增题目后运行 `node gen-readme.js` -->',
  '',
  '| 题目 | 知识点 | 题解 | 状态 |',
  '| --- | --- | --- | --- |',
];

for (const row of rows) {
  const pid = row.pid;
  const title = row.title ? `${pid} ${row.title}` : pid;
  const link = `[${title}](https://www.luogu.com.cn/problem/${pid})`;

  // 知识点：多版本取并集
  const cats = [...new Set(row.versions.map((v) => v.cat))].filter(Boolean);
  const catText = cats.map((c) => CAT_LABEL[c] || c).join(' / ') || '—';

  // 题解：多版本用「标签」区分，单版本直接用文件名
  const sols = row.versions.map((v) => {
    const label = v.cat ? `${CAT_LABEL[v.cat] || v.cat}版` : v.base;
    return `[${label}](${encodeURI(v.rel)})`;
  });
  const solText = sols.join(' · ');

  lines.push(`| ${link} | ${catText} | ${solText} | ✅ 已完成 |`);
}

const tableSection = lines.join('\n') + '\n';

// ── 5. 替换 README 中「题解列表」章节 ─────────────────────────────
let content = fs.readFileSync(README, 'utf8');
const marker = '## 题解列表';
const idx = content.indexOf(marker);
if (idx === -1) {
  console.error('❌ README.md 中未找到「## 题解列表」章节，请检查文件');
  process.exit(1);
}
const head = content.slice(0, idx);
const tailStart = content.indexOf('\n## ', idx + marker.length);
const tail = tailStart === -1 ? '' : content.slice(tailStart + 1); // 去掉开头的换行，统一由下方补
const newContent = head + tableSection + '\n' + tail;

fs.writeFileSync(README, newContent, 'utf8');

// ── 6. 输出摘要 ───────────────────────────────────────────────────
let total = 0;
for (const row of rows) total += row.versions.length;
console.log(`✅ README 已更新`);
console.log(`   题目数: ${rows.length}，文件数: ${total}`);
for (const row of rows) {
  console.log(`   ${row.pid}  ${row.title}  (${row.versions.map((v) => v.rel).join(', ')})`);
}
