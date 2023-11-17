#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **argv)
{
	arg_t args_in[] = { ARG_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_error(argv[0]);
				puts_error(": 0: Can't open ");
				puts_error(argv[1]);
				putchar_error('\n');
				putchar_error(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		args_in->readfd = fd;
	}
	create_env_list(args_in);
	read_history_file(args_in);
	ssh(args_in, argv);
	return (EXIT_SUCCESS);
}


