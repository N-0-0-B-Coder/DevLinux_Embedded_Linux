#include "strutils.h"

char* str_reverse(char* string) {
    if (string == NULL) {
        printf("Error: NULL pointer passed to str_reverse.\n");
        return NULL;
    }

    size_t len = strlen(string);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
    return string;
}

char* str_trim(char* string) {
    if (string == NULL) {
        printf("Error: NULL pointer passed to str_trim.\n");
        return NULL;
    }

    size_t len = strlen(string);
    // Trim leading spaces
    for (size_t i = 0; i < len; i++) {
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            memmove(string, &string[i], len - i + 1);
            break;
        }

        if (i == len - 1) {
            // The string is all spaces
            string[0] = '\0';
            return string;
        }
    }

    // Trim trailing spaces
    len = strlen(string);
    for (int i = len - 1; i >= 0; i--) {
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            string[i + 1] = '\0';
            break;
        }
    }

    return string;
}

int str_to_int(char* string) {
    if (string == NULL) {
        printf("Error: NULL pointer passed to str_to_int.\n");
        return 0;
    }

    int result = 0;
    int sign = 1;
    size_t i = 0;

    // Handle optional sign
    if (string[0] == '-') {
        sign = -1;
        i++;
    } else if (string[0] == '+') {
        i++;
    }

    for (; string[i] != '\0'; i++) {
        if (string[i] < '0' || string[i] > '9') {
            printf("Error: Non-numeric character encountered in str_to_int.\n");
            return -1;
        }
        result = result * 10 + (string[i] - '0');
    }
    return sign * result;
}