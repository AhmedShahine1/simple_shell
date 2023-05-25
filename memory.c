#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @pointer_free: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **pointer_free)
{
    if (pointer_free && *pointer_free)
    {
        free(*pointer_free);
        *pointer_free = NULL;
        return (1);
    }
    return (0);
}
