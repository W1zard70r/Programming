#include <iostream>
#include <limits>
using namespace std;

bool isValidInput();
void inputMatrix(int** matrix, int rows, int cols);
int* findFirstPositive(int** matrix, int rows, int cols);
int* findLastPositive(int** matrix, int rows, int cols);
void printMatrix(int** matrix, int rows, int cols);


int main() {
    int rows, cols;

    // Ввод размеров матрицы
    cout << "Enter the number of Matrix's rows: ";
    while (!(cin >> rows) || rows <= 0 || !isValidInput()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Number type Error! Enter the int value:  ";
    }
    cin.clear();

    cout << "Enter the number of Matrix's columns: ";
    while (!(cin >> cols) || cols <= 0 || !isValidInput()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Number type Error! Enter the int value:  ";
    }
    cin.clear();

    // Выделение памяти для матрицы
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        *(matrix + i) = new int[cols];
    }

    // Ввод матрицы
    inputMatrix(matrix, rows, cols);
    printMatrix(matrix, rows, cols);

    cout << "There's some changes" << endl; 

    // Поиск первого и последнего положительных элементов
    int* firstPositive = findFirstPositive(matrix, rows, cols);
    int* lastPositive = findLastPositive(matrix, rows, cols);

    
    if (firstPositive && lastPositive) {
        if (firstPositive == lastPositive)
        {
            cout << "There's only 1 positive elements, no changes" << endl;    
        } else{    
            swap(*firstPositive, *lastPositive);
            cout << "Elements were changed" << endl;
        }
    } else {
        cout << "There's no positive elements in matrix" << endl;
    }

    printMatrix(matrix, rows, cols);

    // Освобождение памяти
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

bool isValidInput() {
    char ch;
    while (cin.get(ch)) { // Читаем символы по одному
        if (ch == '\n') { 
            return true; 
        }
        if (!isdigit(ch) && ch != '-') { 
            return false; 
        }
    }
    return false;
}
// Функция для ввода матрицы
void inputMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Enter the elements of matrix [" << i << "][" << j << "]: ";
            while (!(cin >> *(*(matrix + i) + j)) || !isValidInput()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Number type Error! Enter the int value: ";
            }
        }
    }
}

// Функция для поиска первого положительного элемента
int* findFirstPositive(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (*(*(matrix + i) + j) > 0) {
                return &*(*(matrix + i) + j);
            }
        }
    }
    return nullptr; // Если положительных элементов нет
}

// Функция для поиска последнего положительного элемента
int* findLastPositive(int** matrix, int rows, int cols) {
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (*(*(matrix + i) + j) > 0) {
                return &*(*(matrix + i) + j);
            }
        }
    }
    return nullptr; // Если положительных элементов нет
}

// Функция для вывода матрицы
void printMatrix(int** matrix, int rows, int cols) {
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
}