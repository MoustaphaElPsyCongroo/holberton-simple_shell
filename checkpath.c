#include "simple_shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

/**
 * checkpath - Searches for files in the PATH
 * @filename: The name of the file to search
 *
 * Return: A pointer to the alloc'd full path of the file, or NULL if fail
 */
char *checkpath(char *filename)
{
	char *path = _getenv("PATH");
	char *cur_folder = NULL;
	char *folder_sep = "/";
	char *slash_filename;
	char *filepath;
	struct stat st;

	slash_filename = alloc_concat(folder_sep, filename);
	if (slash_filename == NULL)
		return (NULL);

	cur_folder = strtok(path, ":");

	while (cur_folder)
	{
		filepath = alloc_concat(cur_folder, slash_filename);
		if (filepath == NULL)
			return (NULL);

		if (stat(filepath, &st) != 0)
		{
			free(filepath);
			cur_folder = strtok(NULL, ":");
		}
		else
		{
			free(slash_filename);
			return (filepath);
		}
	}

	free(slash_filename);
	return (NULL);
}
