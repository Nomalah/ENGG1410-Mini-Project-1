#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* getFileBaseName(char* path, int* length_out) {
    char* dir_sep = strrchr(path, '/');
    char* ext_sep = strrchr(path, '.');
    char* end_str = strrchr(path, '\0');
    if (ext_sep < dir_sep) { // no file extension
        *length_out = end_str - dir_sep;
        return strndup(dir_sep, end_str - dir_sep);
    }
    *length_out = end_str - dir_sep;
    return strndup(dir_sep, end_str - ext_sep);
}

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

int encryptFile(char* filename_in) {
    FILE* file_in = fopen(filename_in, "r");
    if (!file_in) {
        printf("Could not open input file!\n");
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
        printf("Could not open output file!\n");
        return -1;
    }
    

}

int decryptFile(char* filename_in) {
    FILE* file_in = fopen(filename_in, "r");
    int basename_len = 0;
    char* basename = getFileBaseName(filename_in, &basename_len);
    char* filename_out = malloc(basename_len + 5); // 4 + 1
    snprintf(filename_out, basename_len, "%s%s", basename, ".txt");
    free(basename);
    FILE* file_out = fopen(filename_out, "w");
    free(filename_out);

}

int encryptChar(char ascii_in) {
    ascii_in -= 16;
    if (ascii_in < 32){
        return ascii_in - 32 + 144;
    }
    return ascii_in;
}

int fromHex(char ascii_char) {
    if (ascii_char >= 'A'){
        return ascii_char - 'A' + 10;
    }
    return ascii_char - '0';
}

char decryptChar(char comp1, char comp2) {
    if (comp1 == 'T' && comp2 == 'T'){
        return '\t';
    }

    int res = fromHex(comp1) * 16 + fromHex(comp2);
    res += 16;
    if (res > 127) {
        return (char)(res - 144 + 32);
    }
    ascii_in -= 16;
    if (ascii_in < 32){
        return ascii_in - 32 + 144;
    }
    return ascii_in;

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

