#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

#define strLEN 810

bool isRUalpha(char c);
size_t exercise1(char ss[][strLEN], size_t k, char goodstr[][strLEN]);
char *exercise2(char A[][strLEN], size_t m);
bool exercise3(char *A);

int main() 
{   //use Windows 1251 & write "chcp 1251" in cmd
    setlocale(LC_ALL, "Russian");
    
    float fv;
    int k;
    do {
        printf("Enter the value of 0 < k < 200, it will be length of array A[]\n");
        scanf("%f", &fv);
        while(getchar() != '\n');
    } while (fv < 1 || fv != (int)fv || fv > 200);
    k = fv;
    char A[k][strLEN];
    printf("\nEntter the strings:\n");
    for (size_t i = 0; i < k; i++) 
    {
        gets(A[i]);
    }
    printf("\n");
    printf("There's array A with strings:\n");
    for (size_t i = 0; i < k; i++) {
        puts(A[i]);
    }
    printf("\n");

    char B[strLEN][strLEN];
    size_t m = exercise1(A, k, B);
    if (m > 0) {
        printf("Exercise 1:\n");
        for (size_t i = 0; i < m; i++) {
            puts(B[i]);
        }
        printf("\n");
        char *ex2_res = exercise2(B, m);
        if (ex2_res) {
            printf("Exercise 2\n");
            puts(ex2_res);
            printf("\n");
            if (exercise3(ex2_res)) 
            {
                printf("Exercise 3:\n");
                puts(ex2_res);
            } 
            else 
            {
                puts("There's no Russian letters, so there's no changes in string");
            }
        } 
        else 
        {
            printf("No one string doesn't have digits in the end\n");
            printf("Task 3 is impossible to complete");
        }
    } 
    else 
    {
        printf("There's no any strings with russian letter or digits\n");
        printf("Task 2 and Task 3 are impossible to complete");
    }
    return 0;
}

bool isRUalpha(char c) {
    return (c >= 'À' && c <= 'ß') || (c >= 'à' && c <= 'ÿ') || c == '¸' || c == '¨' ;
}

size_t exercise1(char ss[][strLEN], size_t k, char goodstr[][strLEN]) {
    size_t m = 0;
    for (size_t i = 0; i < k; i++) {
        char *pts = ss[i];
        while (*pts) {
            if (isRUalpha(*pts) || isdigit(*pts)) {
                char *pts2 = pts;
                while (*pts && (isRUalpha(*pts) || isdigit(*pts))) {
                    pts++;
                }
                strncpy(goodstr[m], pts2, pts - pts2);
                goodstr[m][pts - pts2] = '\0';
                m++;
            } else {
                pts++;
            }
        }
    }
    return m;
}

char *exercise2(char A[][strLEN], size_t m) {
    char *result = NULL;
    int minlen = -1;
    for (size_t i = 0; i < m; i++) {
        char *pend = A[i] + strlen(A[i]) - 1;
        while (pend >= A[i] && isdigit(*pend)) {
            pend--;
        }
        int digit_len = A[i] + strlen(A[i]) - 1 - pend;
        if (digit_len > 0 && (digit_len < minlen || minlen == -1)) {
            result = A[i];
            minlen = digit_len;
        }
    }
    return result;
}

bool exercise3(char *A) {
    int kdel = 0;
    char *write = A;
    while (*A) {
        if (!isRUalpha(*A)) {
            *write++ = *A;
        } else {
            kdel++;
        }
        A++;
    }
    *write = '\0';
    return kdel > 0;
}