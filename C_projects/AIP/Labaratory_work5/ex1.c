#include <stdio.h>
#include <math.h>

#define lmax 200

void fill_array(float A[], int *n, FILE *f);

int main()
{
    FILE *f1;
    f1 = fopen("ex1.txt","w");
    float A[lmax];
    int n;

    fill_array(A, &n, f1);

    fclose(f1);

    f1 = fopen("ex1.txt", "r");

    float max_modul = 0;

    for (size_t i = 0; i < n; i++)
    {
        float val;
        fscanf(f1, "%f", &val);
        if (fabs(val) > fabs(max_modul))
        {
            max_modul = val;
        }
        printf("%f\t", val);
    }
    
    fclose(f1);
    
    printf("\nThe value with the maximum module is: %f\n", max_modul);

    return 0;
}


void fill_array(float A[], int *n, FILE *f)
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
    for(float *ui = A; ui < A + *n; ui++)
    {
        printf("Enter values of A[%d]: ", ui - A);
        check = scanf("%f", ui);
        while (getchar() != '\n');
    }

    for (size_t i = 0; i < *n; i++)
    {
        fprintf(f, "%f\n", A[i]);
    }
    printf("\n");
}