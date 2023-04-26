#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <stdarg.h>
#include "main.h"
/**
 * print_prompt - prints a prompt and recieves line input
 * @line: a string containing the characters entered on the line
 * @llen: amount of characters
 * Return: 1 to break the loop,
 * 2 to continue the loop,
 * 0 to do nothing
 */
int print_prompt(char *line, int llen)
{
	if (llen > 0 && line[llen - 1] == '\n')
		line[llen - 1] = '\0';
	if (llen == -1 || _strcmp(line, "exit") == 0)
		return (1);
	else if (_strcmp(line, "") == 0)
		return (2);
	return (0);
}
/**
 * free_in_child - frees all memory that needs to be freed in the child process
 * @line: a pointer to free
 * @argd: a pointer to free
 * @strddup: a pointer to free
 * @check: checks if the function is called to free line or not.
 * The check is added so the function can be reuseable
 * Return: Nothing
 */
void free_in_child(char *line, char **argd, char *strddup, int check)
{
	int i;

	if (check == 0)
		free(line);
	for (i = 0; argd[i] != NULL; i++)
		free(argd[i]);
	free(argd);
	free(strddup);
}
/**
 * shell - first simple version of super simple shell
 * @av: argument vector of the main function passed to
 * the shell fucntion
 * Return: Always 0.
 */
int shell(char **av)
{
	char *line = NULL, *strddup, *directory = NULL;
	size_t len = 0, toklen;
	int llen, exec_rtn, stop = 1, id, status, UNUSED i, UNUSED rtn_pp;
	char **argd;

	while (stop == 1)
	{
		llen = getline(&line, &len, stdin);
		rtn_pp = print_prompt(line, llen);
		if (rtn_pp == 1)
			exit(EXIT_SUCCESS);
		else if (rtn_pp == 2)
			continue;
		strddup = _strdup(line);
		argd = _strtok(strddup, " ", &toklen);
		directory = ff_in_path(argd[0]);
		if (directory == NULL)
		{
			printf("%s: No such file or directory\n", av[0]);
			free_in_child(line, argd, strddup, 1);
			continue;
		}
		argd[0] = directory;
		id = fork();
		if (id == 0)
		{
			printf("About to execute");
			exec_rtn = execve(argd[0], argd, environ);
			if (exec_rtn == -1)
				printf("%s: No such file or directory\n", av[0]);
			free_in_child(line, argd, strddup, 0);
			free(directory);
			exit(EXIT_SUCCESS);
		}
		else
			wait(&status);
	}
	free(directory);
	free(line);
	return (0);
}
