#include <stdio.h>
#include <unistd.h>
#include "main.h"
/**
 * main - the main function
 * @ac: argument count
 * @av: argument vector
 * @envp: enviromental variable
 * Return: Always 0.
 */
int main(int ac, char **av, char **envp)
{
	int interactive = isatty(STDIN_FILENO);

	if (interactive)
	{
		interactive_launch(ac, av, envp);
	}
	else if (!interactive)
	{
		non_interactive_launch(ac, av, envp);
	}
	return (0);
}
