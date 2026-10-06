#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll calc(ll a, ll b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    if (op == '^') { ll r = 1; for (ll i = 0; i < b; i++) r *= a; return r; }
    return 0;
}

int prio(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    string s;
    getline(cin, s);
    
    stack<ll> nums;
    stack<char> ops;
    
    for (int i = 0; i < s.size(); ) {
        if (s[i] == ' ') { i++; continue; }
        
      
        if (isdigit(s[i])) {
            ll num = 0;
            while (i < s.size() && isdigit(s[i]))
                num = num * 10 + (s[i++] - '0');
            nums.push(num);
        }
        
        else if (s[i] == '(') {
            ops.push(s[i++]);
        }
        
        else if (s[i] == ')') {
            while (ops.top() != '(') {
                ll b = nums.top(); nums.pop();
                ll a = nums.top(); nums.pop();
                char op = ops.top(); ops.pop();
                nums.push(calc(a, b, op));
            }
            ops.pop();
            i++;
        }
        
        else {
            char op = s[i++];
            
            while (!ops.empty() && ops.top() != '(') {
                int topPrio = prio(ops.top());
                int curPrio = prio(op);
                
                if (topPrio > curPrio) {
                    
                    ll b = nums.top(); nums.pop();
                    ll a = nums.top(); nums.pop();
                    char top = ops.top(); ops.pop();
                    nums.push(calc(a, b, top));
                }
                else if (topPrio == curPrio) {
                    
                    if (op == '^') {
                        
                        break;
                    } else {
                       
                        ll b = nums.top(); nums.pop();
                        ll a = nums.top(); nums.pop();
                        char top = ops.top(); ops.pop();
                        nums.push(calc(a, b, top));
                    }
                }
                else {
                    
                    break;
                }
            }
            
            ops.push(op);
        }
    }
    
    
    while (!ops.empty()) {
        ll b = nums.top(); nums.pop();
        ll a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        nums.push(calc(a, b, op));
    }
    
    cout << nums.top() << endl;
    return 0;
}