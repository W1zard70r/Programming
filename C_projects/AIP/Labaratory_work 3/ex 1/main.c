#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float XY_formula(char name, float a, float b, float c, float d, float e, float f)
{
    if (name == 'X')
    {
        if (a*e == b * d)
        {
            printf("X doesn't exist\n");
            return NAN;
        }
        return (c * e - b * f) / (a * e - b * d);
    }
    else if (name == 'Y')
    {
        if (a*e == b * d)
        {
            printf("Y doesn't exist\n");
            return NAN;
        }
        return (a * f - c * d) / (a * e - b * d);
    }
}

void check_no_string(float *value)
{
    int k;
    do
    {
        k = scanf("%f",value);
        while(getchar()!='\n');
    }while(k == 0);
}

int main()
{
    printf("Laboratory work 3\n\n");
    printf("Exercise 1:\n");

    printf("\n");
    float a,b,c,d,e,f;
    printf("Write value of a: ");
    check_no_string(&a);

    printf("Write value of b: ");
    check_no_string(&b);

    printf("Write value of c: ");
    check_no_string(&c);

    printf("Write value of d: ");
    check_no_string(&d);

    printf("Write value of e: ");
    check_no_string(&e);

    printf("Write value of f: ");
    check_no_string(&f);

    printf("\n");
    float x = XY_formula('X',a,b,c,d,e,f);
    float y = XY_formula('Y',a,b,c,d,e,f);

    if (!isnan(x))
        printf("There is result: x = %f, y = %f", x, y);
    return 0;
}
