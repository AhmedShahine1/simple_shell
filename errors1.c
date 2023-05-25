#include "shell.h"

/**
 * convert_number - converter function, a clone of itoa
 * @number: number
 * @base: base
 * @argument_flags: argument argument_flags
 *
 * Return: string
 */
char *convert_number(long int number, int base, int argument_flags)
{
    static char *array;
    static char buf[50];
    char sign = 0;
    char *ptr;
    unsigned long n = number;

    if (!(argument_flags & CONVERT_UNSIGNED) && number < 0)
    {
        n = -number;
        sign = '-';

    }
    array = argument_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buf[49];
    *ptr = '\0';

    do	{
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}



/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @in: the in
 * @filedescriptor: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int in, int filedescriptor)
{
    int (*__putchar)(char) = _putchar;
    int count = 0;
    unsigned int _abs_, current;

    if (filedescriptor == STDERR_FILENO)
        __putchar = _eputchar;
    if (in >= 0)
        _abs_ = in;
    else
    {
        _abs_ = -in;
        __putchar('-');
        count++;
    }

    current = _abs_;
    for (int i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * print_error - prints an error message
 * @info_struct: the parameter & return info_struct struct
 * @error_type: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info_struct, char *error_type)
{
    _eputs(info_struct->fname);
    _eputs(": ");
    print_d(info_struct->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info_struct->argv[0]);
    _eputs(": ");
    _eputs(error_type);
}


/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
        {
            buffer[i] = '\0';
            break;
        }
}

/**
 * _erratoi - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *string)
{
    unsigned long int result = 0;

    if (*string == '+')string++;  /* TODO: why does this make main return 255? */
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            result *= 10;
            result += (string[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

