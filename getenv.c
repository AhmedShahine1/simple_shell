#include "shell.h"



/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @prototype: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @env_var: the string env env_var property
 * @env_value: the string env env_var env_value
 *  Return: Always 0
 */
int _setenv(info_t *prototype, char *env_var, char *env_value)
{
    char *buffer = NULL;
    list_t *node;
    char *p;

    if (!env_var || !env_value)
        return (0);

    buffer = malloc(_strlen(env_var) + _strlen(env_value) + 2);
    if (!buffer)
        return (1);
    _strcpy(buffer, env_var);
    _strcat(buffer, "=");
    _strcat(buffer, env_value);
    node = prototype->env;
    while (node)
    {
        p = starts_with(node->str, env_var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buffer;
            prototype->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(prototype->env), buffer, 0);
    free(buffer);
    prototype->env_changed = 1;
    return (0);
}


/**
 * get_environ - returns the string array copy of our environ
 * @prototype: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *prototype)
{
    if (!prototype->environ || prototype->env_changed)
    {
        prototype->environ = list_to_strings(prototype->env);
        prototype->env_changed = 0;
    }

    return (prototype->environ);
}



/**
 * _unsetenv - Remove an environment variable
 * @prototype: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @env_var: the string env env_var property
 */
int _unsetenv(info_t *prototype, char *env_var)
{
    list_t *node = prototype->env;
    size_t i = 0;
    char *p;

    if (!node || !env_var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, env_var);
        if (p && *p == '=')
        {
            prototype->env_changed = delete_node_at_index(&(prototype->env), i);
            i = 0;
            node = prototype->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (prototype->env_changed);
}
