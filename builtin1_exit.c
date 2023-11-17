#include "shell.h"

/**
 * sh_history - handles history command
 * @args_in: input arguements
 *  Return: 0
 */

int sh_history(arg_t *args_in)
{
	print_slt(args_in->history);
	return (0);
}


