#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include "main.h"
#include <stdlib.h>
/**
 * _exitshell - dkdj
 * @str: string
 * Return: an arr of the exit command else NULL
 */
char **_exitshell(char *str)
{
	char **arr;
	size_t toklen, i;
	char *strddup;

	if (str == NULL)
		return (NULL);

	strddup = _strdup(str);
	arr = _strtok(strddup, " ", &toklen);
	free(strddup);
	if (_strcmp(arr[0], "exit") == 0)
	{
		return (arr);
	}
	for (i = 0; i < toklen; i++)
		free(arr[i]);
	free(arr);
	return (NULL);
}
