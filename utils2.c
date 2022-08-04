#include "simple_shell.h"
#include <stdlib.h>
#include <limits.h>

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: The numerical difference between the two strings:
 *	a negative value if s1 < s2
 *	0 if s1 == s2
 *	a positive value if s1 > s2
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;

	return (s1[i] - s2[i]);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: A pointer to a new string, duplicate of str
 */
char *_strdup(char *str)
{
	int i = 0;
	int j = 0;
	int length = 0;
	char *s;

	if (str == NULL)
		return (NULL);

	while (str[i++])
		length++;

	s = malloc(sizeof(char) * (length + 1));

	if (s == NULL)
		return (NULL);

	while (j < length)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = 0;

	return (s);
}
