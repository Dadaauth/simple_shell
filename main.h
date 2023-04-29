#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
#define UNUSED __attribute__((unused))
int interactive_launch(int ac, char **av, char **envp);

int non_interactive_launch(int ac, char **av, char **envp);

bool isSpace(const char *str);

int remove_newline(char *str, int length);

char *ff_in_path(char *str);

size_t lenOfStr(char *str);

char *_strdup(char *str);

char **_strtok(char *str, char *delim, size_t *length);

int _strcmp(char *str1, char *str2);

char *_strcpy(char *dest, char *src);

size_t getTokLen(char *str, char *delim);

#endif
