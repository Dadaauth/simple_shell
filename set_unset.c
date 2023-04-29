#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "main.h"
int shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: Invalid arguments\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		fprintf(stderr, "setenv: Failed to set environment variable: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}

int shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Invalid arguments\n");
		return (1);
	}

	if (unsetenv(args[1]) == -1)
	{
		fprintf(stderr, "unsetenv: Failed to unset environment variable: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
