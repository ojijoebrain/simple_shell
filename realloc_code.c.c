#include "shell.h"

/**
 * _memset - fills memory with a value
 * @mem: the pointer to the memory area
 * @b: value to fill
 * @n: number of bytes to be filled
 * Return: pointer to the memory
 */

char *_memset(char *mem, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		mem[i] = b;
	return (mem);
}

/**
 * free_str - frees a string of strings
 * @str: pointer to array of strings
 * Return: None
 */

void free_str(char **str)
{
	char **a = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(a);
}

/**
 * _realloc - reallocates memory
 * @ptr: pointer to memory
 * @old_size: size of previous memory
 * @new_size: byte size of new memory
 * Return: pointer to new memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

