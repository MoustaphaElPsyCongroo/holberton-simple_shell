#include "simple_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * slashifycommand - Ensures a command is preceded  by a /
 * @command: The command to parse, either in name or full path
 * @is_fullpath: An int to indicate if the command is a full path
 *
 * Return: A pointer to the slashified command, or NULL if fail
 */
char *slashifycommand(char *command, int *is_fullpath)
{
	char *slash_command;

	if (command[0] != '/' && command[0] != '.')
	{
		slash_command = alloc_concat("/", command);
		*is_fullpath = 0;
	}
	else
	{
		slash_command = alloc_concat("", command);
		*is_fullpath = 1;
	}
	free(command);

	return (slash_command);
}


/**
 * splitcommand - Splits a command into it and its arguments
 * @command: The command to split
 * @folderlist: A list of folders to search the command in
 * @is_fullpath: An int indicating if the command is a full path or not
 *
 * Return:
 *	An array
 *		of the command + its arguments if found
 *		of the command itself surrounded by NULL -> <NULL> <cmd> <NULL>
 *	or NULL if fail
 */
char **splitcommand(char *command, char **folderlist, int is_fullpath)
{
	int i = 0;
	int buf = 1024;
	char **spl;
	char *cur_word;

	spl = malloc(sizeof(char) * buf);

	if (spl == NULL)
	{
		perror("Error: can't allocate memory");
		return (NULL);
	}

	cur_word = strtok(command, " ");

	cur_word = checkfolderlist(folderlist, cur_word);

	if (cur_word == NULL)
	{
		cur_word = strtok(command, " ");
		spl[0] = NULL;
		if (!is_fullpath)
			spl[1] = ++cur_word;
		else
			spl[1] = cur_word;
		spl[2] = NULL;
		return (spl);
	}

	while (cur_word)
	{
		spl[i] = cur_word;
		i++;
		cur_word = strtok(NULL, " ");
	}

	spl[i] = NULL;
	return (spl);
}

/**
 * split_nopath - Splits a command if there is no PATH env
 * @slash_command: A slash-preceded command, either in name or full path
 * @is_fullpath: Int indicating if slash_command is a full path
 *
 * Return: An array of the command + arguments, or NULL if fail
 */
char **split_nopath(char *slash_command, int is_fullpath)
{
	char *cur_word;
	char **argv;
	int not_found;
	int i;

	cur_word = strtok(slash_command, " ");
	argv = malloc(sizeof(char) * 1024);

	if (argv == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	if (is_fullpath == 0)
	{
		argv[0] = NULL;
		argv[1] = ++cur_word;
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
		}
		else
		{
			argv[0] = NULL;
			argv[1] = cur_word;
			argv[2] = NULL;
		}
	}
	return (argv);
}

/**
 * parsecommand - Checks if a command exists, splitting it if applicable
 * @slash_command: A command preceded by a / or a full path
 * @is_fullpath: An int indicating if the command is a full path
 *
 * Return: An array of the command + arguments
 */
char **parsecommand(char *slash_command, int is_fullpath)
{
	char *path;
	char *path_cpy;
	char **path_arr;
	char **argv;

	path = _getenv("PATH");

	if (path == NULL)
	{
		argv = split_nopath(slash_command, is_fullpath);

		if (argv == NULL)
			perror("split_nopath");
	}
	else
	{
		path_cpy = alloc_concat("", path);
		path_arr = split(path_cpy, ":");
		argv = splitcommand(slash_command, path_arr, is_fullpath);

		free_everything(2, path_cpy, path_arr);
	}

	return (argv);
}

void excommand(
		char **argv,
		char *slash_command,
		char **environ,
		char *prog_name,
		char *total_commands,
		int is_terminal,
		int is_fullpath,
		int *stop
		){

	char *err;

	if (argv[0] == NULL && argv[1])
	{
		err = err_notfound(argv[1], total_commands, prog_name);
		if (err == NULL)
			perror("malloc");
		else
			free(err);
		free_everything(2, argv, slash_command);
		if (!is_terminal)
			exit(127);
	}
	else
	{
		*stop = exec_command(argv, environ, prog_name, is_terminal);
		if (is_fullpath == 0)
			free(argv[0]);
		free_everything(2, argv, slash_command);
	}
}

