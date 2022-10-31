#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stdlib.h>
#include <stdio.h>

#include "strtools.h"

int encryptChar(char ascii_in) {
    ascii_in -= 16;
    if (ascii_in < 32){
        return ascii_in - 32 + 144;
    }
    return ascii_in;
}

int encryptFile(char* filename_in) {
    printf("cryptoMagic: Encrypting %s\n", filename_in);
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
}

#endif // ENCRYPT_H