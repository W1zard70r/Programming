#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string preprocess(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    for (size_t i = 0; i + 1 < s.size(); ++i) {
        if (s[i] == '(' && s[i + 1] == '-') {
            s.insert(i + 1, "0");
        }
    }

    while (s.find("--") != string::npos) {
        s.replace(s.find("--"), 2, "+");
    }

    if (!s.empty() && s[0] == '-') {
        s = "0" + s;
    }

    return s;
}

long long evaluate_expr(const string& s, size_t& i);

long long parse_number(const string& s, size_t& i) {
    long long num = 0;
    while (i < s.size() && isdigit(s[i])) {
        num = num * 10 + (s[i] - '0');
        i++;
    }
    i--; 
    return num;
}

long long evaluate_expr(const string& s, size_t& i) {
    vector<long long> stack;
    long long num = 0;
    char sign = '+';

    while (i < s.size()) {
        char ch = s[i];

        if (isdigit(ch)) {
            num = parse_number(s, i);
        } else if (ch == '(') {
            i++;
            num = evaluate_expr(s, i);
        }

        if (i == s.size() - 1 || ch == '+' || ch == '-' || ch == ')') {
            if (sign == '+') {
                stack.push_back(num);
            } else if (sign == '-') {
                stack.push_back(-num);
            }
            sign = ch;
            num = 0;
        }

        if (ch == ')') break;
        i++;
    }

    long long result = 0;
    for (auto val : stack) result += val;
    return result;
}

int main() {
    string input;
    getline(cin, input);

    input = preprocess(input);
    size_t idx = 0;
    long long result = evaluate_expr(input, idx);

    cout << result << endl;
    return 0;
}
