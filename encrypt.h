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
    snprintf(filename_out, basename_len + 5, "%s%s", basename, ".crp");
    printf("cryptoMagic: Encrypting to %s\n", filename_out);
    free(basename);
    FILE* file_out = fopen(filename_out, "w");
    free(filename_out);
    if (!file_in) {
        printf("cryptoMagic: Could not open output file!\n");
        return -1;
    }

    char c = 0;
    while ((c = fgetc(file_in)) != EOF) {
        if (c == '\t') {
            fprintf(file_out, "TT");
        } else if (c == '\n') {
            fprintf(file_out, "\n");
        } else {
            fprintf(file_out, "%X", encryptChar(c));
        }
    }

    fclose(file_out);
    fclose(file_in);
    printf("cryptoMagic: Successfully encrypted\n");
    return 0; // Success
}

#endif // ENCRYPT_H