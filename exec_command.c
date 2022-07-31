#include "simple_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * exec_command - Executes a program
 * @path: Array containing the path to the program to execute and arguments
 * @env: Array of strings representing the current environement
 * @prog_name: Name of the shell
 *
 *
 * Return: 0
 */
int exec_command(char **path, char **env, char *prog_name, int is_terminal)
{
	pid_t child_pid;
	int status;
	int res = 0;

	child_pid = fork();

	if (child_pid == -1)
		perror("fork");

	if (child_pid == 0)
	{
		if (execve(path[0], path, env) == -1)
		{
			perror(prog_name);
			return (1);
		}
	}
	else
	{
		wait(&status);

	}
	if (WIFEXITED(status) && !is_terminal)
		res = WEXITSTATUS(status);

	return (res);

}
