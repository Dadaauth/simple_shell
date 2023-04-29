#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/**
 * _strcpy - copies a string to another string in memory
 * @dest: the destination string
 * @src: the source string
 * Return: A pointer to dest(the copied string)
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
