#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * main - Launch the Simple shell, calling each general function
 * @ac: Argument count (unused)
 * @av: Arg vector
 *
 * Return: 0 if success (including quitting)), exit with exit code if fail
 */
int main(__attribute__((unused)) int ac, char **av)
{
	char *command;
	char **argv;
	int stop = 0;
	char total_commands[] = {"0"};
	char is_terminal;
	int is_fullpath = 0;
	char *slash_command = NULL;

	while (!stop)
	{
		is_terminal = isatty(0);
		if (is_terminal)
			write(STDIN_FILENO, "$ ", 2);

		command = readcommand(total_commands);
		if (command == NULL)
			continue;
		slash_command = slashifycommand(command, &is_fullpath);
		argv = parsecommand(slash_command, is_fullpath);

		if (argv == NULL)
			break;
		excommand(
				argv,
				slash_command,
				environ, av[0],
				total_commands,
				is_terminal,
				is_fullpath, &stop
			 );

	}

	if (stop > 0)
	{
		perror("Execve error");
		if (!is_terminal)
			exit(stop);
	}
	return (0);
}
