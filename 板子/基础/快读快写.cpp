// 快读快写 — 基于 fread 缓冲的快速输入输出，应对大规模数据 IO
#include <bits/stdc++.h>
using namespace std;

/*
 * 快速输入输出类（fread 缓冲版）。
 * 适用于输入输出量极大（如 n、m 达 1e6 甚至更多）的题目，
 * 相比 cin/cout 能显著减少 IO 时间。
 *
 * 主要接口：
 *   bool readInt(int &x)        读入一个 int，成功返回 true
 *   bool readLong(long long &x) 读入一个 long long，成功返回 true
 *   bool readStr(string &s)     读入一个连续字符串（遇到空白分割），成功返回 true
 *   void writeInt(int x)        输出一个 int
 *   void writeLong(long long x) 输出一个 long long
 *   void writeStr(const string &s) 输出一个字符串
 *   void flush()                将缓冲区内容一次性写入 stdout
 *
 * 原理：一次性从 stdin 读入一大块到 buffer，
 *       由 pos 指针逐个字符解析，避免频繁调用读函数。
 */
struct FastIO {
    static const int BUFSIZE = 1 << 20; // 缓冲区 1MB
    char buf[BUFSIZE];
    int pos = 0;   // buffer 中当前读取位置
    int len = 0;   // buffer 中有效字符数

    // 从 stdin 读入下一批字符到 buffer
    inline bool readNext() {
        return (pos < len) || (len = fread(buf, 1, BUFSIZE, stdin), pos = 0, pos < len);
    }

    // 读入一个整数（支持负数），成功返回 true，到达结尾返回 false
    bool readInt(int &x) {
        return readSigned(x);
    }

    // 读入一个 long long（支持负数），成功返回 true
    bool readLong(long long &x) {
        return readSigned(x);
    }

    // 通用有符号整数读取模板
    template <typename T>
    bool readSigned(T &x) {
        x = 0;
        char c;
        bool neg = false;
        // 跳过空白字符
        do {
            if (!readNext()) return false; // 已到文件尾
            c = buf[pos++];
        } while (c <= ' ');
        // 处理负号
        if (c == '-') {
            neg = true;
            if (!readNext()) return false;
            c = buf[pos++];
        }
        // 逐位累积数字
        for (; c >= '0' && c <= '9'; c = buf[pos++]) {
            x = x * 10 + (c - '0');
            if (!readNext()) break;
        }
        if (neg) x = -x;
        return true;
    }

    // 读入一个字符串（以空白字符为分隔），成功返回 true
    bool readStr(string &s) {
        s.clear();
        char c;
        // 跳过前导空白
        do {
            if (!readNext()) return false;
            c = buf[pos++];
        } while (c <= ' ');
        // 累积直到遇到空白
        do {
            s.push_back(c);
            if (!readNext()) break;
            c = buf[pos++];
        } while (c > ' ');
        return true;
    }

    // 输出缓冲区
    char out[BUFSIZE];
    int opos = 0;

    // 将一个字符放入输出缓冲（必要时先 flush）
    inline void putChar(char c) {
        if (opos >= BUFSIZE - 1) flush();
        out[opos++] = c;
    }

    // 通用有符号整数输出
    template <typename T>
    void writeSigned(T x) {
        if (x == 0) { putChar('0'); return; }
        if (x < 0) { putChar('-'); x = -x; }
        char tmp[32]; int t = 0;
        while (x > 0) { tmp[t++] = char('0' + x % 10); x /= 10; }
        while (t--) putChar(tmp[t]);
    }

    void writeInt(int x)      { writeSigned(x); }
    void writeLong(long long x) { writeSigned(x); }

    // 输出字符串
    void writeStr(const string &s) {
        for (char c : s) putChar(c);
    }

    // 将输出缓冲全部写出
    void flush() {
        if (opos > 0) {
            fwrite(out, 1, opos, stdout);
            opos = 0;
        }
    }

    // 析构时自动刷新
    ~FastIO() { flush(); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 说明：FastIO 内含两块 1MB 缓冲（共约 2MB），
    //       放入静态区（static）而非栈，避免在大栈限制下爆栈。
    static FastIO io;

    // 演示：依次读入 a、b、c（整数）和一个字符串 s，然后原样/反向输出
    int a, b;
    long long c;
    string s;
    io.readInt(a);
    io.readInt(b);
    io.readLong(c);
    io.readStr(s);

    io.writeInt(a + b);
    io.putChar('\n');
    io.writeLong(c);
    io.putChar('\n');
    // 反向输出字符串，演示 writeStr 的用法
    reverse(s.begin(), s.end());
    io.writeStr(s);
    io.putChar('\n');

    io.flush();
    return 0;
}
