#include "main.h"

/**
 * core -  runs the Shell's loop and execution routine
 * @cmd: the command
 * @command: string to contain parsed command
 * @params: array of arguments
 * @program_name: name of the file containing the shell's main program
 * @list: head of the PATH linked list
 * @first_time: specifies if this is the first time the shell is running
 * @bin_path: the directory where previous commands were found
 * @status: value returned by execution of command
 *
 * Return: nothing
 */

void core(char *cmd, char *command, char **params, char *program_name,
char *bin_path, plist *list, int first_time, int status)
{
	do {
		prompt();
		read_command(cmd, params);
		command = parsecmd(cmd, bin_path, list, &first_time);
		if (command == NULL)
		{
			command_error(program_name, cmd);
			continue;
		}

		status = execute(command, params, program_name);
	} while (status);

}


/**
 * command_error - prints a command not found error
 * @program_name: name of the file containing the Shell's main
 * @cmd: name of the command
 *
 * Return: nothing
 */

void command_error(char *program_name, char *cmd)
{

	write(STDIN_FILENO, program_name, _strlen(program_name) + 1);
	write(STDIN_FILENO, ": ", 2);
	write(STDIN_FILENO, cmd, _strlen(cmd) + 1);
	write(STDIN_FILENO, ": command not found\n", 21);
}

/**
 * is_builtin - checks if command is a builtin
 * @cmd: the command
 *
 * Return: 1 if it is a builtin, 0 otherwise
 */

int is_builtin(char *cmd)
{
	int i;
	char *builtin_str[] = {"cd", "exit", "env"};
	int num_builtins;

	num_builtins = sizeof(builtin_str) / sizeof(char *);

	for (i = 0; i < num_builtins; i++)
	{
		if (_strcmp(cmd, builtin_str[i]) == 0)
			return (1);
	}
	return (0);
}







