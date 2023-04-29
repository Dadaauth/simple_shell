#include <stdio.h>
/**
 * remove_newline - remove newline from the string entered by the user
 * @str: the string
 * @length: length of the string
 * Return: 0 if successful -1 if not
 */
int remove_newline(char *str, int length)
{
	if (length > 0 && str[length - 1] == '\n')
	{
		str[length - 1] = '\0';
		return (0);
	}
	return (-1);
}
