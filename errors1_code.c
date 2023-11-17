#include "shell.h"

/**
 * atoi_err - converts a strings to int with error checking
 * @s: pointer to string
 * Return: int or -1
 */
int atoi_err(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - constructs and prints error to stderr
 * @args_in: input arguments
 * @estr: specified error string
 * Return: None
 */

void print_err(arg_t *args_in, char *estr)
{
	puts_error(args_in->fname);
	puts_error(": ");
	print_int(args_in->line_count, STDERR_FILENO);
	puts_error(": ");
	puts_error(args_in->argv[0]);
	puts_error(": ");
	puts_error(estr);
}

/**
 * print_int - prints a ints to stdout and stderr
 * @input: input int
 * @fd: specified file descriptor
 * Return: count of chars
 */

int print_int(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = putchar_error;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _itoa - converts ints to str
 * @num: int
 * @base: specified base
 * @flags: convertion flags
 * Return: pointer to converted str
 */

char *_itoa(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & IS_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & IS_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - removes comments from files
 * @str: pointer to string
 * Return: None
 */

void rm_comments(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '#' && (!i || str[i - 1] == ' '))
		{
			str[i] = '\0';
			break;
		}
}


