#ifndef MAIN_H
#define MAIN_H

#define UNUSED __attribute__((unused))

extern char **environ;

int shell(char **av);

size_t lenOfStr(char *str);

size_t getTokLen(char *str, char *delim);

char *_strdup(char *str);

char **_strtok(char *str, char *delim, size_t *length);

char *ff_in_path(char *str);

int _strcmp(char *str1, char *str2);

char *_strcpy(char *dest, char *src);

int _isspace(char *str);

char **_exitshell(char *str);

#endif
