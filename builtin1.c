#include "shell.h"


/**
 * set_alias - sets alias to string
 * @info_struct: parameter struct
 * @str_alias: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */


int set_alias(info_t *info_struct, char *str_alias)
{
    char *p;

    p = _strchr(str_alias, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info_struct, str_alias));

    unset_alias(info_struct, str_alias);
    return (add_node_end(&(info_struct->alias), str_alias, 0) == NULL);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @prototype: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *prototype)
{
    char *paste = NULL;
    list_t *node = NULL;

    if (prototype->argc == 1)
    {
        node = prototype->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (int i = 1; prototype->argv[i]; i++)
    {
        paste = _strchr(prototype->argv[i], '=');
        if (!paste)
            print_alias(node_starts_with(prototype->alias, prototype->argv[i], '='));
        else
            set_alias(prototype, prototype->argv[i]);
    }

    return (0);
}


/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @prototype: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *prototype)
{
    print_list(prototype->history);
    return (0);
}



/**
 * print_alias - prints an alias string
 * @node_alias: the alias node_alias
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node_alias)
{
    char *paste = NULL, *alias = NULL;

    if (node_alias)
    {
        paste = _strchr(node_alias->str, '=');
        for (alias = node_alias->str; alias <= paste; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(paste + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * unset_alias - sets alias to string
 * @info_struct: parameter struct
 * @str_alias: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info_struct, char *str_alias)
{
    char *paste, chars;
    int ret;

    paste = _strchr(str_alias, '=');
    if (!paste){
        chars = *paste;
        *paste = 0;
        ret = delete_node_at_index(&(info_struct->alias),get_node_index(info_struct->alias, node_starts_with(info_struct->alias, str_alias, -1)));
        *paste = chars;
        return (ret);
    }
    return (1);
}

