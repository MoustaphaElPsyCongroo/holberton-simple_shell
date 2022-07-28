#ifndef simple_shell
#define simple_shell
extern char **environ;
char **split(char *str);
int exec_command(char **path, char **env);
char *readcommand(void);

#endif
