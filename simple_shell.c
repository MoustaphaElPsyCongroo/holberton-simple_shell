#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Launch the Simple shell
 * @ac: Argument count (unused)
 * @av: Arg vector
 *
 * Return: 0 if success (including quitting)), -1 if fail
 */
int main(__attribute__((unused)) int ac, char **av)
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
			running = exec_command(argv, environ, av[0]);
			free(command);
			free(argv);
		}

	}

	return (0);
}
