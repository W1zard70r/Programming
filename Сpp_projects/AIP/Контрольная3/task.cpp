#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
using namespace std;


struct node {
    int data;
    node* next;
};

void push(node*& top, int value) {
    node* newNode = new node{value, top};
    top = newNode;
}

int pop(node*& top) {
    if (!top) return -1;
    node* temp = top;
    int value = temp->data;
    top = top->next;
    delete temp;
    return value;
}

bool isStackEmpty(node* top) {
    return top == nullptr;
}

void clearStack(node*& top) {
    while (top) {
        node* temp = top;
        top = top->next;
        delete temp;
    }
}

void enqueue(node*& front, node*& rear, int value) {
    node* newNode = new node{value, nullptr};
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue(node*& front, node*& rear) {
    if (!front) return -1;
    node* temp = front;
    int value = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return value;
}

bool isQueueEmpty(node* front) {
    return front == nullptr;
}

//чистим очередь
void clearQueue(node*& front, node*& rear) {
    while (front) {
        node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

// читаем файлик
void readStackFromFile(const string& filePath, node*& stackTop) {
    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Ошибка открытия входного файла.\n";
        return;
    }

    string line;
    getline(inFile, line);
    stringstream ss(line);
    int value;
    while (ss >> value) {
        push(stackTop, value);
    }

    inFile.close();
}

// делаем из стека очередь
void convertStackToUniqueQueue(node*& stackTop, node*& queueFront, node*& queueRear, vector<int>& output) {
    unordered_set<int> seen;

    while (!isStackEmpty(stackTop)) {
        int value = pop(stackTop);
        if (seen.find(value) == seen.end()) {
            seen.insert(value);
            enqueue(queueFront, queueRear, value);
            output.push_back(value);
        }
    }
}

// ===== ВЫВОД =====
void outputResults(const vector<int>& output, ostream& out) {
    if (output.empty()) {
        out << "No unique elements found.\n";
        return;
    }

    out << "Unique elements from stack (FIFO order): ";
    for (int val : output) {
        out << val << " ";
    }
    out << "\n";
}

int main() {
    string inputFile, outputFile;
    cout << "Enter input file path: ";
    getline(cin, inputFile);
    cout << "Enter output file name: ";
    getline(cin, outputFile);

    // Стек
    node* stackTop = nullptr;

    // Очередь
    node* queueFront = nullptr;
    node* queueRear = nullptr;

    // Считывание из файла
    readStackFromFile(inputFile, stackTop);

    // Преобразование в очередь
    vector<int> uniqueElements;
    convertStackToUniqueQueue(stackTop, queueFront, queueRear, uniqueElements);

    // Вывод
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error with open input file.\n";
        return 1;
    }

    outputResults(uniqueElements, cout);     // в консоль
    outputResults(uniqueElements, outFile);  // в файл

    // Очистка памяти
    clearQueue(queueFront, queueRear);
    clearStack(stackTop);
    outFile.close();

    return 0;
}
