#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Student {
    string lastName;
    string firstName;
    string middleName;
    string group;
    vector<int> grades;
    double averageGrade;
};

struct Node {
    Student data;
    Node* prev;
    Node* next;
};

Node* createNode(const Student& student) {
    Node* newNode = new Node;
    newNode->data = student;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

Node* inputDataFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return nullptr;
    }

    Node* head = nullptr;
    Node* tail = nullptr;
    string line;

    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        Student student;
        student.lastName = line;

        if (!getline(inputFile, line)) break;
        student.firstName = line;

        if (!getline(inputFile, line)) break;
        student.middleName = line;

        if (!getline(inputFile, line)) break;
        student.group = line;

        if (!getline(inputFile, line)) break;
        istringstream iss(line);
        int grade;
        double sum = 0.0;
        int count = 0;
        while (iss >> grade) {
            student.grades.push_back(grade);
            sum += grade;
            count++;
        }
        student.averageGrade = (count > 0) ? sum / count : 0.0;

        Node* newNode = createNode(student);
        if (!head) {
            head = tail = newNode;
            head->next = head;
            head->prev = head;
        } else {
            newNode->prev = tail;
            newNode->next = head;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
    }

    inputFile.close();
    return head;
}

Node* filterStudents(Node* head) {
    if (!head) return nullptr;

    Node* newHead = nullptr;
    Node* newTail = nullptr;
    Node* current = head;

    do {
        bool hasBadGrade = false;
        for (int grade : current->data.grades) {
            if (grade < 4) {
                hasBadGrade = true;
                break;
            }
        }

        if (!hasBadGrade) {
            Node* newNode = createNode(current->data);
            if (!newHead) {
                newHead = newTail = newNode;
                newNode->next = newNode;
                newNode->prev = newNode;
            } else {
                newNode->prev = newTail;
                newNode->next = newHead;
                newTail->next = newNode;
                newHead->prev = newNode;
                newTail = newNode;
            }
        }

        current = current->next;
    } while (current != head);

    return newHead;
}

void writeToFile(Node* head, const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Cannot create file " << filename << endl;
        return;
    }

    if (!head) {
        outputFile << "No students meet the criteria." << endl;
        outputFile.close();
        return;
    }

    Node* current = head;
    do {
        outputFile << current->data.lastName << "\n";
        outputFile << current->data.firstName << "\n";
        outputFile << current->data.middleName << "\n";
        outputFile << current->data.group << "\n";
        for (size_t i = 0; i < current->data.grades.size(); ++i) {
            if (i > 0) outputFile << " ";
            outputFile << current->data.grades[i];
        }
        outputFile << "\n";
        
        outputFile << current->data.averageGrade << "\n\n";

        current = current->next;
    } while (current != head);

    outputFile.close();
}

void freeList(Node* head) {
    if (!head) return;

    Node* current = head;
    Node* temp;

    do {
        temp = current->next;
        delete current;
        current = temp;
    } while (current != head);
}

int main() {
    string inputFile, outputFile;

    cout << "Enter input filename: ";
    getline(cin, inputFile);

    cout << "Enter output filename: ";
    getline(cin, outputFile);

    Node* students = inputDataFromFile(inputFile);
    if (!students) {
        return 1;
    }

    Node* filteredStudents = filterStudents(students);

    writeToFile(filteredStudents, outputFile);

    freeList(students);
    freeList(filteredStudents);

    cout << "Processing complete. Results saved to " << outputFile << endl;

    return 0;
}