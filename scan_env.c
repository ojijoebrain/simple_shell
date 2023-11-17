#include "shell.h"

/**
 * scan_env_arr - retrives an array of environment variables
 * @args_in: input arguement
 * Return: pointer to array of environment variables
 */

char **scan_env_arr(arg_t *args_in)
{
	if (!args_in->environ || args_in->env_changed)
	{
		args_in->environ = list_of_strings(args_in->env);
		args_in->env_changed = 0;
	}

	return (args_in->environ);
}

/**
 * _rmenv - remove environment variables from the linked list
 * @args_in: input arguement
 * @var: environment variable
 *  Return: args_in
 */

int _rmenv(arg_t *args_in, char *var)
{
	slt_t *node = args_in->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			args_in->env_changed = delete_node(&(args_in->env), i);
			i = 0;
			node = args_in->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (args_in->env_changed);
}

/**
 * set_evn - sets and updates environment variables in a linked list
 * @args_in: input arguement
 * @var: pointer to environment variable
 * @value: pointer to value of environment variable
 *  Return: 0
 */

int set_evn(arg_t *args_in, char *var, char *value)
{
	char *buf = NULL;
	slt_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = args_in->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			args_in->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_end_node(&(args_in->env), buf, 0);
	free(buf);
	args_in->env_changed = 1;
	return (0);
}

