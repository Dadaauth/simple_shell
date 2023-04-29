#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
/**
 * _cd_dir - performs operations such as where to change the directory to. Also
 * updates the PWD & OLDPWD env using the setenv function
 * @str: the string gotten from line
 * Return: A char pointer to where to change the directory to
 * or NULL if the command given is not cd
 */
void _cd_dir(char *str[])
{
	char *home_dir;
	char cwd[MAX_BUFFER_SIZE];

	printf("/root");
	if (str[1] == NULL)
	{
		home_dir = getenv("HOME");
		chdir(home_dir);
	}
	else if (_strcmp(str[1], "-") == 0)
		chdir(getenv("OLDPWD"));
	else
	{
		if (chdir(str[1]) != 0)
			printf("cd: %s: No such file or directory\n", str[1]);
	}
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
}
