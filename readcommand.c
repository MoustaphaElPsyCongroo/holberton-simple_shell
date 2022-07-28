#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * readcommand - Reads a command entered by the user
 * Return: The command read, or NULL if fail
 */
char *readcommand(void)
{
	char *command = NULL;
	ssize_t rd = 0;
	size_t n = 0;
	int i = 0;

	rd = getline(&command, &n, stdin);

	if (rd == -1)
	{
		free(command);
		exit(0);
	}

	while (command[i] == ' ')
	{
		i++;

		if (command[i + 1] == 0)
		{
			free(command);
			return (NULL);
		}
	}

	if (command[0] == '\n')
	{
		free(command);
		return (NULL);
	}

	command[rd - 1] = 0;

	return (command);
}
