#include "shell.h"

/**
 * free_info - frees info_t struct fields
 * @info_struct: struct address
 * @all_fields: true if freeing all_fields fields
 */
void free_info(info_t *info_struct, int all_fields)
{
    ffree(info_struct->argv);
    info_struct->argv = NULL;
    info_struct->path = NULL;
    if (all_fields)
    {
        if (info_struct->env)
            free_list(&(info_struct->env));
        if (!info_struct->cmd_buf)
            free(info_struct->arg);
        if (info_struct->history)
            free_list(&(info_struct->history));
        if (info_struct->alias)
            free_list(&(info_struct->alias));
        ffree(info_struct->environ);
        info_struct->environ = NULL;
        bfree((void **)info_struct->cmd_buf);
        if (info_struct->readfd > 2)
            close(info_struct->readfd);
        _putchar(BUF_FLUSH);
    }
}


/**
 * clear_info - initializes info_t struct
 * @info_struct: struct address
 */
void clear_info(info_t *info_struct)
{
    info_struct->arg = NULL;
    info_struct->argv = NULL;
    info_struct->path = NULL;
    info_struct->argc = 0;
}



/**
 * set_info - initializes info_t struct
 * @info_struct: struct address
 * @argument_vector: argument vector
 */
void set_info(info_t *info_struct, char **argument_vector)
{
    int i = 0;

    info_struct->fname = argument_vector[0];
    if (info_struct->arg)
    {
        info_struct->argv = strtow(info_struct->arg, " \t");
        if (!info_struct->argv)
        {

            info_struct->argv = malloc(sizeof(char *) * 2);
            if (info_struct->argv)
            {
                info_struct->argv[0] = _strdup(info_struct->arg);
                info_struct->argv[1] = NULL;
            }
        }
        for (i = 0; info_struct->argv && info_struct->argv[i]; i++)
            ;
        info_struct->argc = i;

        replace_alias(info_struct);
        replace_vars(info_struct);
    }
}


