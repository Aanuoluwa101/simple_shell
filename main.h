#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * pathlist - a linked list of the PATH directories
 */

typedef struct pathlist
{
	char *d_name;
	struct pathlist *next;
}plist;

extern char **environ;
void core(char *cmd, char *command, char **params, char *program_name, char *bin_path, plist *list, int first_time, int status);
int ispath(char *file);
char *parsecmd(char *cmd, char *path, plist *list, int *first_time);
plist *build_plist(char *path);
void append(plist **head_ref, char *d_name);
int is_builtin(char *cmd);
void print_list(plist *head);
void prompt(void);
int read_command(char command[], char *parameters[]);
size_t _getline(char **buffer, size_t *size, FILE *stream);
char *_getenv(const char *var_name);
int printenv(__attribute__((unused)) char **args, char *program_name);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, char *src);
char *_which(plist *head, const char *filename);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int cd(char **agrs, char *program_name);
int exit_shell(char **args, char *program_name);
char *checkcmd(char *path, char *cmd);
int isexe(char *pathname);
void print_error(char *cmd, char *program_name);
int child(char *cmd, char **args, char *program_name);
int execute(char *cmd, char **args, char *program_name);
void command_error(char *program_name, char *cmd);
#endif
