#include "shell.h"


/**
 * get_node_index - gets the index of a node_pointer
 * @head_list: pointer to list head_list
 * @node_pointer: pointer to the node_pointer
 *
 * Return: index of node_pointer or -1
 */
ssize_t get_node_index(list_t *head_list, list_t *node_pointer)
{
    size_t i = 0;

    while (head_list)
    {
        if (head_list == node_pointer)
            return (i);
        head_list = head_list->next;
        i++;
    }
    return (-1);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @first_node: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *first_node)
{
    list_t *node = first_node;
    size_t i = list_len(first_node), j;
    char **strs;
    char *str;

    if (!first_node || !i)
        return (NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @first_node: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *first_node)
{
    size_t i = 0;

    while (first_node)
    {
        _puts(convert_number(first_node->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(first_node->str ? first_node->str : "(nil)");
        _puts("\n");
        first_node = first_node->next;
        i++;
    }
    return (i);
}


/**
 * list_len - determines length of linked list
 * @first_node: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *first_node)
{
    size_t i = 0;

    while (first_node)
    {
        first_node = first_node->next;
        i++;
    }
    return (i);
}

/**
 * node_starts_with - returns list_head whose string starts with match
 * @list_head: pointer to list head
 * @match: string to match
 * @character: the next character after match to match
 *
 * Return: match list_head or null
 */
list_t *node_starts_with(list_t *list_head, char *match, char character)
{
    char *p = NULL;

    while (list_head)
    {
        p = starts_with(list_head->str, match);
        if (p && ((character == -1) || (*p == character)))
            return (list_head);
        list_head = list_head->next;
    }
    return (NULL);
}




