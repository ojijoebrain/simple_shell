#include "shell.h"

/**
 * sh_env - handles environment command
 * @args_in: input arguements
 * Return: 0
 */

int sh_env(arg_t *args_in)
{
	print_str_list(args_in->env);
	return (0);
}

/**
 * scan_env - retrives environment variables
 * @args_in: input arguements
 * @name: environment variable
 * Return: pointer to environment variable
 */

char *scan_env(arg_t *args_in, const char *name)
{
	slt_t *node = args_in->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * sh_setenv - sets and modifies environment variables
 * @args_in: input arguments
 *  Return: 0
 */

int sh_setenv(arg_t *args_in)
{
	if (args_in->argc != 3)
	{
		puts_error("Incorrect number of arguements\n");
		return (1);
	}
	if (set_evn(args_in, args_in->argv[1], args_in->argv[2]))
		return (0);
	return (1);
}

/**
 * sh_rmenv - handles removal of environment variables
 * @args_in: input arguments
 * Return: 0
 */

int sh_rmenv(arg_t *args_in)
{
	int i;

	if (args_in->argc == 1)
	{
		puts_error("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= args_in->argc; i++)
		_rmenv(args_in, args_in->argv[i]);

	return (0);
}

/**
 * create_env_list - creates linked lists of environment variables
 * @args_in: input arguments
 * Return: 0
 */

int create_env_list(arg_t *args_in)
{
	slt_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_end_node(&node, environ[i], 0);
	args_in->env = node;
	return (0);
}



