#ifndef STRTOOLS_H
#define STRTOOLS_H

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


int fromHex(char ascii_char) {
    if (ascii_char >= 'A'){
        return ascii_char - 'A' + 10;
    }
    return ascii_char - '0';
}

#endif // STRTOOLS_H