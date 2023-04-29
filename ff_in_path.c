#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "main.h"
/**
 * free_last - frees memory at the end of the ff_in_path function
 * @strtow: a pointer to free
 * @duppath: a pointer to free
 * Return: nothing.
 */
void free_last(char **strtow, char *duppath)
{
	unsigned int j;

	for (j = 0; strtow[j] != NULL; j++)
		free(strtow[j]);
	free(strtow);
	free(duppath);
}
/**
 * ff_in_path - looks for the entered command by the user in the path
 * @str: the command enetered by the user
 *
 * Return: Always 0.
 */
char *ff_in_path(char *str)
{
	char *path = getenv("PATH"), *duppath, *directory = NULL, **strtow;
	size_t toklen, i = 0, j = 0;
	int strlen, strlen2, statStatus;
	struct stat st;

	if (!path && stat(str, &st) == 0)
		return (str);
	duppath = _strdup(path);
	strtow = _strtok(duppath, ":", &toklen);
	strlen2 = lenOfStr(str);
	while (strtow[i] != NULL)
	{
		strlen = lenOfStr(strtow[i]);
		directory = malloc((strlen + strlen2 + 2) * sizeof(char));
		if (directory != NULL)
		{
			_strcpy(directory, strtow[i]);
			strcat(directory, "/");
			strcat(directory, str);
			i++;
			statStatus = stat(directory, &st);
			if (statStatus == 0)
			{
				free(str);
				break;
			}
			free(directory);
			directory = NULL;
		}
	}
	for (j = 0; strtow[j] != NULL; j++)
		free(strtow[j]);
	free(strtow);
	free(duppath);
	if (statStatus != 0)
	{
		if (stat(str, &st) == 0)
			return (str);
		else
			return (NULL);
	}
	return (directory);
}
