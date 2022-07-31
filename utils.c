#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * _strlen - Gets the length of a string
 * @s: The string to evaluate
 *
 * Return: s' length
 */
int _strlen(char *s)
{
	char *i;
	int count = 0;

	for (i = s; *i > 0; i++)
		count++;

	return (count);
}

/**
 * _getenv - Gets an environment variable
 * @name: The name of the variable to get
 *
 * Return: A pointer to the variable's value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	int j = 0;
	char *value = NULL;

	while (environ[j])
	{
		i = 0;

		while (name[i])
		{
			if (environ[j][i] != name[i])
				break;

			i++;
		}

		if (environ[j][i] == '=' && name[i] == 0)
		{
			value = &(environ[j][i + 1]);
			break;
		}

		j++;
	}

	return (value);
}

/**
 * alloc_concat - Concatenates two strings, allocating memory for them
 * @str1: First string to concatenate
 * @str2: Second string to concatenate
 *
 * Return: A pointer to the new string, or NULL if fail
 */
char *alloc_concat(char *str1, char *str2)
{
	int len1;
	int len2;
	char *dest;
	int i = 0;
	int j = 0;

	len1 = _strlen(str1);
	len2 = _strlen(str2);

	dest = malloc(len1 + len2 + 1);
	if (dest == NULL)
		return (NULL);

	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}

	while (str2[j])
	{
		dest[i] = str2[j];
		i++;
		j++;
	}

	dest[i] = 0;

	return (dest);
}

/**
 * free_everything - Frees anything
 * @n: The number of variable parameters
 */
void free_everything(int n, ...)
{
	int i = n;
	va_list tofree;

	va_start(tofree, n);

	if (n == 0)
		return;

	while (i--)
		free(va_arg(tofree, char *));

	va_end(tofree);
}
