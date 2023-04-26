#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
/**
 * _strcmp - compares two strings if they are identical
 * @str1: first string
 * @str2: second string
 * Return: 0 if they are identical
 * 1 if they are not identical
 */
int _strcmp(char *str1, char *str2)
{
	int i;
	int rtn_val = 0;

	for (i = 0; str1[i]; i++)
	{
		if (str1[i] == str2[i])
			continue;
		else
			rtn_val = 1;
	}
	for (i = 0; str2[i]; i++)
	{
		if (str2[i] == str1[i])
			continue;
		else
			rtn_val = 1;
	}
	return (rtn_val);
}
