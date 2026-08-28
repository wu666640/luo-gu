#!/usr/bin/env node
/**
 * gen-readme.js — 洛谷刷题仓库 README 自动生成器
 *
 * 用法：在仓库根目录运行  node gen-readme.js
 * 功能：
 *   1. 自动扫描所有分类目录下的 .cpp 文件，解析题号/题名/知识点
 *   2. 自动生成「仓库结构」（按实际目录 + 每类题数）
 *   3. 自动生成「题解列表」表格
 * 每次新增/删除题目或新建分类文件夹后运行一次即可，无需手动改任何章节。
 */
const fs = require('fs');
const path = require('path');

const ROOT = __dirname;
const README = path.join(ROOT, 'README.md');
const SKIP_DIRS = new Set(['.git', '.github', '.cph', 'node_modules', 'assets', '板子']);

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

// ── 4. 统计各分类目录（自动生成「仓库结构」）────────────────────
const catCount = new Map();   // 分类目录名 -> 该目录下 .cpp 文件数
for (const f of files) {
  const top = f.cat.split('/')[0];
  if (top) catCount.set(top, (catCount.get(top) || 0) + 1);
}
const cats = [...catCount.keys()].sort();

const structLines = [
  '## 仓库结构',
  '',
  '<!-- 本结构由 gen-readme.js 自动生成，请勿手动编辑；新建分类文件夹后运行 `node gen-readme.js` -->',
  '',
  '```',
  '.',
];
for (const c of cats) {
  const n = catCount.get(c);
  const label = CAT_LABEL[c] || c;
  const pad = ' '.repeat(Math.max(1, 12 - c.length));  // 对齐到第 12 列（中文按 2 宽估算）
  structLines.push(`├── ${c}/${pad}# ${label}相关题解（${n} 题）`);
}
structLines.push('├── gen-readme.js # README 自动生成脚本（新增题目后运行）');
structLines.push('└── .github/      # CI 工作流（编译检查 + 自动更新 README）');
structLines.push('```');
structLines.push('');
const structSection = structLines.join('\n');

// ── 5. 生成「题解列表」表格 ───────────────────────────────────────
const tableLines = [
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
  const cats2 = [...new Set(row.versions.map((v) => v.cat))].filter(Boolean);
  const catText = cats2.map((c) => CAT_LABEL[c] || c).join(' / ') || '—';

  // 题解：多版本用「标签」区分，单版本直接用文件名
  const sols = row.versions.map((v) => {
    const label = v.cat ? `${CAT_LABEL[v.cat] || v.cat}版` : v.base;
    return `[${label}](${encodeURI(v.rel)})`;
  });
  const solText = sols.join(' · ');

  tableLines.push(`| ${link} | ${catText} | ${solText} | ✅ 已完成 |`);
}

const tableSection = tableLines.join('\n') + '\n';

// ── 6. 拼接并写入 README ─────────────────────────────────────────
let content = fs.readFileSync(README, 'utf8');

// 6a. 替换「仓库结构」章节（## 仓库结构 到下一个 ## 之间）
const structMarker = '## 仓库结构';
let structReplaced = false;
const structIdx = content.indexOf(structMarker);
if (structIdx !== -1) {
  const tailStart = content.indexOf('\n## ', structIdx + structMarker.length);
  const tail = tailStart === -1 ? '' : content.slice(tailStart + 1);
  content = content.slice(0, structIdx) + structSection + '\n\n' + tail;
  structReplaced = true;
}

// 6b. 替换「题解列表」章节
const tableMarker = '## 题解列表';
const tableIdx = content.indexOf(tableMarker);
if (tableIdx === -1) {
  console.error('❌ README.md 中未找到「## 题解列表」章节，请检查文件');
  process.exit(1);
}
const head2 = content.slice(0, tableIdx);
const tailStart2 = content.indexOf('\n## ', tableIdx + tableMarker.length);
const tail2 = tailStart2 === -1 ? '' : content.slice(tailStart2 + 1);
content = head2 + tableSection + '\n' + tail2;

fs.writeFileSync(README, content, 'utf8');

// ── 7. 输出摘要 ───────────────────────────────────────────────────
let total = 0;
for (const row of rows) total += row.versions.length;
console.log(`✅ README 已更新`);
console.log(`   分类目录: ${cats.join(', ')}`);
console.log(`   题目数: ${rows.length}，文件数: ${total}`);
if (!structReplaced) console.warn('   ⚠️ 未找到「## 仓库结构」章节，仅更新了题解列表');
for (const row of rows) {
  console.log(`   ${row.pid}  ${row.title}  (${row.versions.map((v) => v.rel).join(', ')})`);
}
