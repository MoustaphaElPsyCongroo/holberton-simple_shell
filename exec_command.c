#include "simple_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * exec_command - Executes a program
 * @path: Array containing the path to the program to execute and arguments
 * @env: Array of strings representing the current environement
 *
 * Return: 0
 */
int exec_command(char **path, char **env)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
		perror("Can't create new process");

	if (child_pid == 0)
	{
		if (execve(path[0], path, env) == -1)
		{
			perror("./shell");
			return (0);
		}
	}
	else
	{
		wait(&status);
	}

	return (1);
}
