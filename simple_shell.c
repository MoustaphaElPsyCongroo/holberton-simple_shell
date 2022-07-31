#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * main - Launch the Simple shell
 * @ac: Argument count (unused)
 * @av: Arg vector
 *
 * Return: 0 if success (including quitting)), exit with exit code if fail
 */
int main(__attribute__((unused)) int ac, char **av)
{
	char *command;
	char **argv;
	char *err;
	int stop = 0;
	char total_commands[] = {"0"};
	char is_terminal;
	int is_fullpath = 0;
	char *slash_command = NULL;
	char *path;
	char *path_cpy;
	char **path_arr;
	char *cur_word;
	int not_found;
	int i;


	while (!stop)
	{
		is_terminal = isatty(0);
		if (is_terminal)
			write(STDIN_FILENO, "$ ", 2);

		command = readcommand(total_commands);

		if (command == NULL)
			continue;

		if (command[0] != '/' && command[0] != '.')
		{
			is_fullpath = 0;
			slash_command = alloc_concat("/", command);
			free(command);
		}
		else
		{
			is_fullpath = 1;
			slash_command = alloc_concat("", command);
			free(command);
		}

		path = _getenv("PATH");
		if (path == NULL)
		{
			cur_word = strtok(slash_command, " ");
			argv = malloc(sizeof(char) * 1024);

			if (is_fullpath == 0)
			{
				argv[0] = NULL;
				argv[1] = cur_word;
				argv[2] = NULL;
			}
			else
			{
				not_found = access(cur_word, F_OK) && access(cur_word, X_OK);
				if (!not_found)
				{
					for (i = 0; cur_word; i++)
					{
						argv[i] = cur_word;
						cur_word = strtok(NULL, " ");
					}
					argv[i] = NULL;
					printf("argv0: %s", argv[0]);
					printf("argv1: %s", argv[1]);
				}
				else
				{
					argv[0] = NULL;
					argv[1] = cur_word;
					argv[2] = NULL;
				}
			}
		}
		else
		{
			path_cpy = alloc_concat("", path);
			path_arr = split(path_cpy, ":");

			argv = splitcommand(slash_command, path_arr);
		}

		if (argv[0] == NULL && argv[1])
		{
			err = err_notfound(argv[1], total_commands, av[0]);
			if (err == NULL)
				perror("malloc");
			else
				free(err);
			if (path)
				free_everything(4, argv, path_cpy, path_arr, slash_command);
			else
				free_everything(2, argv, slash_command);

			if (!is_terminal)
				exit(127);
			else
				continue;
		}
		else
		{
			stop = exec_command(argv, environ, av[0], is_terminal);
			if (is_fullpath == 0)
				free(argv[0]);
			if (path)
				free_everything(4, argv, path_cpy, path_arr, slash_command);
			else
				free_everything(2, argv, slash_command);
		}

	}

	if (stop > 0)
	{
		perror("Execve error");
		if (!is_terminal)
			exit(stop);
	}

	return (0);
}
