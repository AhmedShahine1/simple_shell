#include "shell.h"

/**
 * sigintHandler - blocks ctrl-C
 * @signal_number: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_number)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}


/**
 * get_input - gets a line minus the newline
 * @info_struct: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info_struct)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buffer_p = &(info_struct->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info_struct, &buffer, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len)	/* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buffer position */
        p = buffer + i; /* get pointer for return */

        check_chain(info_struct, buffer, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (is_chain(info_struct, buffer, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info_struct->cmd_buf_type = CMD_NORM;
        }

        *buffer_p = p; /* pass back pointer to current command position */
        return (_strlen(p)); /* return length of current command */
    }

    *buffer_p = buffer; /* else not a chain, pass back buffer from _getline() */
    return (r); /* return length of buffer from _getline() */
}

/**
 * input_buf - buffers chained commands
 * @info_struct: parameter struct
 * @buffer: address of buffer
 * @lenght: address of lenght var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info_struct, char **buffer, size_t *lenght)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*lenght) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)info_struct->cmd_buf);*/
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        r = getline(buffer, &len_p, stdin);
#else
        r = _getline(info_struct, buffer, &len_p);
#endif
        if (r > 0)
        {
            if ((*buffer)[r - 1] == '\n')
            {
                (*buffer)[r - 1] = '\0'; /* remove trailing newline */
                r--;
            }
            info_struct->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info_struct, *buffer, info_struct->histcount++);
            /* if (_strchr(*buffer, ';')) is this a command chain? */
            {
                *lenght = r;
                info_struct->cmd_buf = buffer;
            }
        }
    }
    return (r);
}


/**
 * _getline - gets the next line of input from STDIN
 * @info_struct: parameter struct
 * @preallocated: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated preallocated buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info_struct, char **preallocated, size_t *leng)
{
    static char buffer[READ_BUF_SIZE];
    static size_t i, length;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *preallocated;
    if (i == length)
        i = length = 0;
    if (p && leng)
        s = *leng;

    r = read_buf(info_struct, buffer, &length);
    if (r == -1 || (r == 0 && length == 0))
        return (-1);

    c = _strchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : length;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buffer + i, k - i);
    else
        _strncpy(new_p, buffer + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (leng)
        *leng = s;
    *preallocated = p;
    return (s);
}


/**
 * read_buf - reads a buffer
 * @info_struct: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info_struct, char *buffer, size_t *size)
{
    ssize_t r = 0;

    if (*size)
        return (0);
    r = read(info_struct->readfd, buffer, READ_BUF_SIZE);
    if (r >= 0)
        *size = r;
    return (r);
}

