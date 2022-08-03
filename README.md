# Simple_Shell

## _Introduction_

A Shell is the software program that provides a user interface to access OS services. It is a command-line interpreter. This respository contains Simple Shell, our team project at Holberton School. This shell works on **interactive** and **non interactive** mode.

The aim of this projet was to make us comprehend how a shell works. what environment is, the difference between functions and system calls and how to create processes.

## Allowed functions used

*   `access` (man 2 access)
*   `chdir` (man 2 chdir)
*   `close` (man 2 close)
*   `closedir` (man 3 closedir)
*   `execve` (man 2 execve)
*   `exit` (man 3 exit)
*   `_exit` (man 2 _exit)
*   `fflush` (man 3 fflush)
*   `fork` (man 2 fork)
*   `free` (man 3 free)
*   `getcwd` (man 3 getcwd)
*   `getline` (man 3 getline)
*   `getpid` (man 2 getpid)
*   `isatty` (man 3 isatty)
*   `kill` (man 2 kill)
*   `malloc` (man 3 malloc)
*   `open` (man 2 open)
*   `opendir` (man 3 opendir)
*   `perror` (man 3 perror)
*   `read` (man 2 read)
*   `readdir` (man 3 readdir)
*   `signal` (man 2 signal)
*   `stat` (__xstat) (man 2 stat)
*   `lstat` (__lxstat) (man 2 lstat)
*   `fstat` (__fxstat) (man 2 fstat)
*   `strtok` (man 3 strtok)
*   `wait` (man 2 wait)
*   `waitpid` (man 2 waitpid)
*   `wait3` (man 2 wait3)
*   `wait4` (man 2 wait4)
*   `write` (man 2 write)


## Usage
This program was coded on Ubuntu 20.04 LTS

To run this program:
Clone this repo

```sh
git clone https://github.com/MoustaphaElPsyCongroo/holbertonschool-simple_shell.git
```
## Compilation

```sh
gcc -Wall -werror -wextra -pedantic *.c -o hsh
```

## Execute the command below after compilation:

```sh
$ ./hsh
```
# How to use it 
In order to use this shell, in a terminal, first run the program:
```sh
prompt$ ./hsh
```
It wil then display a simple prompt and wait for commands.
```sh
$
```

## Interactive-mode

```sh
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
## Non-interactive-mode:

```sh
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c mode_ls_2
$
$ cat mode_ls_2
/bin/ls
/bin/ls
$
$ cat mode_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
## Files
| Files | Description |
| ----- | ----------- |
| Authors |Contributors in this repository |
| README.md | information about this repository |
| exec_command.c| execute builtins and commands |
| main.c | main arguments functions |
| parsecommand.c | parses command line |
| print_errors | prints error to standard output |
| readcommand.c | reads input
| simple_shell .h | prototypes functions and hearders |
| split.c | Tokenizes a string |
|utils.c | 
|man_1_simple_shell | manual page |
