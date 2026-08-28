// 数位DP — 数位 DP：按位处理 + 记忆化，统计 [0,x] 中满足条件的数的个数
#include <bits/stdc++.h>
using namespace std;

int num[25];                          // 把上界 x 拆成十进制各低位（num[0] 为个位）
long long memo[25][2][2][25];         // memo[pos][limit][lead][cnt] 记忆化
// pos: 当前处理到的位；limit: 此前是否一直贴着上界；lead: 是否仍处前导零；cnt: 已累加的计数

/*
 * 数位 DP：统计 [0, x] 内所有数的十进制表示中数字 c 出现的总次数。
 * 从高位向低位递归，每一位枚举填 d：0..(limit ? 该位上界 : 9)。
 * 参数含义：
 *   pos   当前处理从最高位起的第 pos 位（数位从高到低）；
 *   limit 此前是否一直贴着上界，若是则当前位只能填到 num[pos]；
 *   lead  是否仍处于前导零阶段（之前全是 0）；
 *   cnt   之前已经出现的数字 c 的次数（作为 state）；
 *   c     要找的目标数字。
 * 递归返回：从当前位继续往后能贡献的 c 的总次数。
 * 记忆化：只有当 !limit && !lead 时状态才不受上界/前导零影响，可复用。
 * 复杂度：O(位数 * 2 * 2 * 位数)。
 * 若要统计"满足某条件（如含数字 X、可被某数整除、各位和等）的数的个数"，
 * 只需替换 state（cnt）与加贡献（add）的判定即可。
 */
long long dfs(int pos, int limit, int lead, int cnt, int c) {
    if (pos < 0) return cnt;                                  // 所有位处理完
    if (!limit && !lead && memo[pos][limit][lead][cnt] != -1)
        return memo[pos][limit][lead][cnt];

    int up = limit ? num[pos] : 9;
    long long res = 0;
    for (int d = 0; d <= up; ++d) {
        // 统计本位置为 d 时对数字 c 的贡献：
        // 处于前导零阶段且 d == 0 时不算作数字 0 的计数（常见约定）
        int add = (!(lead && d == 0) && d == c) ? 1 : 0;
        res += dfs(pos - 1, limit && d == up, lead && d == 0, cnt + add, c);
    }
    if (!limit && !lead) memo[pos][limit][lead][cnt] = res;
    return res;
}

// 统计 [0, x] 中数字 c 出现的总次数
long long countDigit(long long x, int c) {
    if (x < 0) return 0;
    int len = 0;
    while (x) { num[len++] = x % 10; x /= 10; }
    if (len == 0) num[len++] = 0;          // 特判 x == 0
    memset(memo, -1, sizeof(memo));
    return dfs(len - 1, 1, 1, 0, c);       // 从最高位开始
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 演示：统计 [0, 20] 内数字 1 出现的总次数
    long long ans = countDigit(20, 1);
    cout << "[0, 20] 中数字 1 出现的次数：" << ans << '\n';
    // 验证：1(1次), 10(1), 11(2), 12~19(各1,共8) -> 1+1+2+8 = 12
    return 0;
}
