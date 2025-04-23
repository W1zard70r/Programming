#include <iostream>
#include <limits>
using namespace std;

void inputArray(int* arr, int size, const char* name);
int countOccurrences(int* arr, int size, int value);
void computeArrayC(int* A, int* B, int* C, int sizeA, int sizeB, int& sizeC);
void printArray(int* arr, int size, const char* name);
bool isValidInput();

int main() {
    int sizeA, sizeB;

    // Ввод размеров массивов
    cout << "Enter the length of array A: ";
    while (!(cin >> sizeA) || sizeA <= 0 || !isValidInput()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Value issue! Enter the positive integer value: ";
    }
    cin.clear();

    cout << "Enter the length of array B: ";
    while (!(cin >> sizeB) || sizeB <= 0 || !isValidInput()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Value issue! Enter the positive integer value: ";
    }
    cin.clear();

    // Выделение памяти для массивов
    int* A = new int[sizeA];
    int* B = new int[sizeB];
    int* C = new int[sizeA]; 

    // Ввод массивов
    inputArray(A, sizeA, "A");
    inputArray(B, sizeB, "B");

    // Вывод введённых массивов
    printArray(A, sizeA, "A");
    printArray(B, sizeB, "B");
    
    // Вычисление массива C
    int sizeC = 0;
    computeArrayC(A, B, C, sizeA, sizeB, sizeC);

    // Вывод результата
    printArray(C, sizeC, "C");

    // Освобождение памяти
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}

// Функция для ввода массива
void inputArray(int* arr, int size, const char* name) {
    for (int i = 0; i < size; i++) {
        cout << "Enter the value of " << name << "[" << i << "]: ";
        while (!(cin >> *(arr + i)) || !isValidInput()) {
            cin.clear(); // Очистка флага ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование некорректного ввода
            cout << "Number type Error! Enter the int value: ";
        }
    }
}

// Функция для проверки, сколько раз элемент встречается в массиве
int countOccurrences(int* arr, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (*(arr + i) == value) {
            count++;
        }
    }
    return count;
}

// Функция для вычисления массива C
void computeArrayC(int* A, int* B, int* C, int sizeA, int sizeB, int& sizeC) {
    sizeC = 0;
    for (int i = 0; i < sizeA; i++) {
        if (*(A + i) < 0 && countOccurrences(B, sizeB, *(A + i)) == 1) {
            C[sizeC++] = A[i];
        }
    }
}

// Функция для вывода массива
void printArray(int* arr, int size, const char* name) {
    cout << "There's array " << name << ": ";
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
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