#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * trim - Trims a string's trailing whitespaces
 * @str: The string to trim
 *
 * Return: A trimmed string, or NULL if fail or no string
 */
char *trim(char *str)
{
	char *front = str;
	char *end = NULL;
	int len = 0;

	if (str == NULL)
		return (NULL);
	if (str[0] == '\0')
		return (str);

	len = _strlen(str);
	end = str + len;

	while (*front == ' ')
		front++;

	if (end != front)
	{
		while (*end == ' ' && end != front)
			end--;
	}

	if (front != str && end == front)
		*str = '\0';
	else if (str + len - 1 != end)
		*(end + 1) = '\0';

	end = str;
	if (front != str)
	{
		while (*front)
			*end++ = *front++;
		*end = '\0';
	}

	return (str);
}

/**
 * readcommand - Reads a command entered by the user
 * Return: The command read, or NULL if fail
 */
char *readcommand(void)
{
	char *command = NULL;
	ssize_t rd = 0;
	size_t n = 0;

	rd = getline(&command, &n, stdin);

	if (rd == -1)
	{
		free(command);
		exit(0);
	}
	command[rd - 1] = 0;
	command = trim(command);

	if (command[0] == '\n' || !command[0])
	{
		free(command);
		return (NULL);
	}

	return (command);
}
