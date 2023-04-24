#include <stdio.h>
#include "main.h"
/**
 * lenOfStr - gets the length of a string
 * @str: the string to work on
 * Return: the length of the string
 */
int lenOfStr(char *str)
{
	int i;
	int len = 0;

	for (i = 0; str[i]; i++)
		len++;
	return (len);
}
