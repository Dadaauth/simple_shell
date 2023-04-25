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
	char *line = NULL, *strddup;
	size_t len = 0, toklen;
	int llen, exec_rtn, stop = 1, id, status, i;
	char **argd, **tokarr;

	while (stop == 1)
	{
		printf(" ($) ");
		llen = getline(&line, &len, stdin);
		if (llen > 0 && line[llen - 1] == '\n')
			line[llen - 1] = '\0';
		if (llen == -1 || strcmp(line, "exit") == 0)
			break;
		else if (strcmp(line, "") == 0)
			continue;

		id = fork();
		if (id == 0)
		{
			strddup = _strdup(line);

			tokarr = _strtok(strddup, " ", &toklen);

			free(strddup);

			argd = malloc((toklen + 1) * sizeof(char *));

			for (i = 0; tokarr[i]; i++)
				argd[i] = tokarr[i];

			argd[i] = NULL;
			exec_rtn = execve(argd[0], argd, environ);

			if (exec_rtn == -1)
				printf("%s: No such file or directory\n", av[0]);
			free(line);
			for (i = 0; argd[i]; i++)
				free(argd[i]);
			free(argd);
			free(tokarr);

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
