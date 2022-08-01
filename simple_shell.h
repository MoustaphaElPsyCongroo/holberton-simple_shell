#ifndef simple_shell
#define simple_shell
extern char **environ;
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *alloc_concat(char *str1, char *str2);
char *_getenv(const char *name);
char *checkfolderlist(char **path_arr, char *slash_file);
char **split(char *str, char *delim);
char **splitcommand(char *command, char **folderlist, int is_fullpath);
char **split_nopath(char *slash_command, int is_fullpath);
char *readcommand(char *);
char **parsecommand(char *slash_command, int is_fullpath);
char *slashifycommand(char *command, int *is_fullpath);
int exec_command(char **path, char **env, char *prog_name, int is_terminal);
void excommand(
		char **argv,
		char *slash_command,
		char **environ,
		char *prog_name,
		char *total_commands,
		int is_terminal,
		int is_fullpath,
		int *stop);
char *err_notfound(char *command, char *total_commands, char *prog_name);
void free_everything(int n, ...);
#endif
