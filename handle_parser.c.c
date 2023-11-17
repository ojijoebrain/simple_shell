#include "shell.h"

/**
 * is_exe - checks if file is an executable
 * @args_in: input arguement
 * @path: file path
 * Return: 1 or 0
 */

int is_exe(arg_t *args_in, char *path)
{
	struct stat st;

	(void)args_in;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters between start and stop index
 * @path: the PATH string
 * @start: start index
 * @stop: stop index
 *
 * Return: pointer to new buffer
 */

char *dup_chars(char *path, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path[i] != ':')
			buf[k++] = path[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_cmd_path - finds this cmd in the PATH string
 * @args_in: input arguement
 * @pathstr: string of directories
 * @cmd: command to find full path
 * Return: pointer to full path or NULL
 */

char *find_cmd_path(arg_t *args_in, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exe(args_in, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_exe(args_in, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

