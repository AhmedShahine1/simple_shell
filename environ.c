#include "shell.h"

/**
 * populate_env_list - populates env linked list
 * @info_linked_list: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info_linked_list)
{
    list_t *node = NULL;

    for (size_t i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info_linked_list->env = node;
    return (0);
}


/**
 * _getenv - gets the value of an environ variable
 * @info_variable: Structure containing potential arguments. Used to maintain
 * @env_name: env var env_name
 *
 * Return: the value
 */
char *_getenv(info_t *info_variable, const char *env_name)
{
    char *pa;
    list_t *node = info_variable->env;

    while (node)
    {
        pa = starts_with(node->str, env_name);
        if (pa && *pa)
            return (pa);
        node = node->next;
    }
    return (NULL);
}


/**
 * _myunsetenv - Remove an environment variable
 * @info_variable: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info_variable)
{

    if (info_variable->argc == 1)
    {
        _eputs("Too few arguements.\n");
        return (1);
    }
    for (int i = 1; i <= info_variable->argc; i++)
        _unsetenv(info_variable, info_variable->argv[i]);

    return (0);
}



/**
 * _myenv - prints the current environment
 * @info_environment: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info_environment)
{
    print_list_str(info_environment->env);
    return (0);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info_variable: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info_variable)
{
    if (_setenv(info_variable, info_variable->argv[1], info_variable->argv[2]))
        return (0);

    if (info_variable->argc != 3)
    {
        _eputs("Incorrect number of arguements\n");
        return (1);
    }
    return (1);
}


