#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/**
 * _strcat - concatenates two strings together
 * @dest: the destination string
 * @src: the source string
 * Return: Always 0.
 */
char *_strcat(char *dest, char *src)
{
	int i, j, lofstr;

	lofstr = lenOfStr(dest);
	j = lofstr;

	for (i = 0; src[i] ; i++)
	{
		dest[j] = src[i];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

