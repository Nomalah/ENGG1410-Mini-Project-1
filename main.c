#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"
#include "decrypt.h"

// Returning 0 from this function means Encrypt, 1 means Decrypt, -1 means invalid input
int validateFlags(char** argv, int argc, char** filename){
    if (argc != 2 && argc != 3) {
        printf("cryptoMagic: %d args given, 2 or 3 required.\n", argc);
        return -1;
    }

    if (!strcmp(argv[1], "-E")) {
        // Encrypt
        if (argc != 3) {
            printf("cryptoMagic: -E flag specified, but file name not specified.\n");
            return -1; // Failure
        }
        *filename = argv[2]; // filename is in the 3rd param
        return 0; // Encrypt
    } else if (!strcmp(argv[1], "-D")) {
        // Decrypt
        if (argc != 3) {
            printf("cryptoMagic: -D flag specified, but file name not specified.\n");
            return -1; // Failure
        }
        *filename = argv[2]; // filename is in the 3rd param
        return 1; // Decrypt
    }

    *filename = argv[1]; // filename is in the 2nd param
    return 0; // Encrypt by default
}

int main(int argc, char* argv[]) {
    char* filename = NULL;
    int encrypt_or_decrypt = validateFlags(argv, argc, &filename);
    if (encrypt_or_decrypt < 0) {
        return encrypt_or_decrypt;
    }
    
    if (encrypt_or_decrypt == 0){
        return encryptFile(filename); // 0 if success, anything else if fail
    } else if (encrypt_or_decrypt == 1){
        return decryptFile(filename); // 0 if success, anything else if fail
    }
    return -1; // Should never be reached.
}

