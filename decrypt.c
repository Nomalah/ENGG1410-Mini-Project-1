#include <stdlib.h>
#include <stdio.h>

#include "strtools.h"

#include "decrypt.h"

char decryptChar(char comp1, char comp2)
{
    if (comp1 == 'T' && comp2 == 'T')
    {
        return '\t';
    }

    int res = fromHex(comp1) * 16 + fromHex(comp2);
    res += 16;
    if (res > 127)
    {
        return (char)(res - 144 + 32);
    }
    return res;
}

int decryptFile(char *filename_in)
{
    printf("cryptoMagic: Decrypting %s\n", filename_in);
    FILE *file_in = fopen(filename_in, "r");
    if (!file_in)
    {
        printf("cryptoMagic: Could not open input file!\n");
        return -1;
    }
    int basename_len = 0;
    char *basename = getFileBaseName(filename_in, &basename_len);
    char *filename_out = malloc(basename_len + 5); // 4 + 1
    snprintf(filename_out, basename_len + 5, "%s%s", basename, ".txt");
    printf("cryptoMagic: Decrypting to %s\n", filename_out);
    free(basename);
    FILE *file_out = fopen(filename_out, "w");
    free(filename_out);
    if (!file_in)
    {
        printf("cryptoMagic: Could not open output file!\n");
        return -1;
    }

    char c1, c2;
    while ((c1 = fgetc(file_in)) != EOF)
    {
        if (c1 != '\n' && c1 != '\r')
        {
            c2 = fgetc(file_in);
            fprintf(file_out, "%c", decryptChar(c1, c2));
            continue;
        }
        fprintf(file_out, "%c", c1);
    }

    fclose(file_out);
    fclose(file_in);
    printf("cryptoMagic: Successfully decrypted\n");
    return 0; // Success
}