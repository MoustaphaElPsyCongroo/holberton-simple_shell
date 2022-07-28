#ifndef simple_shell
#define simple_shell
extern char **environ;
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *alloc_concat(char *dest, char *tocat);
char *_getenv(const char *name);
char *checkpath(char *filename);
char **split(char *str);
int exec_command(char **path, char **env, char *prog_name);
char *readcommand(void);

#endif
