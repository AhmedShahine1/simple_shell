#include "shell.h"

/**
 * dup_chars - duplicates characters
 * @path_string: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_string, int start_index, int stop_index)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start_index; i < stop_index; i++)
        if (path_string[i] != ':')
            buffer[k++] = path_string[i];
    buffer[k] = 0;
    return (buffer);
}


/**
 * is_cmd - determines if a file is an executable command
 * @info_struct: the info_struct struct
 * @path_file: path_file to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info_struct, char *path_file)
{
    struct stat st;

    (void)info_struct;
    if (!path_file || stat(path_file, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}


/**
 * find_path - finds this cmd in the PATH string
 * @info_struct: the info_struct struct
 * @path_string: the path_string string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info_struct, char *path_string, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!path_string)
        return (NULL);
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info_struct, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!path_string[i] || path_string[i] == ':')
        {
            path = dup_chars(path_string, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info_struct, path))
                return (path);
            if (!path_string[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}
