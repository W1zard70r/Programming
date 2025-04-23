#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cctype>

using namespace std;

// Check if character is allowed in substrings
bool isAllowedChar(char c) {
    return isdigit(c) || c == 'E' || c == '.' || c == '+' || c == '-';
}

// Extract valid substrings manually (Part 1)
vector<string> extractSubstrings(const string& s) {
    vector<string> result;
    string temp = "";

    for (char c : s) {
        if (isAllowedChar(c)) {
            temp += c;
        } else {
            if (!temp.empty()) {
                result.push_back(temp);
                temp = "";
            }
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}

// Count the number of operators (+ - / *)
int countOperators(const string& s) {
    int count = 0;
    for (char c : s)
        if (c == '+' || c == '-' || c == '/' || c == '*')
            ++count;
    return count;
}

// Find substring with minimum number of operations (Part 2)
string findMinOperationsSubstring(const vector<string>& substrings) {
    string result;
    int minOps = INT_MAX;

    for (const string& s : substrings) {
        int ops = countOperators(s);
        if (ops < minOps) {
            minOps = ops;
            result = s;
        }
    }
    return result;
}

// Insert '0' before every '1' (Part 3)
string transformString(const string& s) {
    string result;
    for (char c : s) {
        if (c == '1')
            result += '0';
        result += c;
    }
    return result;
}

int main() {
    int n;
    cout << "Enter number of input lines: ";
    cin >> n;
    cin.ignore();

    vector<string> originalLines(n);
    vector<vector<string>> allSubstrings(n);

    cout << "Enter the lines:" << endl;
    for (int i = 0; i < n; ++i) {
        getline(cin, originalLines[i]);
        allSubstrings[i] = extractSubstrings(originalLines[i]);
    }

    // Print valid substrings
    vector<string> collectedSubstrings;
    for (const auto& subs : allSubstrings) {
        for (const string& s : subs) {
            collectedSubstrings.push_back(s);
        }
    }

    if (collectedSubstrings.empty()) {
        cout << "No valid substrings found." << endl;
        return 0;
    }
    else{
        cout << "There's valid substrings: " << endl;
        vector<string> collectedSubstrings;
        for (const auto& subs : allSubstrings) {
            for (const string& s : subs) {
                cout << s << endl;
            }
        }
    }

    string target = findMinOperationsSubstring(collectedSubstrings);
    cout << "Substring with minimum operations: " << target << endl;

    // Find index of the original line containing the target substring
    int sourceLineIdx = -1;
    for (int i = 0; i < n; ++i) {
        for (const string& s : allSubstrings[i]) {
            if (s == target) {
                sourceLineIdx = i;
                break;
            }
        }
        if (sourceLineIdx != -1) break;
    }

    if (sourceLineIdx != -1) {
        string transformed = transformString(originalLines[sourceLineIdx]);
        cout << "Transformed line: " << transformed << endl;
    } else {
        cout << "Original line not found." << endl;
    }

    return 0;
}
