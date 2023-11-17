#include "shell.h"

/**
 * _active - determines if shell is active
 * @args_in: input argument
 *
 * Return: 0 or 1
 */

int _active(arg_t *args_in)
{
	return (isatty(STDIN_FILENO) && args_in->readfd <= 2);
}

/**
 * _delimeter - determines if char is a delimeter
 * @c: the char to be checked for delimeter
 * @delim: the delimeter string
 * Return: 0 or 1
 */

int _delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _alpha - determines if char is alphabetic
 * @c: input char
 * Return: 0 or 1
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts strings to an integer
 * @s: string to be converted
 * Return: 0 or converted number
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

