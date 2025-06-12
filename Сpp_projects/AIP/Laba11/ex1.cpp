#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int gcd_recursive(int n, int m) {
    if (n == m) {
        return n;
    } else if (n > m) {
        return (m != 0) ? gcd_recursive(n % m, m) : n;
    } else {
        return (n != 0) ? gcd_recursive(n, m % n) : m;
    }
}

int gcd_iterative(int n, int m) {
    while (m != 0 && n != 0) {
        if (n > m) {
            n %= m;
        } else {
            m %= n;
        }
    }
    return (m == 0) ? n : m;
}

int main() {
    int num1, num2;
    
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    auto start_rec = high_resolution_clock::now();
    int result_rec = gcd_recursive(num1, num2);
    auto end_rec = high_resolution_clock::now();
    auto duration_rec = duration_cast<nanoseconds>(end_rec - start_rec);

    cout << "\nRecursive GCD: " << result_rec << endl;
    cout << "Time taken (recursive): " << duration_rec.count() << " ns" << endl;

    auto start_iter = high_resolution_clock::now();
    int result_iter = gcd_iterative(num1, num2);
    auto end_iter = high_resolution_clock::now();
    auto duration_iter = duration_cast<nanoseconds>(end_iter - start_iter);

    cout << "Iterative GCD: " << result_iter << endl;
    cout << "Time taken (iterative): " << duration_iter.count() << " ns" << endl;

    return 0;
}