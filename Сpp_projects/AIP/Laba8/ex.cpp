#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Функция для проверки, является ли символ допустимым
bool isValidChar(char c) {
    return (c == 'E' || c == 'e' || 
            isdigit(c) || 
            c == '.' || c == '+' || c == '-');
}

// Функция для выделения подстрок
vector<string> extractSubstrings(const vector<string>& strings) {
    vector<string> result;
    
    for (const string& s : strings) {
        string currentSubstring;
        
        for (char c : s) {
            if (isValidChar(c)) {
                currentSubstring += c;
            } else {
                if (!currentSubstring.empty()) {
                    result.push_back(currentSubstring);
                    currentSubstring.clear();
                }
            }
        }
        
        // Добавляем последнюю подстроку, если она не пустая
        if (!currentSubstring.empty()) {
            result.push_back(currentSubstring);
        }
    }
    
    // Удаляем пустые подстроки (на случай, если они появились)
    vector<string> filteredResult;
    for (const string& s : result) {
        if (!s.empty()) {
            filteredResult.push_back(s);
        }
    }
    
    return filteredResult;
}

int main() {
    int n;
    cout << "Введите количество строк: ";
    cin >> n;
    
    // Очистка буфера после ввода числа
    cin.ignore();
    
    if (n <= 0) {
        cout << "Количество строк должно быть положительным числом." << endl;
        return 1;
    }
    
    vector<string> strings;
    for (int i = 0; i < n; ++i) {
        string s;
        cout << "Введите строку " << i+1 << ": ";
        getline(cin, s);
        strings.push_back(s);
    }
    
    vector<string> substrings = extractSubstrings(strings);
    
    if (substrings.empty()) {
        cout << "Не найдено подстрок, удовлетворяющих условиям." << endl;
    } else {
        cout << "\nНайденные подстроки:" << endl;
        for (const string& substr : substrings) {
            cout << substr << endl;
        }
    }
    
    return 0;
}