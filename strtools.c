#include <string.h>
#include "strtools.h"

char *getFileBaseName(char *path, int *length_out)
{
    char *dir_sep = strrchr(path, '/');
    char *ext_sep = strrchr(path, '.');
    char *end_str = strrchr(path, '\0');
    if (!dir_sep)
    { // if dir_sep is not found
        dir_sep = path;
    }
    if (ext_sep < dir_sep)
    { // no file extension
        *length_out = end_str - dir_sep;
        return strndup(dir_sep, end_str - dir_sep);
    }
    *length_out = ext_sep - dir_sep;
    return strndup(dir_sep, ext_sep - dir_sep);
}

int fromHex(char ascii_char)
{
    if (ascii_char >= 'A')
    {
        return ascii_char - 'A' + 10;
    }
    return ascii_char - '0';
}