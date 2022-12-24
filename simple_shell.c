#include "main.h"

/**
 * main - entry point of the shell program
 * @argc: argument count
 * @av: an array of arguments
 *
 * Return: 0
 */


int main(__attribute__((unused)) int argc, char **av)
{

	plist *list;
	int first_time;
	char *path;
	char *bin_path;
	int status;
	char program_name[20];
	char cmd[100];
	char *params[256];
	char *command;

	path = _getenv("PATH");
	list = build_plist(path);
	bin_path = _which(list, "ls");
	_strcat(bin_path, "/");
	_strcpy(program_name, av[0]);

	status = 1;
	command = NULL;

	if (!(isatty(STDIN_FILENO)))
	{
		read_command(cmd, params);
		command = parsecmd(cmd, bin_path, list, &first_time);
		if (command == NULL)
		{
			command_error(program_name, cmd);
			exit(EXIT_SUCCESS);
		}
		status = execute(command, params, program_name);
		return (1);
	}

	core(cmd, command, params, program_name, bin_path, list, first_time, status);

	return (0);
}


