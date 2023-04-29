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
	char **argptr;
	int mine, i;
	int interactive = isatty(STDIN_FILENO);

	if (interactive && (_strcmp(line, "\n") == 0 || _isspace(line) == 0))
		return (2);
	if (!interactive && _isspace(line) == 0)
		return (4);
	if (interactive && (llen == -1 || _strcmp(line, "exit\n") == 0))
	{
		if (llen == -1 && interactive)
			printf("\n");
		return (1);
	}
	if (llen > 0 && line[llen - 1] == '\n')
	{
		line[llen - 1] = '\0';
	}
	if (_strcmp(line, "env") == 0)
	{
		return (3);
	}
	argptr = _exitshell(line);
	if (argptr != NULL)
	{
		if (argptr[1] == NULL)
		{
			free(argptr[0]);
			free(argptr);
			return (1);
		}
		mine = 100 + atoi(argptr[1]);

		for (i = 0; argptr[i] != NULL; i++)
			free(argptr[i]);
		free(argptr);
		return (mine);
	}
	return (0);
}
/**
 * free_in_child - frees all memory that needs to be freed in the child process
 * @line: a pointer to free
 * @argd: a pointer to free
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
	int i = 0;

	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
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
	int llen = 0, UNUSED exec_rtn, run = 1, id, status, UNUSED i, UNUSED rtn_pp;
	int interactive = isatty(STDIN_FILENO);
	char **argd = NULL;
	static int count = 1;
	char buffer[BUFSIZ];

	signal(SIGINT, sigint_handler);
	while (run)
	{
		len = 0;
		if (interactive)
		{
			write(1, "$ ", 2);
			llen = getline(&line, &len, stdin);
		}
		if (!interactive)
		{
			llen = read(STDIN_FILENO, buffer, BUFSIZ);
			if (llen == 0)
			{
				break;
			}
			else if (llen == -1)
			{
				perror("read");
				break;
			}
			line = buffer;
		}
		rtn_pp = print_prompt(line, llen);
		if (rtn_pp == 1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (rtn_pp == 2)
		{
			free(line);
			continue;
		}
		else if (rtn_pp == 3)
		{
			print_environ();
			free(line);
			continue;
		}
		else if (rtn_pp == 4)
		{
			break;
		}
		else if (rtn_pp > 100)
		{
			if (interactive)
				free(line);
			exit(rtn_pp - 100);
		}

		strddup = _strdup(line);
		argd = _strtok(strddup, " ", &toklen);
		if (_strcmp(argd[0], "setenv") == 0)
		{
			shell_setenv(argd);
			for (i = 0; argd[i]; i++)
				free(argd[i]);
			free(argd);
			free(strddup);
			if (interactive)
				continue;
			break;
		}
		else if (_strcmp(argd[0], "unsetenv") == 0)
		{
			shell_unsetenv(argd);
			for (i = 0; argd[i]; i++)
				free(argd[i]);
			free(argd);
			free(strddup);
			if (interactive)
				continue;
			break;
		}
		if (_strcmp(argd[0], "cd") == 0)
		{
			_cd_dir(argd);
			for (i = 0; argd[i] != NULL; i++)
				free(argd[i]);
			free(argd);
			free(strddup);
			if (!interactive)
				exit(EXIT_SUCCESS);
			free(line);
			continue;
		}
		directory = ff_in_path(argd[0]);
		free(strddup);
		if (interactive)
			free(line);
		if (directory == NULL)
		{
			/**
			printf("%s: %d: %s: not found\n", av[0], count, line);
			*/
			execve(argd[0], argd, environ);
			perror(av[0]);
			count++;
			for (i = 0; argd[i] != NULL; i++)
				free(argd[i]);
			free(argd);
			continue;
		}
		else
		argd[0] = directory;
		id = fork();
		if (id == 0)
		{
			exec_rtn = execve(argd[0], argd, environ);
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
	/**
	 * free(directory);
	 */
	/**
	 * free(argd);
	 */
	return (0);
}
