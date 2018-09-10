#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int getRandom(int min, int max);

void main() {
    FILE *fp;    
    int max;
    int digit;
    char cwd[1024];

    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/randomnumsuniq");
    srand(time(0));

    printf("Insert max numbers generated: \n");
    scanf("%d", &max);
    printf("Insert max number of digits: \n");
    scanf("%d", &digit);

    int d = pow(10, digit);
    int *x = malloc(sizeof(int)*d);

    if (!x) {
        printf("Out of RAM!");
    }
    
    for(int i = 0; i < d; ++i) {
        x[i] = i;
    }

    fp = fopen(cwd, "w");

    for(int i = 0; i < max; ++i) {
        int rndm = getRandom(i, d - 1);
        int swap = x[i];
        x[i] = x[rndm];
        x[rndm] = swap;
        printf("%d\n", x[i]);
        fprintf(fp, "%d\n", x[i]);
    }

    free(x);
    fclose(fp);
}

int getRandom(int min, int max) {
    int num = (rand() % (max - min + 1) + min);
    return num;
}
