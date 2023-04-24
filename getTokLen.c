#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
/**
 * getTokLen - gets how many tokens are in a string
 * @str: the string to work on
 * Return: The length of the token
 */
size_t getTokLen(char *str)
{
	size_t len = 0;
	char *token;

	token = strtok(str, " ");
	while (token != NULL)
	{
		len++;
		token = strtok(NULL, " ");
	}
	return (len);
}
