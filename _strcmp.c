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
	size_t i;
	int rtn_val = 0;
	size_t lofstr1, lofstr2;

	lofstr1 = lenOfStr(str1);
	lofstr2 = lenOfStr(str2);
	for (i = 0; i < lofstr1; i++)
	{
		if (i >= lofstr2)
		{
			rtn_val = 1;
			break;
		}
		if (str1[i] == str2[i])
			continue;
		else
		{
			rtn_val = 1;
			break;
		}
	}
	for (i = 0; i < lofstr2; i++)
	{
		if (i >= lofstr1)
		{
			rtn_val = 1;
			break;
		}
		if (str2[i] == str1[i])
			continue;
		else
		{
			rtn_val = 1;
			break;
		}
	}
	return (rtn_val);
}
