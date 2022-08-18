#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void setBit(int * byte, int position);
void printArr(int * arr, int len);
int checkBit(int * byte, int position);

void main() {
        FILE * fp;
        char cwd[1024];
        char path_in[1024];
        char path_out[1024];
        int buff;
        int byte[312500] = { 0 };
        
        getcwd(cwd, sizeof(cwd));

        strcpy(path_in, cwd);
        strcpy(path_out, cwd);
        strcat(path_in, "/randomnumsuniq");
        strcat(path_out, "/sorted");

        fp = fopen(path_in, "r");
        
        while ( fscanf(fp, "%d", &buff) == 1) {
            setBit(byte, buff);
        }
        fclose(fp);

        fp = fopen(path_out, "w");

        for(int i = 0; i < 10000000; ++i) {
            int bit = checkBit(byte, i);
            if (bit == 1) {
                fprintf(fp, "%07d\n", i);
            }
        }
        fclose(fp);
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

