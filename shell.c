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
	{
		line[llen - 1] = '\0';
	}
	if (llen == -1 || _strcmp(line, "exit") == 0)
	{
		return (1);
	}
	else if (_strcmp(line, "") == 0)
		return (2);
	else if (_strcmp(line, "env") == 0)
		return (3);
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
void free_in_child(char *line, char **argd, int check)
{
	int i;

	if (check == 0)
		free(line);
	for (i = 0; argd[i] != NULL; i++)
		free(argd[i]);
	free(argd);
}
/**
 * sigint_handler - handles the control C signal and
 * disallows it from stopping the shell
 * @signum: the signal recieved
 */
void sigint_handler(UNUSED int signum)
{
	printf("\n");
	printf("$ ");
	fflush(stdout);
}
/**
 * print_environ - prints the enviromental variables
 * 
 * Return: Nothing
 */
void print_environ()
{
	extern char **environ;
	char **envp = environ;

	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
/**
 * shell - first simple version of super simple shell
 * @av: argument vector of the main function passed to
 * the shell fucntion
 * Return: Always 0.
 */
int shell(char **av)
{
	char *line = NULL, *strddup = NULL, *directory = NULL;
	size_t len = 0, toklen;
	int llen, UNUSED exec_rtn, run = 1, id, status, UNUSED i, UNUSED rtn_pp;
	int interactive = isatty(STDIN_FILENO);
	char **argd = NULL;
	static int count = 1;

	signal(SIGINT, sigint_handler);
	while (run)
	{
		len = 0;
		if (interactive)
			printf("$ ");
		llen = getline(&line, &len, stdin);
		rtn_pp = print_prompt(line, llen);
		if (rtn_pp == 1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (rtn_pp == 2)
			continue;
		else if (rtn_pp == 3)
			print_environ();
		strddup = _strdup(line);
		argd = _strtok(strddup, " ", &toklen);
		directory = ff_in_path(argd[0]);
		free(strddup);
		if (directory == NULL)
		{
			/**
			printf("%s: %d: %s: not found\n", av[0], count, line);
			*/
			perror(av[0]);
			count++;
			for (i = 0; argd[i] != NULL; i++)
				free(argd[i]);
			free(argd);
			continue;
		}
		else
			free(line);
		argd[0] = directory;
		id = fork();
		if (id == 0)
		{
			printf("About to execute");
			execve(argd[0], argd, environ);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&status);
			for (i = 0; argd[i] != NULL; i++)
				free(argd[i]);
			free(argd);
		}
	}
	free(directory);
	free(line);
	free(argd);
	return (0);
}
