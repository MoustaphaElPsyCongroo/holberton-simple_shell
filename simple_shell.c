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
	char *cur_cmd;
	char **argv;
	char *err;
	char *err_temp1;
	char *err_temp2;
	char *err_temp3;
	char *err_temp4;
	char *err_temp5;
	int stop = 0;
	char total_commands[] = {"0"};
	char is_terminal;
	int is_fullpath = 0;
	char *slash_command = NULL;
	char *path;
	char *path_cpy;
	char **path_arr;


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
			free(slash_command);
			perror("get path");
		}

		path_cpy = alloc_concat("", path);
		path_arr = split(path_cpy, ":");

		argv = splitcommand(slash_command, path_arr);

		if (argv[0] == NULL && argv[1])
		{
			cur_cmd = argv[1];
			err_temp1 = alloc_concat("", av[0]);
			err_temp2 = alloc_concat(err_temp1, ": ");
			free(err_temp1);
			err_temp3 = alloc_concat(err_temp2, total_commands);
			free(err_temp2);
			err_temp4 = alloc_concat(err_temp3, ": ");
			free(err_temp3);
			err_temp5 = alloc_concat(err_temp4, cur_cmd);
			free(err_temp4);
			err = alloc_concat(err_temp5, ": not found\n");
			free(err_temp5);
			write(STDERR_FILENO, err, _strlen(err));
			free(err);
			free(argv);
			free(path_cpy);
			free(path_arr);
			free(slash_command);


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
			free(argv);
			free(path_cpy);
			free(path_arr);
			free(slash_command);
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
