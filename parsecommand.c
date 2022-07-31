#include "simple_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * parsecommand - Checks if a command has its full path
 * @command: The command to parse, either in name or full path
 *
 * Return: A pointer to the command's full path, or NULL if fail
 */
char *parsecommand(char *command)
{
	char *slash = "/";
	char *slash_command;

	if (command[0] != '/' && command[0] != '.')
	{
		slash_command = alloc_concat(slash, command);
	}
	else
	{
		slash_command = alloc_concat("", command);
	}

	if (slash_command == NULL)
		return (NULL);

	return (slash_command);
}

/**
 * checkfolderlist - Checks if a file exists in a list of paths
 * @path_arr: List of folders
 * @slash_file: File to search, prefixed by a /
 *
 * Return: The full path of the file if it exists, NULL otherwise
 */
char *checkfolderlist(char **path_arr, char *slash_file)
{
	int size = 1024;
	char *buf;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	if (access(slash_file, F_OK) == 0)
		return (slash_file);

	while (path_arr[i])
	{
		buf = malloc(sizeof(char) * size);
		if (buf == NULL)
			return (NULL);

		while (path_arr[i][j])
			buf[k++] = path_arr[i][j++];
		while (slash_file[l])
			buf[k++] = slash_file[l++];
		buf[k] = 0;

		if (access(buf, F_OK) != 0)
		{
			i++;
			j = 0;
			k = 0;
			l = 0;
			free(buf);
		}
		else
		{
			return (buf);
		}
	}
	return (NULL);
}

char **splitcommand(char *command, char **folderlist)
{
	int i = 0;
	int buf = 1024;
	char **spl;
	char *cur_word;
	char *cur_word_bkp;

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
		spl[1] = ++cur_word;
		spl[2] = NULL;
		return (spl);
	}

	while (cur_word)
	{
/*		if (i == 0)
		{
	//		cur_word_bkp = alloc_concat("", cur_word);

			cur_word = checkfolderlist(folderlist, cur_word);

			if (cur_word == NULL)
			{
				break;
	*			spl[0] = NULL;
				spl[1] = ++cur_word_bkp;
				spl[2] = NULL;
				return (spl);
			}
		}
*/
		spl[i] = cur_word;
		i++;
		cur_word = strtok(NULL, " ");
	}

/*	if (i == 0)
	{
		cur_word = strtok(command, " ");

		spl[0] = NULL;
		spl[1] = ++cur_word;
		spl[2] = NULL;
		return (spl);
	}
*/
	spl[i] = NULL;
	return (spl);
}

/**
 * checkpath - Checks if a command exists in the PATH
 * @command: The command to search, either in name or full path
 *
 * Return: Array to command's full path and args if it exists, NULL otherwise
 */
char **checkpath(char *command)
{
	char *slash_command;
	char **argv;
	char *path;
	char *path_cpy;
	char **path_arr;

	slash_command = parsecommand(command);

	if (slash_command == NULL)
		return (NULL);

	path = _getenv("PATH");
	if (path == NULL)
	{
		free(slash_command);
		return (NULL);
	}

	path_cpy = alloc_concat("", path);
	path_arr = split(path_cpy, ":");

	argv = splitcommand(slash_command, path_arr);
	free(path_arr);
	free(path_cpy);

	if (argv == NULL)
		return (NULL);

	return (argv);
}
