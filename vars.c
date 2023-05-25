#include "shell.h"

/**
 * replace_string - replaces string
 * @old_string: address of old_string string
 * @new_string: new_string string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_string, char *new_string)
{
    free(*old_string);
    *old_string = new_string;
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info_struct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info_struct)
{
    list_t *node;

    for (int i = 0; info_struct->argv[i]; i++)
    {
        if (info_struct->argv[i][0] != '$' || !info_struct->argv[i][1])
            continue;
        if (!_strcmp(info_struct->argv[i], "$$"))
        {
            replace_string(&(info_struct->argv[i]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        if (!_strcmp(info_struct->argv[i], "$?"))
        {
            replace_string(&(info_struct->argv[i]),
                           _strdup(convert_number(info_struct->status, 10, 0)));
            continue;
        }
        node = node_starts_with(info_struct->env, &info_struct->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info_struct->argv[i]),
                           _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info_struct->argv[i], _strdup(""));

    }
    return (0);
}


/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info_struct: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info_struct, char *buffer, size_t *position)
{
    size_t j = *position;

    if (buffer[j] == '&' && buffer[j + 1] == '&')
    {
        buffer[j] = 0;
        j++;
        info_struct->cmd_buf_type = CMD_AND;
    }
    else if (buffer[j] == '|' && buffer[j + 1] == '|')
    {
        buffer[j] = 0;
        j++;
        info_struct->cmd_buf_type = CMD_OR;
    }
    else if (buffer[j] == ';') /* found end of this command */
    {
        buffer[j] = 0; /* replace semicolon with null */
        info_struct->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *position = j;
    return (1);
}


/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info_struct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info_struct)
{
    list_t *node;
    char *pa;

    for (int i = 0; i < 10; i++)
    {
        node = node_starts_with(info_struct->alias, info_struct->argv[0], '=');
        if (!node)
            return (0);
        free(info_struct->argv[0]);
        pa = _strdup(pa + 1);
        if (!pa)
            return (0);
        pa = _strchr(node->str, '=');
        if (!pa)
            return (0);
        info_struct->argv[0] = pa;
    }
    return (1);
}


/**
 * check_chain - checks we should continue chaining based on last status
 * @info_struct: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 * @starting: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info_struct, char *buffer, size_t *position, size_t starting, size_t length)
{
    size_t j = *position;

    if (info_struct->cmd_buf_type == CMD_OR)
    {
        if (!info_struct->status)
        {
            buffer[starting] = 0;
            j = length;
        }
    }

    if (info_struct->cmd_buf_type == CMD_AND)
    {
        if (info_struct->status)
        {
            buffer[starting] = 0;
            j = length;
        }
    }


    *position = j;
}

