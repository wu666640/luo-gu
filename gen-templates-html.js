#!/usr/bin/env node
/**
 * gen-templates-html.js — 把 板子/ 下的所有 C++ 模板生成一份可打印的合订 HTML
 *
 * 用法：  node gen-templates-html.js
 * 产物：  板子/模板合集.html  （自包含、语法高亮、A4 打印优化，浏览器 Ctrl+P 可导出 PDF）
 *
 * 特性：
 *   - 自动扫描 板子/ 目录下所有 .cpp，按一级分类（基础/数学/数据结构/图论/字符串/搜索/DP/杂项）分组
 *   - 每个模板开头第一句 `// 板子名 — 一句话用途` 自动作为该页的说明
 *   - 之后新增模板：往对应分类文件夹放一个 .cpp，再跑一次本脚本即可（无需手改这份文档）
 *   - 只依赖 Node 标准库，无第三方依赖
 */
const fs = require('fs');
const path = require('path');

const ROOT = __dirname;
const TPL_DIR = path.join(ROOT, '板子');
const OUT_FILE = path.join(TPL_DIR, '模板合集.html');

const CATEGORIES = ['基础', '数学', '数据结构', '图论', '字符串', '搜索', 'DP', '杂项'];

// ---- 1. 扫描所有 .cpp 并按一级分类分组 ----
const byCat = new Map();
function walk(dir, rel = '') {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    if (e.isDirectory()) walk(path.join(dir, e.name), path.join(rel, e.name));
    else if (e.name.endsWith('.cpp')) {
      const cat = rel.split(path.sep)[0];           // 一级分类名（若在子目录则取最近一级）
      if (!byCat.has(cat)) byCat.set(cat, []);
      byCat.get(cat).push({ abs: path.join(dir, e.name), rel: path.join(rel, e.name) });
    }
  }
}
if (!fs.existsSync(TPL_DIR)) { console.error('❌ 未找到 板子/ 目录'); process.exit(1); }
walk(TPL_DIR);

// 让分类按固定顺序显示，未列出的追加到后面
const cats = [...CATEGORIES.filter((c) => byCat.has(c)),
              ...[...byCat.keys()].filter((c) => !CATEGORIES.includes(c))];

for (const c of cats) byCat.get(c).sort((a, b) => a.rel.localeCompare(b.rel, 'zh'));

// ---- 2. 从文件名/首行注释提取标题 ----
function titleOf(f) {
  const base = path.basename(f.rel, '.cpp');
  const first = fs.readFileSync(f.abs, 'utf8').split('\n')[0].trim();
  if (base.toLowerCase().startsWith('p')) return base;  // 题解类（这里一般不会出现）
  return base;                                          // 板子：直接用文件名
}
function descOf(f) {
  const lines = fs.readFileSync(f.abs, 'utf8').split('\n');
  for (const ln of lines) {
    const t = ln.trim();
    if (t.startsWith('//') && !t.startsWith('//http') && t.length > 3) {
      return t.replace(/^\/\/\s*/, '');                 // 去掉 // 前缀
    }
  }
  return '';
}

// ---- 3. 简易 C++ 语法高亮（按 token 分类成 span）----
function esc(s) {
  return s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
}
const TOKEN_RE = /(\/\/[^\n]*)|(\/\*[\s\S]*?\*\/)|("(?:[^"\\\n]|\\.)*")|('(?:[^'\\\n]|\\.)*')|(^[ \t]*#\s*\w+)|(\b\d+(?:\.\d+)?(?:[eE][+-]?\d+)?\b)|(\b(?:return|if|else|for|while|do|break|continue|switch|case|default|int|char|long|short|double|float|bool|void|constexpr|using|typedef|struct|class|enum|namespace|template|typename|auto|new|delete|size_t|true|false|sizeof|public|private|protected|const|static)\b)|(\b[A-Za-z_]\w*(?=\s*\())|([A-Za-z_]\w*)/g;
function hl(code) {
  let out = '', last = 0, m;
  TOKEN_RE.lastIndex = 0;
  while ((m = TOKEN_RE.exec(code)) !== null) {
    out += esc(code.slice(last, m.index));
    let cls = 'i';
    if (m[1] != null || m[2] != null) cls = 'c';
    else if (m[3] != null || m[4] != null) cls = 's';
    else if (m[5] != null) cls = 'p';
    else if (m[6] != null) cls = 'n';
    else if (m[7] != null) cls = 'k';
    else if (m[8] != null) cls = 'f';
    out += `<span class="${cls}">${esc(m[0])}</span>`;
    last = m.index + m[0].length;
  }
  out += esc(code.slice(last));
  return out;
}

// ---- 4. 组装 HTML ----
let tocHtml = '';
const mainBlocks = [];
for (const cat of cats) {
  const files = byCat.get(cat);
  // 目录项
  const toc = files.map((f) => `<li><a href="#${esc(f.rel)}">${esc(titleOf(f))}</a></li>`).join('');
  tocHtml += `<div class="toc-group"><h4>${esc(cat)}</h4><ul>${toc}</ul></div>\n`;
  // 每个模板的 section
  const tpls = files.map((f) => {
    const code = fs.readFileSync(f.abs, 'utf8');
    const title = titleOf(f);
    const desc = descOf(f);
    return `<section id="${esc(f.rel)}" class="tpl" data-cat="${esc(cat)}">
  <header>
    <span class="cat">${esc(cat)}</span>
    <h3>${esc(title)}</h3>
    ${desc ? `<p>${esc(desc)}</p>` : ''}
  </header>
  <pre><code>${hl(code)}</code></pre>
</section>`;
  }).join('\n');
  mainBlocks.push(`<h2 class="cat-h" id="${esc(cat)}">${esc(cat)}</h2>\n${tpls}`);
}
const bodyHtml = mainBlocks.join('\n');

const total = [...byCat.values()].reduce((s, a) => s + a.length, 0);
const date = new Date().toLocaleDateString('zh-CN');

const html = `<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ACM/OI 算法板子合集 · 共 ${total} 个模板</title>
<style>
  :root{
    --code-bg:#f6f8fa; --code-fg:#24292e;
    --c:#8a8f98; --s:#4a9e3f; --p:#b06a00; --n:#9a6700; --k:#7c3aed; --f:#1a56db; --i:#24292e;
    --acc:#2f6fed; --line:#e3e6ea;
  }
  *{box-sizing:border-box}
  body{margin:0;font-family:"Microsoft YaHei","PingFang SC",system-ui,sans-serif;color:#1f2328;background:#fff;line-height:1.6}
  .wrap{max-width:860px;margin:0 auto;padding:0 20px 80px}
  .mast{padding:34px 0 10px;border-bottom:2px solid var(--acc)}
  .mast h1{margin:0 0 6px;font-size:26px;color:var(--acc)}
  .mast p{margin:0;color:#57606a;font-size:13px}
  .meta{margin-top:12px;font-size:12px;color:#8b949e}
  h2.cat-h{font-size:20px;margin:34px 0 8px;padding:6px 12px;background:#eef3ff;color:var(--acc);border-radius:6px}
  section.tpl{margin:26px 0;border:1px solid var(--line);border-radius:8px;overflow:hidden}
  section.tpl header{background:#f6f8fa;padding:10px 16px;border-bottom:1px solid var(--line)}
  section.tpl .cat{font-size:11px;color:#fff;background:var(--acc);padding:2px 8px;border-radius:10px;margin-right:8px}
  section.tpl h3{display:inline;margin:0;font-size:16px}
  section.tpl header p{margin:6px 0 0;font-size:13px;color:#57606a}
  pre{margin:0;padding:14px 16px;background:var(--code-bg);overflow:auto;font-family:Consolas,"Courier New",monospace;font-size:13px;line-height:1.5;color:var(--code-fg)}
  pre code{font-family:inherit;white-space:pre}
  .c{color:var(--c);font-style:italic}.s{color:var(--s)}.p{color:var(--p)}.n{color:var(--n)}
  .k{color:var(--k)}.f{color:var(--f)}.i{color:var(--i)}
  /* 目录导航（仅屏幕） */
  .toc{position:sticky;top:12px;max-height:calc(100vh - 30px);overflow:auto;border:1px solid var(--line);border-radius:8px;padding:14px 18px;background:#fff}
  .toc h2{margin:0 0 10px;font-size:16px}
  .toc-group h4{margin:10px 0 4px;color:var(--acc)}
  .toc-group ul{list-style:none;margin:0;padding-left:10px}
  .toc-group li{margin:2px 0}
  .toc-group a{color:#444;text-decoration:none;font-size:13px}
  .toc-group a:hover{color:var(--acc)}
  .toc-layout{display:grid;grid-template-columns:280px 1fr;gap:22px;margin-top:22px}
  /* 打印 */
  @media print{
    @page{size:A4;margin:14mm 12mm}
    body{font-size:9.5pt}
    .wrap{max-width:none;padding:0}
    .mast{border-bottom-width:1px}
    .toc-layout{display:block}
    .toc{display:none}   /* 打印时隐藏目录，改用首页文字目录 */
    .print-toc{display:block}
    section.tpl{page-break-before:always;margin:0 0 14mm;border:1px solid #ccc;break-inside:avoid}
    section.tpl:first-of-type{page-break-before:auto}
    pre{font-size:8pt;line-height:1.4}
    pre code{white-space:pre-wrap;word-break:break-word}
    a{color:inherit}
  }
  .print-toc{display:none;margin-top:16px;font-size:12px}
  @media not print{.print-toc{display:none}}
</style>
</head>
<body>
<div class="wrap">
  <div class="mast">
    <h1>ACM / OI 算法板子合集</h1>
    <p>C++17 常用算法模板 · 由 gen-templates-html.js 自动生成</p>
    <div class="meta">生成日期：${date} ｜ 模板数：${total} ｜ 源：<strong>板子/</strong> 目录</div>
  </div>

  <div class="print-toc">
    <h2>目录</h2>
    ${tocHtml}
  </div>

  <div class="toc-layout">
    <aside>
      <nav class="toc">
        <h2>目录</h2>
        ${tocHtml}
      </nav>
    </aside>
    <main>
      ${bodyHtml}
    </main>
  </div>

  <footer style="margin-top:40px;color:#8b949e;font-size:12px;text-align:center">
    由 <code>node gen-templates-html.js</code> 生成 · 添加新模板后重跑即可更新本文档
  </footer>
</div>
</body>
</html>`;

fs.writeFileSync(OUT_FILE, html, 'utf8');
console.log(`✅ 已生成 ${path.relative(ROOT, OUT_FILE)}`);
console.log(`   分类: ${cats.join(', ')}`);
console.log(`   模板数: ${total}`);
console.log(`   打印: 浏览器打开后 Ctrl+P（建议 边距-默认/背景-关闭，纸张 A4）`);
