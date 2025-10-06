#include "strutils.h"

void main(void) {
    char str1[] = "Hello, World!";
    char str2[] = "   Trim me!   ";
    char str3[] = "12345";

    printf("Original: '%s'\n", str1);
    printf("Reversed: '%s'\n\n", str_reverse(str1));

    printf("Original: '%s'\n", str2);
    printf("Trimmed: '%s'\n\n", str_trim(str2));

    printf("String: '%s'\n", str3);
    printf("Converted to int: %d\n", str_to_int(str3));
}