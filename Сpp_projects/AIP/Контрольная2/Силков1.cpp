#include <iostream>

using namespace std;
const int lmax = 200;


bool existsInB(int product, int B[lmax], int k) {
    for (int i = 0; i < k; i++) {
        if (B[i] == product) return true;
    }
    return false;
}


int makeC(int n, int m, int A[lmax][lmax], int k, int B[lmax], int C[lmax*lmax])
{
    int C_size = 0;
    for (int j = 0; j < m; j++)
    {
        int last_positive_index = -1;
        int last_negative_index = -1;

        for (int i = 0; i < n; i++)
        {
            if (A[i][j] < 0)
            {
                last_negative_index = i;
            }
            else if (A[i][j] > 0)
            {
                last_positive_index = i;
            }
        }
        if (last_positive_index != -1 && last_negative_index != -1 && last_positive_index < last_negative_index) {
            // мне кажется тут сначала должен идти положительный, потом отрицательный
            // в задании вариант отрицательный положительный не указан
            int product = 1;
            int temp[lmax];
            int temp_size = 0;

            for (int i = last_positive_index + 1; i < last_negative_index; i++) {
                temp[temp_size++] = A[i][j];
                product *= A[i][j];
            }

            if (temp_size > 0 && existsInB(product, B, k)) {
                for (int i = 0; i < temp_size; i++) {
                    C[C_size++] = temp[i];
                }
            }
        }
    }
    
    return C_size;
}


void printArray(int C[lmax * lmax], int C_size) {
    cout << "There's massive C: ";
    if (C_size == 0) {
        cout << "It's empty";
    } else {
        for (int i = 0; i < C_size; i++) {
            cout << C[i] << " ";
        }
    }
    cout << endl;
}


int main()
{
    int n, m, k;
    int A[lmax][lmax];
    int B[lmax];
    cout << "Enter the n" << endl;
    cin >> n;
    cout << "Enter the m" << endl;
    cin >> m;
    cout << "Enter the elements of matrix A" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << "Enter A[" << i << "][" << j << "]" << endl;
            cin >> A[i][j];
        }   
    }

    cout << "There's matrix A" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << A[i][j] << " ";
        }  
        cout << endl; 
    }
    cout << "Enter the k" << endl;
    cin >> k;
    
    cout << "Enter the elements of array B" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << "Enter B[" << i << "]" << endl;
        cin >> B[i];
    }
    cout << "There's array B" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << B[i] << " ";
    }
    cout << endl;
    int C_size = 0;
    int C[lmax*lmax];

    C_size = makeC(n, m, A, k, B, C);
    printArray(C, C_size);
    return 0;
}