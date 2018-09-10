#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

void increaseCount(int *index, int position);
int checkCount(int *index, int position);

void main() {
    FILE * fp_in;
    FILE * fp_out;
    char cwd[1024];
    char path_in[1024];
    char path_out[1024];
    int buff;
    int memsize;
    int index_size;
    int max;
    int max_stored;
    int passes;
    int remainder;

    getcwd(cwd, sizeof(cwd));

    strcpy(path_in, cwd);
    strcpy(path_out, cwd);

    strcat(path_in, "/randomnumsuniq");
    strcat(path_out, "/sorted");

    printf("Insert max memory size in KiB:  \n");
    scanf("%d", &memsize);

    printf("Insert number of digits of largest number:  \n");
    scanf("%d", &max);

    //index_size = (memsize * 1024) / 4;
    max = pow(10, max);
    index_size = max / 8;
    max_stored = index_size * 8;
    passes = max / max_stored;
    remainder = max % max_stored;

    printf("index_size: %d, max: %d, max_stored: %d, passes: %d, remainder: %d\n", index_size, max, max_stored, passes, remainder);

    int *index = malloc(sizeof(int) * index_size);
    
    fp_in = fopen(path_in, "r");
    fp_out = fopen(path_out, "w");
 
    for (int pass = 0; pass < passes; ++pass) {
        int low = pass * max_stored;
        int high = (pass + 1) * max_stored;
        while (fscanf(fp_in, "%d", &buff) == 1) {
            if (buff >= low && buff < high) {
                int bit = buff - pass * max_stored;
                increaseCount(index, bit);
            }
        }

        for (int j = 0; j < max_stored; ++j) {
            int count = checkCount(index, j);
            int final = j + pass * max_stored;
            for (count; count > 0; --count) {
                fprintf(fp_out, "%d\n", final);
            }
        }

        for (int k = 0; k < index_size; ++k) {
            index[k] = 0;
        }

        rewind(fp_in);
    }

    if (remainder > 0) {
        int low = passes * max_stored;
        int high = passes * max_stored + remainder;

        printf("low: %d, high: %d\n", low, high);

        while (fscanf(fp_in, "%d", &buff) == 1) {
            if (buff >= low && buff < high) {
                int bit = buff - passes * max_stored;
                increaseCount(index, bit);
            }
        }

        for (int i = 0; i < max_stored; ++i) {
            int count = checkCount(index, i);
            int final = i + passes * max_stored;
            for (count; count > 0; --count) {
                fprintf(fp_out, "%d\n", final);
            }
        }
    }

    free(index);
    fclose(fp_in);
    fclose(fp_out);
}

int checkCount(int *index, int position) {
    int i = position / 8;
    int k = position % 8;

    unsigned int flag = 15 << (k * 4);

    int result = (index[i] & flag) >> (k * 4);
    return result;
}

void increaseCount(int *index, int position) {
    int i = position / 8;
    int k = position % 8;
    int current =  checkCount(index, position);
    
    index[i] ^= (current << (k * 4));

    int flag = (current + 1) << (k * 4);

    index[i] |= flag;
}
