#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: A pointer to the duplicated string
 */
char *_strdup(char *str)
{
	char *temp;
	int lofstr, i;

	lofstr = lenOfStr(str);
	temp = malloc((lofstr + 1) * sizeof(char));
	for (i = 0; str[i]; i++)
		temp[i] = str[i];
	temp[i] = '\0';
	return (temp);
}
