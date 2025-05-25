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

    int n, m;
    std::cin >> n >> m;
    std::cin.ignore();

    std::vector <std::vector <ll>> Matrix(n, std::vector <ll>(m, 0));
    std::vector <std::vector <ll>> PrefSumMatrix(n + 1, std::vector <ll>(m + 1, 0));
    for (size_t i = 0; i < n; i++){
        std::string line;
        getline(std::cin, line);
        std::stringstream ss(line);

        for (int j = 0; j < m; ++j) {
            ss >> Matrix[i][j];
        }
    }
    for (size_t i = 1; i < n + 1; i++){
        for (size_t j = 1; j < m + 1; j++){
            PrefSumMatrix[i][j] = PrefSumMatrix[i - 1][j] + PrefSumMatrix[i][j - 1] - PrefSumMatrix[i - 1][j - 1] + Matrix[i - 1][j - 1];      
        }
    }

    int k;
    std::cin >> k;


    for (size_t i = 0; i < k; i++)
    {
        int Xleft, Xright, Yleft, Yright;
        std::cin >> Xleft >> Yleft >> Xright >> Yright;

        std::cout << PrefSumMatrix[Xright][Yright ] - PrefSumMatrix[Xleft - 1][Yright] - PrefSumMatrix[Xright][Yleft - 1] + PrefSumMatrix[Xleft - 1][Yleft - 1]<< "\n"; 
    }
    return 0;
}