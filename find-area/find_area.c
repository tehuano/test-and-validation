#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef short int c_int;

int algoritmo(c_int n);
char isNumber(char *text);

int main(c_int argc,char* argv[]) { 
    int counter;
    c_int n = 0;
    long long int n2; 
    clock_t start_t, end_t, total_t;
    
    printf("Program Name Is: %s\n",argv[0]); 
    if(1 == argc) {
        printf("No Extra Command Line Argument Passed.\n");
    }
    if(argc >= 2) { 
        for(counter=0;counter<argc;counter++) 
            printf("argv[%d]: %s\n",counter,argv[counter]);
        n2 = atoi(argv[1]);
        if (n2 < 0 || n2 > 32767 || !isNumber(argv[1])) {
            printf("No valid input.\n");
            return 0;
        }
        n = n2;
    } else {
        printf("Number Of Arguments Passed: %d, closing program\n",argc); 
        return 0;
    }

    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

    printf("n = %d, p = %d\n", n, algoritmo(n));

    end_t = clock();
    printf("Ending of the program, end_t = %ld\n", end_t);
    
    total_t = (double)(end_t - start_t);// / CLOCKS_PER_SEC;
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    printf("Total time taken by CPU: %d\n", total_t  );
    printf("Exiting of the program...\n");
    return 0; 
}

int algoritmo(c_int n) {
    int ret = 0;
    //int x, t;
    if (0 == n) {
        ret = 0;
    } else if (1 == n){
        ret = 1;
    } else {
        ret = (n + n) * (n - 1) + 1;
    }
    return ret;
}

char isNumber(char *text)
{
    int j;
    j = strlen(text);
    while(j--)
    {
        if(text[j] >= '0' && text[j] <= '9')
            continue;

        return 0;
    }
    return 1;
}
