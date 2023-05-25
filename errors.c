#include <mspcoll.h>
#include "shell.h"



/**
 * _putfd - writes the character character_print to given filedescriptor
 * @character_print: The character to print
 * @filedescriptor: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char character_print, int filedescriptor)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (character_print == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(filedescriptor, buffer, i);
        i = 0;
    }
    if (character_print != BUF_FLUSH)
        buffer[i++] = character_print;
    return (1);
}

/**
 * _eputchar - writes the character character_print to stderr
 * @character_print: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char character_print)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (character_print == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buffer, i);
        i = 0;
    }
    if (character_print != BUF_FLUSH)
        buffer[i++] = character_print;
    return (1);
}


/**
 *_putsfd - prints an input string
 * @str_printed: the string to be printed
 * @filedescriptor: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str_printed, int filedescriptor)
{
    int i = 0;

    if (str_printed == NULL)
        return (0);
    while (*str_printed)
    {
        i += _putfd(*str_printed++, filedescriptor);
    }
    return (i);
}

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

