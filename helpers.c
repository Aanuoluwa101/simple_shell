#include "main.h"


/**
 * isexe - checks whether a file exists and is an executable
 * @pathname: name of the file
 *
 * Return: 1 if file exists and is an executable, 0 otherwise
 */

int isexe(char *pathname)
{
	if (access(pathname, F_OK && X_OK) == 0)
		return (1);
	return (0);
}


/**
 * checkcmd - returns the full pathname to  cmd
 * after checking if it exists and is executable
 * @path: the pathname of the directory containing cmd
 * @cmd: the command
 *
 * Return: a string with the full pathname of cmd or
 * NULL  pointer if cmd is not found or is not an executable
 */

char *checkcmd(char *path, char *cmd)
{
	char *command;

	command = malloc(sizeof(char) * 1280);
	_strcpy(command, path);
	_strcat(command, cmd);

	if (isexe(command))
	{
		return (command);
	}
	else
	{
		free(command);
		command = NULL;
		return (command);
	}
}


/**
 * print_error - prints error messages
 * @cmd: the command whose error is to be printed
 * @program_name: name of the file containing the shell's main program
 *
 * Returns: nothing
 */

void print_error(char *cmd, char *program_name)
{
	write(STDOUT_FILENO, program_name, _strlen(program_name) + 1);
	write(STDOUT_FILENO, ": ", 2);
	perror(cmd);
}



/**
 * ispath - checks if pathname is a path or regular filename
 * @file: name of the file
 *
 * Return: 1 if pathname is a path, 0 otherwise
 */

int ispath(char *file)
{
	if (file[0] == '.' || file[0] == '/')
		return (1);
	return (0);
}


/**
 * prompt - prints shell prompt
 *
 * Returns: nothing
 */

void prompt(void)
{
	write(STDIN_FILENO, "MercyKim# ", 11);
}
