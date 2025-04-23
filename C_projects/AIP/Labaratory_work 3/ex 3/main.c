#include <stdio.h>
#include <stdlib.h>

#define lmax 200

void fill_array(int A[], int *n)
{
    int check;
    float fv;
    do
    {
        printf("Enter the value of 0 < n < %d for array A[0:n-1]\n", lmax);
        check = scanf("%f", &fv);
        *n = (int) fv;
        while (getchar() != '\n');
    } while (fv != *n || check != 1 || *n > lmax || *n < 1);
    printf("\n");
    printf("Enter the values of elements for array A[0:%d]\n", *n - 1);
    for(int *ui = A; ui < A + *n; ui++)
    {
        do
        {
            printf("Enter values of A[%d]: ", ui - A);
            check = scanf("%f", &fv);
            *ui = (int)fv;
            while (getchar() != '\n');
        } while (check != 1 || *ui != fv);
    }
    printf("\n");
}

void print_array(int A[], int n)
{
    for (int *ui = A; ui < A + n; ui++)
    {
        printf("%4d\t", *ui);
    }
    printf("\n");
}
void count_elements(int A[], int n, int res[])
{
    for(int *ui = A; ui < A + n; ui++)
    {
        *(res + (ui - A)) = 0;
        for(int *uj = A; uj < A + n; uj++)
        {
            if (*ui == *uj)
                (*(res + (ui - A)))++;
        }
    }
}

void make_set(int A[], int n, int res[], int *k)
{
    *k = 0;
    for(int *ui = A; ui < A + n; ui++)
    {
        int *uj = res;
        while(uj < res + *k && *ui != *uj)
            uj++;
        if (uj == res + *k )
        {
            *(res + (*k)++) = *ui;
        }
    }
}

int main()
{
    printf("Laboratoy work 3\n\n");
    printf("Exercise 3\n\n");

    int A[lmax], n;
    fill_array(A, &n);
    printf("There is array A[0:%d]:", n-1);
    print_array(A, n);
    printf("\n");

    int B[n];
    count_elements(A, n, B);
    printf("There is array  B[0:%d] with numbers of elements in A:", n-1);
    print_array(B, n);
    printf("\n");

    int C[lmax], k;
    make_set(A, n, C, &k);
    printf("There is array C[0:%d] with unique elements of A:", k-1);
    print_array(C, k);

    return 0;
}
//    int A[3][5] = {
//    {1,2,3,52, 34},
//    {6,7,8,41, 123},
//    {9,10,11,31, 321}
//    };
//
//    int n = 3, m = 5;
//
//    for(int (*ui)[m] = A; ui < A + n; ui++)
//    {
//        for(int *uj = ui; uj < *ui + m; uj++)
//            printf("%d\t", *uj);
//        printf("\n");
//    }
