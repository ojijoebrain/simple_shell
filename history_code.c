#include "shell.h"

/**
 * create_history_path - creates path to history file
 * @args_in: input struct/arguement
 * Return: dynamically allocated string or Null
 */

char *create_history_path(arg_t *args_in)
{
	char *buf, *dir;

	dir = scan_env(args_in, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * create_history_file - creates history file from commands in linked list
 * @args_in: input arguement
 * Return: 1 or -1
 */

int create_history_file(arg_t *args_in)
{
	ssize_t fd;
	char *filename = create_history_path(args_in);
	slt_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = args_in->history; node; node = node->next)
	{
		write_str_fd(node->str, fd);
		write_fd('\n', fd);
	}
	write_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_file - reads history from file
 * @args_in: input arguement
 * Return: count of history entries
 */

int read_history_file(arg_t *args_in)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = create_history_path(args_in);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_list(args_in, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		history_list(args_in, buf + last, linecount++);
	free(buf);
	args_in->histcount = linecount;
	while (args_in->histcount-- >= HISTORY_MAX)
		delete_node(&(args_in->history), 0);
	update_histcount(args_in);
	return (args_in->histcount);
}

/**
 * history_list - adds commands to history linked list
 * @args_in: input sturct/args
 * @cmd: pointer to string of commands
 * @linecount: count of commands
 *
 * Return: 0
 */

int history_list(arg_t *args_in, char *cmd, int linecount)
{
	slt_t *node = NULL;

	if (args_in->history)
		node = args_in->history;
	add_end_node(&node, cmd, linecount);

	if (!args_in->history)
		args_in->history = node;
	return (0);
}

/**
 * update_histcount - updates the histcount of the linked list
 * @args_in: input sturct/args
 * Return: updated histcount in arg_t
 */

int update_histcount(arg_t *args_in)
{
	slt_t *node = args_in->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (args_in->histcount = i);
}

