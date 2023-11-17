#include "shell.h"

/**
 * list_len - counts the length of linked list
 * @h: pointer to head node
 * Return: count of nodes in linked list
 */

size_t list_len(const slt_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_of_strings - converts the string values of a linked list to an array
 * @head: pointer to head node
 * Return: an array of strings
 */

char **list_of_strings(slt_t *head)
{
	slt_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_slt - prints the contents of linked list
 * @h: pointer to head node
 * Return: size of list
 */

size_t print_slt(const slt_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(_itoa(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_prefix - returns node whose string starts with prefix
 * @head: pointer to head node
 * @prefix: prefix to match
 * @c: character after prefix
 * Return: pointer to prefix node
 */

slt_t *node_prefix(slt_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * seach_node_index - gets the index of a specified node
 * @head: pointer to head node
 * @node: pointer to specified node
 * Return: index of specified node or -1
 */

ssize_t seach_node_index(slt_t *head, slt_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}


