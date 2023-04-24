#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include "main.h"
/**
 * shell - first simple version of super simple shell
 * @av: argument vector of the main function passed to
 * the shell fucntion
 * Return: Always 0.
 */
int shell(char **av)
{
	char *line = NULL;
	size_t len = 0;
	int llen, exec_rtn, stop = 1, id, status;
	char **argd;

	while (stop == 1)
	{
		printf(" ($) ");
		llen = getline(&line, &len, stdin);
		if (llen > 0 && line[llen - 1] == '\n')
			line[llen - 1] = '\0';
		if (llen == -1 || strcmp(line, "exit") == 0)
			break;
		id = fork();
		if (id == 0)
		{
			argd = malloc(2 * sizeof(char *));
			argd[0] = line;
			argd[1] = NULL;
			exec_rtn = execve(argd[0], argd, environ);
			if (exec_rtn == -1)
				printf("%s: No such file or directory\n", av[0]);
			free(line);
			free(argd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return (0);
}
