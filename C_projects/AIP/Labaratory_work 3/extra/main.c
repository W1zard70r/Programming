#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define lmax 200


void print_matrix(int A[lmax][lmax], int n, int m);
void fill_matrix(int A[lmax][lmax], int *n, int *m);
int* find_first_max(int A[][lmax], int n, int m);
int* find_last_max(int A[][lmax], int n, int m);
void column_replace(int A[][lmax], int n, int m, int *first_max, int *last_max);
void swap(int *a, int *b);

int main()
{
    //Õ¿…“» 1 MAX »  œŒ—À≈ƒÕ»… MAX, œŒÃ≈Õﬂ“‹ —“ŒÀ¡÷€ — Õ»Ã» Ã≈—“¿Ã»
    int A[lmax][lmax], n, m;
    int *imax1, *imax2;
    fill_matrix(A, &n, &m);
    print_matrix(A, n, m);

    imax1 = find_first_max(A, n, m);
    imax2 = find_last_max(A, n, m);

    if (imax1 == imax2)
        printf("There's only one MAX element");
    else
        {
        column_replace(A, n, m, imax1, imax2);
        print_matrix(A, n, m);
        }
    return 0;
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

int* find_first_max(int A[][lmax], int n, int m)
{
    int *m1 = &A[0][0];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (A[i][j] > *m1)
            {
                m1 = &A[i][j];
            }
        }
    }
    return m1;
}

int* find_last_max(int A[][lmax], int n, int m)
{
    int *m1 = &A[0][0];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (A[i][j] >= *m1)
            {
                m1 = &A[i][j];
            }
        }
    }
    return m1;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void column_replace(int A[][lmax], int n, int m, int *first_max, int *last_max)
{
    int column1, column2;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (&A[i][j] == first_max)
            {
                column1 = j;
            }
            else if (&A[i][j] == last_max)
            {
                column2 = j;
            }
        }
    }

    //replace
    for(int i =0; i < n; i++)
        swap(&A[i][column1], &A[i][column2]);
}

