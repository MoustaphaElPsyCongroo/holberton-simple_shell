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

	if (command[i] == ' ')
	{
		while (command[i])
		{
			if (command[i + 1] == 0)
				return (NULL);

			i++;
		}
	}

	if (command[0] == '\n' && command[1] == 0)
		return (NULL);

	if (rd == -1)
	{
		free(command);
		exit(0);
	}

	command[rd - 1] = 0;

	return (command);
}
