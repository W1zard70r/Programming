#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <sstream>
#include <ios>

using ll = long long;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::cin.ignore();

    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);

    std::vector <ll> a(n);
    ll x;
    int i = 0;
    while (ss >> x)
    {
        a[i] = x;
        i++;
    }
    std::vector <ll> Aprefxor(n + 1, 0);
    
    for (size_t i = 1; i < n + 1; i++)
    {
        Aprefxor[i] = Aprefxor[i - 1] ^ a[i - 1];
    }
    


    int k;
    std::cin >> k;
    std::cin.ignore();

    for (size_t i = 0; i < k; i++)
    {
        int left, right;
        std::cin >> left >> right;
        std::cin.ignore();

        std::cout << (Aprefxor[right] ^ Aprefxor[left - 1]) << "\n"; 
    }
    
}