#ifndef simple_shell
#define simple_shell
extern char **environ;
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *alloc_concat(char *str1, char *str2);
char *_getenv(const char *name);
char **checkpath(char *command);
char **split(char *str, char *delim);
char **splitcommand(char *command, char **folderlist, int is_fullpath);
char *readcommand(char *);
int exec_command(char **path, char **env, char *prog_name, int is_terminal);
char *err_notfound(char *command, char *total_commands, char *prog_name);
void free_everything(int n, ...);
#endif
