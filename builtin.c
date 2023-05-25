#include "shell.h"

/**
 * _mycd - changes the current directory of the process
 * @prototype: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *prototype)
{
    char *string, *directory, buff[1024];
    int chdir_ret;

    string = getcwd(buff, 1024);
    if (!string)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (_strcmp(prototype->argv[1], "-") == 0)
    {
        if (!_getenv(prototype, "OLDPWD="))
        {
            _puts(string);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(prototype, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
                chdir((directory = _getenv(prototype, "OLDPWD=")) ? directory : "/");
    }
    else if (!prototype->argv[1])
    {
        directory = _getenv(prototype, "HOME=");
        if (directory)
            chdir_ret = chdir(directory);
        else
            chdir_ret = /* TODO: what should this be? */chdir((directory = _getenv(prototype, "PWD=")) ? directory : "/");
    }
    else
        chdir_ret = chdir(prototype->argv[1]);
    if (chdir_ret != -1)
    {
        _setenv(prototype, "OLDPWD", _getenv(prototype, "PWD="));
        _setenv(prototype, "PWD", getcwd(buff, 1024));
    }
    else
    {
        print_error(prototype, "can't cd to ");
        _eputs(prototype->argv[1]), _eputchar('\n');
    }
    return (0);
}


/**
 * _myhelp - changes the current directory of the process
 * @prototype: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *prototype)
{
    char **array;

    array = prototype->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*array); /* temp att_unused workaround */
    return (0);
}


/**
 * _myexit - exits the shell
 * @prototype: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if prototype.argv[0] != "exit"
 */
int _myexit(info_t *prototype)
{
    int exit;

    if (prototype->argv[1])  /* If there is an exit arguement */
    {
        exit = _erratoi(prototype->argv[1]);
        if (exit != -1)
        {
            prototype->err_num = _erratoi(prototype->argv[1]);
            return (-2);
        }
        prototype->status = 2;
        print_error(prototype, "Illegal number: ");
        _eputs(prototype->argv[1]);
        _eputchar('\n');
        return (1);

    }
    prototype->err_num = -1;
    return (-2);
}
