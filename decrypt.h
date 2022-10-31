#ifndef DECRYPT_H
#define DECRYPT_H

#include <stdlib.h>
#include <stdio.h>

#include "strtools.h"

char decryptChar(char comp1, char comp2) {
    if (comp1 == 'T' && comp2 == 'T'){
        return '\t';
    }

    int res = fromHex(comp1) * 16 + fromHex(comp2);
    res += 16;
    if (res > 127) {
        return (char)(res - 144 + 32);
    }
    return res;
}

int decryptFile(char* filename_in) {
    printf("cryptoMagic: Decrypting %s\n", filename_in);
    FILE* file_in = fopen(filename_in, "r");
    if (!file_in) {
        printf("cryptoMagic: Could not open input file!\n");
        return -1;
    }
    int basename_len = 0;
    char* basename = getFileBaseName(filename_in, &basename_len);
    char* filename_out = malloc(basename_len + 5); // 4 + 1
    snprintf(filename_out, basename_len, "%s%s", basename, ".txt");
    free(basename);
    FILE* file_out = fopen(filename_out, "w");
    free(filename_out);
    if (!file_in) {
        printf("cryptoMagic: Could not open output file!\n");
        return -1;
    }
    
    fclose(file_out);
    fclose(file_in);
    return 0; // Success
}

#endif // DECRYPT_H