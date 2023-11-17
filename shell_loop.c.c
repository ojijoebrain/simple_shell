#include "shell.h"

/**
 * ssh - prompts and processes input
 * @args_in: input arguement
 * @argv: the argument vector
 * Return: 0 or 1
 */

int ssh(arg_t *args_in, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_args_in(args_in);
		if (_active(args_in))
			_puts("$ ");
		putchar_error(BUFFER_FLUSH);
		r = get_input_cmd(args_in);
		if (r != -1)
		{
			set_args_in(args_in, argv);
			builtin_ret = is_builtin(args_in);
			if (builtin_ret == -1)
				is_cmd(args_in);
		}
		else if (_active(args_in))
			_putchar('\n');
		free_args_in(args_in, 0);
	}
	create_history_file(args_in);
	free_args_in(args_in, 1);
	if (!_active(args_in) && args_in->status)
		exit(args_in->status);
	if (builtin_ret == -2)
	{
		if (args_in->err_num == -1)
			exit(args_in->status);
		exit(args_in->err_num);
	}
	return (builtin_ret);
}

/**
 * is_builtin - checks for and executes builtin commands
 * @args_in: input argument
 * Return: result or -1
 */
int is_builtin(arg_t *args_in)
{
	int i, built_in_ret = -1;
	builtin_args builtintbl[] = {
		{"exit", sh_exit},
		{"env", sh_env},
		{"help", sh_help},
		{"history", sh_history},
		{"setenv", sh_setenv},
		{"unsetenv", sh_rmenv},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(args_in->argv[0], builtintbl[i].type) == 0)
		{
			args_in->line_count++;
			built_in_ret = builtintbl[i].func(args_in);
			break;
		}
	return (built_in_ret);
}

/**
 * is_cmd - check if a path is an executable command
 * @args_in: input argument
 * Return: None
 */

void is_cmd(arg_t *args_in)
{
	char *path = NULL;
	int i, k;

	args_in->path = args_in->argv[0];
	if (args_in->linecount_flag == 1)
	{
		args_in->line_count++;
		args_in->linecount_flag = 0;
	}
	for (i = 0, k = 0; args_in->arg[i]; i++)
		if (!_delimeter(args_in->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_cmd_path(args_in, scan_env(args_in, "PATH="), args_in->argv[0]);
	if (path)
	{
		args_in->path = path;
		fork_new(args_in);
	}
	else
	{
		if ((_active(args_in) || scan_env(args_in, "PATH=")
					|| args_in->argv[0][0] == '/') && is_exe(args_in, args_in->argv[0]))
			fork_new(args_in);
		else if (*(args_in->arg) != '\n')
		{
			args_in->status = 127;
			print_err(args_in, "not found\n");
		}
	}
}

/**
 * fork_new - forks to a new process
 * @args_in: input arguement
 * Return: None
 */

void fork_new(arg_t *args_in)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(args_in->path, args_in->argv, scan_env_arr(args_in)) == -1)
		{
			free_args_in(args_in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(args_in->status));
		if (WIFEXITED(args_in->status))
		{
			args_in->status = WEXITSTATUS(args_in->status);
			if (args_in->status == 126)
				print_err(args_in, "Permission denied\n");
		}
	}
}
