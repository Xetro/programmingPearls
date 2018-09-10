#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

void setBit(int * byte, int position);
int checkBit(int * byte, int position);

void main() {
    FILE * fp_in;
    FILE * fp_out;
    char cwd[1024];
    char path_in[1024];
    char path_out[1024];
    int buff;
    int memsize;
    int arraysize;
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

    arraysize  = (memsize * 1024) / 4;
    max = pow(10, max);
    max_stored = arraysize * 32;
    passes = max / max_stored;
    remainder = max % max_stored;

    printf("arrsize: %d, max: %d, max_stored: %d, passes: %d, remainder: %d\n", arraysize, max, max_stored, passes, remainder);

    int *byte = malloc(sizeof(int) * arraysize);

    fp_in = fopen(path_in, "r");
    fp_out = fopen(path_out, "w");
 
    for (int pass = 0; pass < passes; ++pass) {
        int low = pass * max_stored;
        int high = (pass + 1) * max_stored;

        while (fscanf(fp_in, "%d", &buff) == 1) {
            if (buff >= low && buff < high) {
                int bit = buff - pass * max_stored;
                setBit(byte, bit);
            }
        }

        for (int j = 0; j < max_stored; ++j) {
            int bit = checkBit(byte, j);
            if (bit == 1) {
                int final = j + pass * max_stored;
                fprintf(fp_out, "%d\n", final);
            }       
        }

        for (int k = 0; k < arraysize; ++k) {
            byte[k] = 0;
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
                setBit(byte, bit);
            }
        }

        for (int i = 0; i < max_stored; ++i) {
            int check = checkBit(byte, i);
            if (check == 1) {
                int final = i + passes * max_stored;
                fprintf(fp_out, "%d\n", final);
            }
        }
    }

    free(byte);
    fclose(fp_in);
    fclose(fp_out);
}

void setBit(int * byte, int position) {
        int i = position / 32;
        int k = position % 32;
 
        unsigned int flag = 1;

        flag = flag << k;

        byte[i] = byte[i] | flag;
}

int checkBit(int * byte, int position) {
        int i = position / 32;
        int k = position % 32;

        unsigned int flag = 1;

        flag = flag << k;

        if (byte[i] & flag) {
            return 1;
        } else {
            return 0;
        }
}
