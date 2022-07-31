#include "simple_shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * split - Splits a string into an array of each word
 * @str: The string to split
 * @delim: The delimiter that defines a word
 *
 * Return: A pointer to the resulting array, or NULL if fail
 */
char **split(char *str, char *delim)
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

	cur_word = strtok(str, delim);

	while (cur_word)
	{
		spl[i] = cur_word;
		i++;
		cur_word = strtok(NULL, delim);
	}
	spl[i] = NULL;

	return (spl);
}
