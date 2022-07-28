#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Launch the Simple shell
 *
 * Return: 0 if success (including quitting)), -1 if fail
 */
int main(void)
{
	char *command;
	char **argv;
	int running = 1;

	while (running)
	{
		if (isatty(0))
			printf("$ ");

		command = readcommand();

		if (command == NULL)
			continue;

		argv = split(command);

		if (argv == NULL)
		{
			free(command);
			free(argv);
		}
		else
		{
			running = exec_command(argv, environ);
			free(command);
			free(argv);
		}

	}

	return (0);
}
