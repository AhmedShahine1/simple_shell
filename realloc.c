#include "shell.h"

/**
 * ffree - frees a string of strings
 * @string_string: string of strings
 */
void ffree(char **string_string)
{
    char **a = string_string;

    if (!string_string)
        return;
    while (*string_string)
        free(*string_string++);
    free(a);
}



/**
 **_memset - fills memory with a constant byte
 *@memoryarea: the pointer to the memory area
 *@byte: the byte to fill *memoryarea with
 *@amount: the amount of bytes to be filled
 *Return: (memoryarea) a pointer to the memory area memoryarea
 */
char *_memset(char *memoryarea, char byte, unsigned int amount)
{
    unsigned int i;

    for (i = 0; i < amount; i++)
        memoryarea[i] = byte;
    return (memoryarea);
}


/**
 * _realloc - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @old: byte size of previous block
 * @new: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pointer, unsigned int old, unsigned int new)
{
    char *p;

    if (!new)
        return (free(pointer), NULL);
    if (!pointer)
        return (malloc(new));

    if (new == old)
        return (pointer);

    p = malloc(new);
    if (!p)
        return (NULL);

    old = old < new ? old : new;
    while (old--)
        p[old] = ((char *)pointer)[old];
    free(pointer);
    return (p);
}
