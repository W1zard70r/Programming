#include <iostream>

using namespace std;

void processArray(int *A, int &n) {
    if (n == 0) return;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *(A + i);
    }
    double avg = (double) (sum) / n;

    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (*(A + i) <= avg) {
            *(A + newSize) = *(A + i);
            newSize++;
        }
    }
    n = newSize;
}

int main() {
    int n;
    cout << "Enter the n" << endl;
    cin >> n;

    int A[n];
    cout << "Enter the array A" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Enter A[" << i << "]" << endl;
        cin >> *(A + i);
    }

    processArray(A, n);

    cout << "There's result" << endl;
    for (int i = 0; i < n; i++) {
        cout << *(A + i) << " ";
    }
    cout << endl;

    return 0;
}
