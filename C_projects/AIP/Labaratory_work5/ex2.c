#include <stdio.h>
#include <math.h>

#define lmax 200

void deln(char *s)
{ for (; *s && *s!='\n'; s++);
*s='\0';
}

int main()
{
    FILE *f2;
    f2 = fopen("ex2.txt","r");
    if (f2 == NULL) {
        perror("Error opening file");
        return 1;
    }
    char A[lmax][lmax];
    
    FILE *f3 = fopen("ex2_result.txt","w");
    
    int k = 0;
    int KDEL = 0;
    while(fgets(A[k], lmax , f2) != NULL)
    {
        deln(A[k]); //замена '\n' на'\0'
        int kdel = 0;
        char *temp = A[k];

        //puts(A[k]);
        while (*temp)
        {
            //printf("%c\n",*temp);
            if (*temp == '0' || *temp == '2' || *temp == '4' || *temp == '6' || *temp == '8'){
                kdel++;
            }
            else{
                *(temp - kdel) = *temp;
            }
            temp++;
            //puts(temp);
        }
        *(temp - kdel) = '\0'; 
        //puts(A[k]);
        KDEL += kdel;
        fputs(A[k], f3);
        fputc('\n', f3);
        k++;
    }
    fclose(f2);
    fclose(f3);

    f3 = fopen("ex2_result.txt", "r");
    while (fgets(A[k], lmax , f3) != NULL)
    {
        deln(A[k]);
        puts(A[k]);
    }

    if (KDEL == 0)
    {
        printf("There's no changes");      
    }
    
    
    fclose(f3);
    

    return 0;
}