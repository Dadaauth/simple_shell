#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
/**
 * _strtok - gets tokens from a string
 * @str: the string to work on
 * @delim: the string delimeter to look for
 * @length: the length of the token gotten
 * Return: A pointer to an array of tokens
 * (arguments given to the shell)
 */
char **_strtok(char *str, char *delim, UNUSED size_t *length)
{
	UNUSED size_t toklen;
	UNUSED char *strddup, *token;
	UNUSED char **tokarr;

	strddup = _strdup(str);
	toklen = getTokLen(strddup);
	free(strddup);
	tokarr = malloc((toklen + 1) * sizeof(char *));
	token = strtok(str, delim);
	while (token != NULL)
	{
		
	}
	return (tokarr);
}
