#include "shell.h"

/**
 * sh_exit - handles exit commands
 * @args_in: input arguements
 * Return: -2 on success and 1 for error
 */

int sh_exit(arg_t *args_in)
{
	int exitcheck;

	if (args_in->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = atoi_err(args_in->argv[1]);
		if (exitcheck == -1)
		{
			args_in->status = 2;
			print_err(args_in, "Illegal number: ");
			puts_error(args_in->argv[1]);
			putchar_error('\n');
			return (1);
		}
		args_in->err_num = atoi_err(args_in->argv[1]);
		return (-2);
	}
	args_in->err_num = -1;
	return (-2);
}

/**
 * sh_help - handles help command
 * @args_in: input arguements
 * Return: 0
 */

int sh_help(arg_t *args_in)
{
	char **arg_array;

	arg_array = args_in->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

