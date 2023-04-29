#include <stdbool.h>
/**
 * isSpace -  checks if a string contains only space
 * @str: the string to test
 * Return: true or false
 */
bool isSpace(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
			return (false);
	}
	return (true);
}
