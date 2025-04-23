#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define lmax 200

void fill_matrix(int A[lmax][lmax], int *n, int *m)
{
    int check;
    float fv1, fv2, fv3;

    do
    {
        printf("Enter the value of 0 < n < %d and 0 < m < %d for matrix A[0:n-1][0:m-1]\n", lmax, lmax);
        check = scanf("%f %f", &fv1, &fv2);
        *n = (int) fv1;
        *m = (int) fv2;
    while (getchar() != '\n');
    } while (fv1 != *n || fv2 != *m || check != 2 || *n > lmax || *n < 1 || *m > lmax || *m < 1 );

    printf("\n");
    printf("Enter the values of elements matrix A[0:%d][0:%d]\n", *n - 1, *m - 1);

    for (int *ui = *A; ui < *A + *n * lmax; ui+= lmax)
    {
        for (int* uj = ui; uj < ui + *m; uj++)
        {
            do
            {
                printf("Enter values of A[%d][%d]: ", (ui - *A)/lmax, uj - ui);
                check = scanf("%f", &fv3);
                *uj = (int) fv3;
                while (getchar() != '\n');
            } while (check != 1 || *uj != fv3);
        }
    }
}
void print_matrix(int A[lmax][lmax], int n, int m)
{
    printf("\n");
    printf("There is matrix A[0:%d][0:%d]:\n", n-1, m-1);

    for (int *ui = *A; ui < *A + n * lmax; ui+= lmax)
    {
        for (int* uj = ui; uj < ui + m; uj++)
        {
            printf("%4d\t", *uj);
        }
        printf("\n");
    }
    printf("\n\n");
}

int Max_min_delta(int A[lmax][lmax], int n, int m)
{
    int nowdelta, max_mindelta = -1;
    if (m > 1)
    {
        for (int *ui = *A; ui < *A + n * lmax; ui+= lmax)
        {
            int mindelta = -1;
            for (int* uj = ui + 1; uj < ui + m; uj++)
            {
                nowdelta = abs(*uj   - *(uj - 1));
                if (nowdelta < mindelta || mindelta == -1)
                    mindelta = nowdelta;
            }
            if (mindelta > max_mindelta)
                max_mindelta = mindelta;
        }
    }
    return max_mindelta;
}

int main()
{
    printf("Laboratory Work 3\n\n");
    printf("Exercise 2\n\n");

    int A[lmax][lmax], n, m;

    fill_matrix(A, &n, &m);
    print_matrix(A, n, m);

    int result = Max_min_delta(A, n, m);

    if (result != -1)
        printf("The result: %d\n",result);
    else
        printf("There is only 1 column, it is impossible to calculate the difference\n");
    return 0;
}




