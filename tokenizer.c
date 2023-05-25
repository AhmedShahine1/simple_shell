#include "shell.h"

/**
 * **strtow2 - splits a string into words
 * @string: the input string
 * @delimeter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char delimeter)
{
    int i, j, k, m, numwords = 0;
    char **s;

    if (string == NULL || string[0] == 0)
        return (NULL);
    for (i = 0; string[i] != '\0'; i++)
        if ((string[i] != delimeter && string[i + 1] == delimeter) ||
            (string[i] != delimeter && !string[i + 1]) || string[i + 1] == delimeter)
            numwords++;
    if (numwords == 0)
        return (NULL);
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (string[i] == delimeter && string[i] != delimeter)
            i++;
        k = 0;
        while (string[i + k] != delimeter && string[i + k] && string[i + k] != delimeter)
            k++;
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            s[j][m] = string[i++];
        s[j][m] = 0;
    }
    s[j] = NULL;
    return (s);
}


/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @input_string: the input string
 * @delimeter_string: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *input_string, char *delimeter_string)
{
    int i, j, k, m, numwords = 0;
    char **String;

    if (input_string == NULL || input_string[0] == 0)
        return (NULL);
    if (!delimeter_string)
        delimeter_string = " ";
    for (i = 0; input_string[i] != '\0'; i++)
        if (!is_delim(input_string[i], delimeter_string) && (is_delim(input_string[i + 1], delimeter_string) || !input_string[i + 1]))
            numwords++;

    if (numwords == 0)
        return (NULL);
    String = malloc((1 + numwords) * sizeof(char *));
    if (!String)
        return (NULL);
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (is_delim(input_string[i], delimeter_string))
            i++;
        k = 0;
        while (!is_delim(input_string[i + k], delimeter_string) && input_string[i + k])
            k++;
        String[j] = malloc((k + 1) * sizeof(char));
        if (!String[j])
        {
            for (k = 0; k < j; k++)
                free(String[k]);
            free(String);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            String[j][m] = input_string[i++];
        String[j][m] = 0;
    }
    String[j] = NULL;
    return (String);
}


