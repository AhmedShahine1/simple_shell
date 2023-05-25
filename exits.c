#include "shell.h"


/**
 **_strncat - concatenates two strings
 *@first_string: the first string
 *@second_string: the second string
 *@amount: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *first_string, char *second_string, int amount)
{
    int i = 0, j = 0;
    char *s = first_string;

    while (first_string[i] != '\0')
        i++;
    while (second_string[j] != '\0' && j < amount)
    {
        first_string[i] = second_string[j];
        i++;
        j++;
    }
    if (j < amount)
        first_string[i] = '\0';
    return (s);
}

/**
 **_strchr - locates a character in a string
 *@string_parsed: the string to be parsed
 *@character: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *string_parsed, char character)
{
    do {
        if (*string_parsed == character)
            return (string_parsed);
    } while (*string_parsed++ != '\0');

    return (NULL);
}

/**
 **_strncpy - copies a string
 *@destination_string: the destination string to be copied to
 *@source_string: the source string
 *@amount: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *destination_string, char *source_string, int amount)
{
    int i = 0, j;
    char *s = destination_string;

    while (source_string[i] != '\0' && i < amount - 1)
    {
        destination_string[i] = source_string[i];
        i++;
    }
    if (i < amount)
    {
        j = i;
        while (j < amount)
        {
            destination_string[j] = '\0';
            j++;
        }
    }
    return (s);
}

