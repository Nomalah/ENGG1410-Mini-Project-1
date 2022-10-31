#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"
#include "decrypt.h"

// Returning 0 from this function means Encrypt, 1 means Decrypt, -1 means invalid input
int validateFlags(char** argv, int argc, int* filename_index){
    if (argc != 2 && argc != 3) {
        printf("cryptoMagic: %d args given, 2 or 3 required.\n", argc);
        return -1;
    }

    if (!strcmp(argv[1], "-E")) {
        // Encrypt
        if (argc != 3) {
            printf("cryptoMagic: -E flag specified, but file name not specified.\n");
            return -1;
        }
        return 0;
    } else if (!strcmp(argv[1], "-D")) {
        // Decrypt
        if (argc != 3) {
            printf("cryptoMagic: -D flag specified, but file name not specified.\n");
            return -1;
        }
        return 1;
    }

    return 0; // Encrypt by default
}

int main(int argc, char* argv[]) {
    int filename_index = 0;
    int encrypt_or_decrypt = validateFlags(argv, argc, &filename_index);
    if (encrypt_or_decrypt < 0) {
        return encrypt_or_decrypt;
    }
    char* filename = argv[filename_index];
    
    if (encrypt_or_decrypt == 0){
        return encryptFile(filename); // 0 if success, anything else if fail
    } else if (encrypt_or_decrypt == 1){
        return decryptFile(filename); // 0 if success, anything else if fail
    }
    return -1; // Should never be reached.
}

