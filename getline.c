#include "shell.h"

/**
 * scan_input - buffers chained commands
 * @args_in: parameter struct
 * @buf: pointer to input buffer
 * @len: pointer to length of input buffer
 * Return: no. of chars read
 */

ssize_t scan_input(arg_t *args_in, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, int_sig);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(args_in, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			args_in->linecount_flag = 1;
			rm_comments(*buf);
			history_list(args_in, *buf, args_in->histcount++);
		}
	}
	return (r);
}

/**
 * get_input_cmd - handles command chains of user input
 * @args_in: input arguements
 *
 * Return: length of buffer
 */

ssize_t get_input_cmd(arg_t *args_in)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(args_in->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = scan_input(args_in, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		i = j + 1;

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_input - reads data from file descriptor into buffer
 * @args_in: input arguments
 * @buf: pointer to buffer
 * @i: pointer to position of buffer
 * Return: result r
 */

ssize_t read_input(arg_t *args_in, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(args_in->readfd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - handles memory allocation and reads input lines
 * @args_in: input arguement
 * @buffer: pointer the pointer to buffer
 * @length: pointer to size of buffer
 * Return: length of buffer
 */

int _getline(arg_t *args_in, char **buffer, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *buffer;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_input(args_in, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*buffer = p;
	return (s);
}

/**
 * int_sig - prints newline and flushes buffer
 * @sig_num: signal number to warnings
 * Return: None
 */

void int_sig(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}


