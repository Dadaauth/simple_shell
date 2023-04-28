#include <stdio.h>
#include "main.h"
/**
 * _isspace - checks if a strings contains only spaces
 * @str: the string
 * Return: 0 if it contains only spaces
 * 1 if it contians something else
 */
int _isspace(char *str)
{
	int i = 0;
	int rtn_val = 0;
	char *test = " ";
	char *test2 = "\n";

	while (str[i])
	{
		if (str[i] != test[0] && str[i] != test2[0])
		{
			rtn_val = 1;
			break;
		}
		i++;
	}
	return (rtn_val);
}
