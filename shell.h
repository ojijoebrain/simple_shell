#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for _itoa */
#define IS_LOWERCASE	1
#define IS_UNSIGNED	2

/* using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;


/**
 * struct listslt - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct listslt
{
	int num;
	char *str;
	struct listslt *next;
} slt_t;

/**
 * struct pseudoarg - holds pseudo-arguments to pass into functions.
 * @arg: A string generated from getline, encompassing the command arguments.
 * @argv:An array of strings derived from command arguments.
 * @path: The current command's file path.
 * @argc: The count of arguments in the command.
 * @line_count: The count of errors encountered during execution.
 * @err_num: The exit code used in the event of termination.
 * @linecount_flag: Flag indicating whether to count this line of input.
 * @fname: The filename of the program being executed.
 * @env: A linked list representing the local copy of the environment.
 * @environ: Custom-modified copy of the environment from the linked list env.
 * @history: Node representing the command history.
 * @env_changed: Flag indicating whether the environment was modified.
 * @status: The return status of the most recent executed command.
 * @readfd: The file descriptor used to read input lines.
 * @histcount: The count of lines in the command history.
 */
typedef struct pseudoarg
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	slt_t *env;
	slt_t *history;
	char **environ;
	int env_changed;
	int status;
	int readfd;
	int histcount;
} arg_t;

#define ARG_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, \
		0, 0}

/**
 * struct builtincmd - holds builtin command
 * @type:pointer to a character array.
 *
 * @func: function pointer
 */
typedef struct builtincmd
{
	char *type;
	int (*func)(arg_t *);
} builtin_args;


/* shell_loop.c */
int ssh(arg_t *, char **);
int is_builtin(arg_t *);
void is_cmd(arg_t *);
void fork_new(arg_t *);

/* handle_parser.c */
int is_exe(arg_t *, char *);
char *dup_chars(char *, int, int);
char *find_cmd_path(arg_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors_code.c */
void puts_error(char *);
int putchar_error(char);
int write_fd(char c, int fd);
int write_str_fd(char *str, int fd);

/* handle_str.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* handle_str1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* str_tokenizer.c */
char **split_str(char *, char *);

/* realloc_code.c */
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* mem.c */
int free_ptr(void **);

/* strtol.c */
int _active(arg_t *);
int _delimeter(char, char *);
int _alpha(int);
int _atoi(char *);

/* errors_code1.c */
int atoi_err(char *);
void print_err(arg_t *, char *);
int print_int(int, int);
char *_itoa(long int, int, int);
void rm_comments(char *);

/* builtin_exit.c */
int sh_exit(arg_t *);
int sh_help(arg_t *);
int sh_history(arg_t *);

/* getline.c */
ssize_t get_input_cmd(arg_t *);
int _getline(arg_t *, char **, size_t *);
void int_sig(int);

/* get_args.c */
void clear_args_in(arg_t *);
void set_args_in(arg_t *, char **);
void free_args_in(arg_t *, int);

/* env_builtin.c */
char *scan_env(arg_t *, const char *);
int sh_env(arg_t *);
int sh_setenv(arg_t *);
int sh_rmenv(arg_t *);
int create_env_list(arg_t *);

/* scan_env.c */
char **scan_env_arr(arg_t *);
int _rmenv(arg_t *, char *);
int set_evn(arg_t *, char *, char *);

/* history_code.c */
char *create_history_path(arg_t *args_in);
int create_history_file(arg_t *args_in);
int read_history_file(arg_t *args_in);
int history_list(arg_t *args_in, char *buf, int linecount);
int update_histcount(arg_t *args_in);

/* lists_handling.c */
slt_t *add_start_node(slt_t **, const char *, int);
slt_t *add_end_node(slt_t **, const char *, int);
size_t print_str_list(const slt_t *);
int delete_node(slt_t **, unsigned int);
void clear_list(slt_t **);

/* lists_handling1..c */
size_t list_len(const slt_t *);
char **list_of_strings(slt_t *);
size_t print_slt(const slt_t *);
slt_t *node_prefix(slt_t *, char *, char);
ssize_t seach_node_index(slt_t *, slt_t *);

#endif

