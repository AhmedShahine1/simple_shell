#include "shell.h"


/**
 * _putchar - writes the character character_print to stdout
 * @character_print: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char character_print)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (character_print == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buffer, i);
        i = 0;
    }
    if (character_print != BUF_FLUSH)
        buffer[i++] = character_print;
    return (1);
}


/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *src)
{
    int i = 0;

    if (destination == src || src == 0)
        return (destination);
    while (src[i])
    {
        destination[i] = src[i];
        i++;
    }
    destination[i] = 0;
    return (destination);
}


/**
 *_puts - prints an input string
 *@string_printed: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string_printed)
{
    int i = 0;

    if (!string_printed)
        return;
    while (string_printed[i] != '\0')
    {
        _putchar(string_printed[i]);
        i++;
    }
}

/**
 * _strdup - duplicates a string
 * @string_duplicate: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string_duplicate)
{
    int length = 0;
    char *ret;

    if (string_duplicate == NULL)
        return (NULL);
    while (*string_duplicate++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--string_duplicate;
    return (ret);
}

