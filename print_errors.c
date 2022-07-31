#include "simple_shell.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * err_notfound - Writes to stderr when a command is not found
 * @command: The invalid command
 * @total_commands: Number of commands input so far
 * @prog_name: The name of the current program
 *
 * Return: A pointer to the error message, NULL otherwise
 */
char *err_notfound(char *command, char *total_commands, char *prog_name)
{
	char *cur_cmd = command;
	char *err_temp1, *err_temp2, *err_temp3, *err_temp4, *err_temp5, *err;

	err_temp1 = alloc_concat("", prog_name);
	if (err_temp1 == NULL)
		return (NULL);

	err_temp2 = alloc_concat(err_temp1, ": ");
	if (err_temp2 == NULL)
		return (free(err_temp1), NULL);
	free(err_temp1);

	err_temp3 = alloc_concat(err_temp2, total_commands);
	if (err_temp3 == NULL)
		return (free(err_temp2), NULL);
	free(err_temp2);

	err_temp4 = alloc_concat(err_temp3, ": ");
	if (err_temp4 == NULL)
		return (free(err_temp3), NULL);
	free(err_temp3);

	err_temp5 = alloc_concat(err_temp4, cur_cmd);
	if (err_temp5 == NULL)
		return (free(err_temp4), NULL);
	free(err_temp4);

	err = alloc_concat(err_temp5, ": not found\n");
	if (err == NULL)
		return (free(err_temp5), NULL);
	free(err_temp5);

	write(STDERR_FILENO, err, _strlen(err));
	return (err);
}
