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

	while (!stop)
	{
		is_terminal = isatty(0);
		if (is_terminal)
			write(STDIN_FILENO, "$ ", 2);

		command = readcommand(total_commands);

		if (command == NULL)
			continue;

/*		argv = split(command, " ");*/
		argv = checkpath(command);
/*		printf("%s", slash_command);
		free(slash_command);
		continue;

		slash_command = alloc_concat("/", command);

		printf("transfo commande: %s\n", slash_command);
		free(command);

		ppath = _getenv("PATH");
		if (ppath == NULL)
			return (0);

		pathcpy = alloc_concat("", ppath);
		ppath_arr = split(pathcpy, ":");

		while (ppath_arr[i])
		{
			buf = malloc(1024);

			while (ppath_arr[i][j])
				buf[k++] = ppath_arr[i][j++];

			while (slash_command[l])
			{
				buf[k++] = slash_command[l++];
			}
			buf[k] = 0;

			if (stat(buf, &st) != 0)
			{
			i++;
			j = 0;
			k = 0;
			l = 0;
			free(buf);
			}
			else
			{
				printf("found");
				command = buf;
				free(buf);
				break;
			}
		}

		write(STDERR_FILENO, av[0], _strlen(av[0]));
		free(ppath_arr);
		free(pathcpy);
		free(slash_command);
		i = 0;
		j = 0;
		k = 0;
		l = 0;


		continue;
*/

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
/*			free(command); */

			if (!is_terminal)
				exit(127);
			else
				continue;
		}
		else
		{
			stop = exec_command(argv, environ, av[0], is_terminal);
			free(argv[0]);
			free(argv);
/*			free(command); */
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
