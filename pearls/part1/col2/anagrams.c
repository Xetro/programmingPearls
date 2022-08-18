#include <stdio.h>
#include <string.h>

#include "util/hash_table.h"

#define WORDMAX 100

char *getSignature(char word[]);

void main() {
    char word[WORDMAX];
    ht_hash_table *ht = ht_new();

    FILE *fp_in;
    char path_in[] = "./dictionary.txt";
    char buff[1024];

    printf("Insert word you want to search anagrams for: \n");
    fgets(word,WORDMAX,stdin);

    
    fp_in = fopen(path_in, "r");
    int j = 0;
    while (fscanf(fp_in, "%s", buff) == 1 && j < 10000) {
/*        printf("word: %s ", buff);*/
        char *sign = getSignature(buff);
        ht_insert(ht, sign, buff);
        j++;
    }
    printf("FINAL SIZE: %d count: %d\n", ht->size, ht->count);
}

char *getSignature(char word[]) {
    char temp;
    static char signature[WORDMAX];
    int i, j;

    strcpy(signature, word);
    int length = strlen(word);
    
    for (i = 0; i < length-1; i++) {
        for (j = i+1; j < length; j++) {
            if (signature[i] > signature[j]) {
                temp = signature[i];
                signature[i] = signature[j];
                signature[j] = temp;
            }
        }
    }
    return signature;
}



