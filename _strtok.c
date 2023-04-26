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
char **_strtok(char *str, char *delim, size_t *length)
{
	size_t toklen, strlen;
	char *strddup, *token;
	char **tokarr;
	int i = 0, j;

	strddup = _strdup(str);
	toklen = getTokLen(strddup, delim);
	*length = toklen;
	free(strddup);
	tokarr = malloc((toklen + 1) * sizeof(char *));
	token = strtok(str, delim);
	i = 0;
	while (token != NULL)
	{
		strlen = lenOfStr(token);
		tokarr[i] = malloc((strlen + 1) * sizeof(char));
		for (j = 0; token[j]; j++)
		{
			tokarr[i][j] = token[j];
		}
		tokarr[i][j] = '\0';
		token = strtok(NULL, delim);
		i++;
	}
	tokarr[i] = NULL;
	return (tokarr);
}
