#include "shell.h"

/**
 * clear_args_in - clears all fields in arg_t struct
 * @args_in: input arguement
 * Return: None
 */

void clear_args_in(arg_t *args_in)
{
	args_in->arg = NULL;
	args_in->argv = NULL;
	args_in->path = NULL;
	args_in->argc = 0;
}

/**
 * set_args_in - sets all fields in arg_t struct
 * @args_in: input sturct/arguement
 * @argv: argument vector
 * Return: None
 */

void set_args_in(arg_t *args_in, char **argv)
{
	int i = 0;

	args_in->fname = argv[0];
	if (args_in->arg)
	{
		args_in->argv = split_str(args_in->arg, " \t");
		if (!args_in->argv)
		{
			args_in->argv = malloc(sizeof(char *) * 2);
			if (args_in->argv)
			{
				args_in->argv[0] = _strdup(args_in->arg);
				args_in->argv[1] = NULL;
			}
		}
		for (i = 0; args_in->argv && args_in->argv[i]; i++)
			;
		args_in->argc = i;
	}
}

/**
 * free_args_in - frees fields in arg_t struct
 * @args_in: input struct/arguement
 * @all: flags for resource to be freed
 * Return: None
 */

void free_args_in(arg_t *args_in, int all)
{
	free_str(args_in->argv);
	args_in->argv = NULL;
	args_in->path = NULL;
	if (all)
	{
		if (args_in->env)
			clear_list(&(args_in->env));
		if (args_in->history)
			clear_list(&(args_in->history));
		free_str(args_in->environ);
			args_in->environ = NULL;
			close(args_in->readfd);
		_putchar(BUFFER_FLUSH);
	}
}

