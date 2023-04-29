#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "main.h"
void sigint_handler(UNUSED int signum)
{
	printf("\n");
	printf("$ ");
	fflush(stdout);
}
/**
 * interactive_launch - shell code for the interactive mode
 * @ac: argument count
 * @av: argument vector
 * @envp: enviromental variables
 * Return: 0 if successful, -1 if error
 */
int interactive_launch(int UNUSED ac, char UNUSED **av, char  UNUSED **envp)
{
	char *line = NULL, **argd = NULL, *directory = NULL;
	size_t len = 0, toklen;
	int llen, size = 0, i, id, exec_rtn, status;
	char *strddup;
	static int count = 1;

	signal(SIGINT, sigint_handler);
	while (size == 0)
	{
		write(1, "$ ", 2);
		llen = getline(&line, &len, stdin);
		if (llen == -1)
		{
			printf("\n");
			free(line);
			break;
		}
		if (llen == 0)
			continue;
		remove_newline(line, llen);
		if (isSpace(line))
		{
			continue;
		}
		strddup = _strdup(line);
		argd = _strtok(strddup, " ", &toklen);
		directory = ff_in_path(argd[0]);
		free(strddup);
		if (directory == NULL)
		{
			fprintf(stderr, "%s: %d : %s: not found\n", av[0], count, argd[0]);
			count++;
			for (i = 0; argd[i] != NULL; i++)
				free(argd[i]);
			free(argd);
			continue;
		}
		argd[0] = directory;
		id = fork();
		if (id == 0)
		{
			exec_rtn = execve(argd[0], argd, envp);
			if (exec_rtn == -1)
				perror("execve");
			exit(2);
		}
		else
		{
			wait(&status);
			for (i = 0; argd[i] != NULL; i++)
				free(argd[i]);
			free(argd);
		}
	}
	return (0);
}
int non_interactive_launch(int UNUSED ac, char UNUSED **av, char UNUSED **envp)
{
	int llen, i, id, exec_rtn, status;
	static int count = 1;
	char *line = NULL, **argd = NULL, *strddup, *directory = NULL;
	char *buffer = malloc(BUFSIZ);
	size_t toklen;

	llen = read(STDIN_FILENO, buffer, BUFSIZ);
	if (llen == 0)
		exit(EXIT_SUCCESS);
	else if (llen == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	line = buffer;
	remove_newline(line, llen);
	if (isSpace(line))
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	strddup = _strdup(line);
	argd = _strtok(strddup, " ", &toklen);
	directory = ff_in_path(argd[0]);
	free(strddup);
	free(line);
	if (directory == NULL)
	{
		fprintf(stderr, "%s: %d : %s: not found\n", av[0], count, argd[0]);
		count++;
		for (i = 0; argd[i] != NULL; i++)
			free(argd[i]);
		free(argd);
		exit(EXIT_FAILURE);
	}
	argd[0] = directory;
	id = fork();
	if (id == 0)
	{
		exec_rtn = execve(argd[0], argd, envp);
		if (exec_rtn == -1)
			perror("execve");
		exit(2);
	}
	else
	{
		wait(&status);
		for (i = 0; argd[i] != NULL; i++)
			free(argd[i]);
		free(argd);
	}
	return (0);
}
