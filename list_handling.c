#include "shell.h"

/**
 * add_start_node - adds new node to the begining of linked list
 * @head: pointer to pointer of head node
 * @str: string value for new node
 * @num: integer value for new node
 * Return: pointer to new node
 */

slt_t *add_start_node(slt_t **head, const char *str, int num)
{
	slt_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(slt_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(slt_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_end_node - adds new node to the end of linked list
 * @head: pointer to the pointer of head node
 * @str: string value for new node
 * @num: integer value for new node
 * Return: pointer to new node
 */

slt_t *add_end_node(slt_t **head, const char *str, int num)
{
	slt_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(slt_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(slt_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_str_list - prints sting elements of each node in linked list
 * @h: pointer to head node
 *
 * Return: node count
 */

size_t print_str_list(const slt_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node - deletes node at specified index
 * @head: pointer to pointer of head node
 * @index: index to delete
 * Return: 1 or 0
 */

int delete_node(slt_t **head, unsigned int index)
{
	slt_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * clear_list - frees all the memory in a linked list
 * @head_ptr: pointer to pointer of head node
 * Return: None
 */

void clear_list(slt_t **head_ptr)
{
	slt_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}


