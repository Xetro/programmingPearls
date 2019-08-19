#include <stdio.h>

void main() {
    FILE * fp_in;
    FILE * fp_out;
    char path_out[1024];
    char buff[1024];

    char path_in[] = "./dictionary.txt";
    fp_in = fopen(path_in, "r"); 

    while (fscanf(fp_in, "%s", buff) ==1) {
        printf("%s\n", buff);
    }
}
