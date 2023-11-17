#include "shell.h"

/**
 * _strlen - counts length of a string
 * @str: pointer to the string
 * Return: string length
 */

int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - compares two strings.
 * @str1: string1 to be compared
 * @str2: string2 to be compared
 * Return: the difference between the 2 strings
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks for prefix in a string
 * @str: string
 * @prefix: prefix to find
 * Return: pointer prefix in str
 */

char *starts_with(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strcat - concatenates strings
 * @dest: pointer to destination string
 * @src: pointer to source string
 * Return: pointer to resulting string
 */

char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
