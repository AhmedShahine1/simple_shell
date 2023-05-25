#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @destination_buffer: the destination buffer
 * @source_buffer: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination_buffer, char *source_buffer)
{
    char *ret = destination_buffer;

    while (*destination_buffer)
        destination_buffer++;
    while (*source_buffer)
        *destination_buffer++ = *source_buffer++;
    *destination_buffer = *source_buffer;
    return (ret);
}


/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *string)
{
    int i = 0;

    if (!string)
        return (0);

    while (*string++)
        i++;
    return (i);
}


/**
 * starts_with - checks if substring starts with search
 * @search: string to search
 * @substring: the substring to find
 *
 * Return: address of next char of search or NULL
 */
char *starts_with(const char *search, const char *substring)
{
    while (*substring)
        if (*substring++ != *search++)
            return (NULL);
    return ((char *)search);
}


/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @first_strang: the first strang
 * @second_strang: the second strang
 *
 * Return: negative if first_strang < second_strang, positive if first_strang > second_strang, zero if first_strang == second_strang
 */
int _strcmp(char *first_strang, char *second_strang)
{
    while (*first_strang && *second_strang)
    {
        if (*first_strang != *second_strang)
            return (*first_strang - *second_strang);
        first_strang++;
        second_strang++;
    }
    if (*first_strang != *second_strang)
        return (*first_strang < *second_strang ? -1 : 1);
    else
        return (0);
}

