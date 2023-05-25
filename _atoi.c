#include "shell.h"


/**
 * is_delim - checks if character is a delimeter
 * @chars: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char chars, char *delimeter)
{
	while (*delimeter){
        char x= *delimeter++;
		if ( x == chars)
			return (1);
    }
	return (0);
}


/**
 *_atoi - converts a string to an integer
 *@string: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *string)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; string[i] != '\0' && flag != 2; i++)
	{
        if (string[i] >= '0' && string[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (string[i] - '0');
        }
        else if (flag == 1)
            flag = 2;

		if (string[i] == '-')
			sign *= -1;
	}

	if (sign != -1)
		output = result;
	else
		output = -result;

	return (output);
}

/**
 * interactive - returns true if shell is interactive mode
 * @address: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *address)
{
    return (isatty(STDIN_FILENO) && address->readfd <= 2);
}


/**
 *_isalpha - checks for alphabetic character
 *@character: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
        return (1);
    else
        return (0);
}

