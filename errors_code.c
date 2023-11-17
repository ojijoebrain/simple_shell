#include "shell.h"

/**
 * puts_error - prints string to stderr
 * @str: string error
 * Return: None
 */

void puts_error(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_error(str[i]);
		i++;
	}
}

/**
 * putchar_error - writes buffered characters to stderr
 * @c: buffered character
 * Return: 1 or -1 or error number
 */

int putchar_error(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_fd - writes buffered characters to specified file descriptors
 * @c: buffered character
 * @fd: specified file descriptor
 * Return: 1 or -1 or error number
 */

int write_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_str_fd - writes strings to specified file descriptors
 * @str: string to be writen
 * @fd: specified file descriptor
 * Return: no. of chars in str
 */
int write_str_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_fd(*str++, fd);
	}
	return (i);
}


