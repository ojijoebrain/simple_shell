#include "shell.h"

/**
 * free_ptr - frees a specified pointer
 * @ptr: pointer to a pointer to be freed
 * Return: 1 if freed, otherwise 0.
 */

int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

