#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/**
 * _exitshell - checks if an exit command is given to the cli
 * @str: the line str
 * Return: 0 if it is exit, 1 if otherwise
 */
int _exitshell(char *str)
{
	int i = 0, j = 0;
	char *str2 = malloc(5 * sizeof(char)), *strddup;
	int rtn_val = 1;

	strddup = _strdup(str);
	while (strddup[i])
	{
		if (strddup[i] == ' ')
			continue;
		else
		{
			if (strddup[i] == 'e')
			{
				while (strddup[i])
				{
					str2[j] = strddup[i];
					i++;
					j++;
				}
				break ;
			}
			else
			{
				break;
			}
		}
		i++;
	}
	if (_strcmp(str2, "exit") == 0)
		rtn_val = 0;
	free(str2);
	free(strddup);
	printf("%d what are\n", rtn_val);
	return (rtn_val);
}
