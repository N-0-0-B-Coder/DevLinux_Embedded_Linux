#ifndef STRUTILS_H
#define STRUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Reverses a string in-place.
 * 
 * @param string [in] Pointer to the string to be reversed.
 * 
 * @return char* Pointer to the reversed string.
 */
char* str_reverse(char* string);

/**
 * @brief Remove leading and trailing whitespaces from a string.
 * 
 * @param string [in] Pointer to the string to be trimmed.
 * 
 * @return char* Pointer to the trimmed string.
 */
char* str_trim(char* string);

/**
 * @brief Converts a string to an integer.
 * 
 * @param string [in] Pointer to the string to be converted.
 * 
 * @return int The converted integer value.
 */
int str_to_int(char* string);

#ifdef __cplusplus
}
#endif

#endif /* STRUTILS_H */
