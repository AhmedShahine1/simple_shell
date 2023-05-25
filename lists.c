#include "shell.h"


/**
 * free_list - frees all nodes of a list
 * @head_pointer: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_pointer)
{
    list_t *node, *next_node, *head;

    if (!head_pointer || !*head_pointer)
        return;
    head = *head_pointer;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *head_pointer = NULL;
}


/**
 * add_node_end - adds a node to the end of the list
 * @head_node: address of pointer to head_node node
 * @str_field: str_field field of node
 * @num_node: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head_node, const char *str_field, int num_node)
{
    list_t *new_node, *node;

    if (!head_node)
        return (NULL);

    node = *head_node;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num_node = num_node;
    if (str_field)
    {
        new_node->str_field = _strdup(str_field);
        if (!new_node->str_field)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head_node = new_node;
    return (new_node);
}


/**
 * add_node - adds a node to the start of the list
 * @head_node: address of pointer to head_node node
 * @str_node: str_node field of node
 * @num_index: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head_node, const char *str_node, int num_index)
{
    list_t *new_head;

    if (!head_node)
        return (NULL);
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);
    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num_index = num_index;
    if (str_node)
    {
        new_head->str_node = _strdup(str_node);
        if (!new_head->str_node)
        {
            free(new_head);
            return (NULL);
        }
    }
    new_head->next = *head_node;
    *head_node = new_head;
    return (new_head);
}


/**
 * delete_node_at_index - deletes node at given index_node
 * @head_pointer: address of pointer to first node
 * @index_node: index_node of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head_pointer, unsigned int index_node)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head_pointer || !*head_pointer)
        return (0);

    if (!index_node)
    {
        node = *head_pointer;
        *head_pointer = (*head_pointer)->next;
        free(node->str);
        free(node);
        return (1);
    }
    node = *head_pointer;
    while (node)
    {
        if (i == index_node)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return (0);
}


/**
 * print_list_str - prints only the str element of a list_t linked list
 * @firstnode: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *firstnode)
{
    size_t i = 0;

    while (firstnode)
    {
        _puts(firstnode->str ? firstnode->str : "(nil)");
        _puts("\n");
        firstnode = firstnode->next;
        i++;
    }
    return (i);
}

