#include "simple_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * builtin_exit - Exits with the specified status
 * @status: Exit status, defaults to 0
 */
void builtin_exit(int status)
{
	exit(status);
}

/**
 * builtin_printenv - Prints the current environment
 */
void builtin_printenv(void)
{
	int i = 0;

	while (environ[i])
		printf("%s\n", environ[i++]);
}

/**
 * check_builtins - Checks if a command is built in, launching it if applicable
 * @command: The command to check
 *
 * Return: 0 if a builtin was found, 1 if fail
 */
int check_builtins(char *command)
{
	int status = 0;
	char *cur_word;
	char *cmd_cpy;

	cmd_cpy = _strdup(command);
	if (cmd_cpy == NULL)
	{
		perror("_strdup");
		return (1);
	}

	cur_word = strtok(cmd_cpy, " ");

	if (_strcmp(cur_word, "exit") == 0)
	{
		free_everything(2, cmd_cpy, command);
		builtin_exit(status);
		return (0);
	}

	if (_strcmp(cur_word, "env") == 0)
	{
		free_everything(2, cmd_cpy, command);
		builtin_printenv();
		return (0);
	}

	free(cmd_cpy);
	return (1);
}
