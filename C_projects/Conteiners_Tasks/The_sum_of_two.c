#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    return int_a - int_b;
}


int main()
{
    int a[] = {5, 2, 1, 4, 7, 2};
    const int n = sizeof(a)/sizeof(int);



    qsort(a, n, sizeof(int), compare_ints);
    for(size_t i = 0;i < n; i++)
        printf("%d\t",a[i]);

    return 0;
}
