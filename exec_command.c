#include "simple_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * exec_command - Executes a program
 * @path: Array containing the path to the program to execute and arguments
 * @env: Array of strings representing the current environement
 * @prog_name: Name of the shell
 *
 * Return: 0
 */
int exec_command(char **path, char **env, char *prog_name)
{
	pid_t child_pid;
	int status;
	char *pth = path[0];

	child_pid = fork();

	if (child_pid == -1)
		perror("Can't create new process");

	if (child_pid == 0)
	{
		if (pth[0] != '/' && pth[0] != '.')
			pth = checkpath(pth);

		if (pth == NULL)
		{
			execve(path[0], path, env);
			perror(prog_name);
			return (0);
		}

		if (execve(pth, path, env) == -1)
		{
			perror(prog_name);
			return (0);
		}
	}
	else
	{
		wait(&status);
	}

	return (1);
}
