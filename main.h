#ifndef MAIN_H
#define MAIN_H
#define UNUSED __attribute__((unused))
extern char **environ;

int shell(char **av);

int lenOfStr(char *str);

size_t getTokLen(char *str);

char *_strdup(char *str);

char **_strtok(char *str, char *delim, size_t *length);
#endif
