#include "main.h"


/**
 * child - creates a child process and executes a new program
 * @cmd: command
 * @args: an array of arguments to the command
 * @program_name: name of the file containing the shell's
 * main
 *
 * Return: 1
 */


int child(char *cmd, char **args, char *program_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		print_error("fork", program_name);
	}
	else if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
			print_error("fork", program_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

/**
 * execute - executes a program
 * @cmd: the command
 * @args: array of arguments
 * @program_name: name of the file containing the main
 *
 * Return: the return value of the program
 */

int execute(char *cmd, char **args, char *program_name)
{
	int num_builtins;
	int i;
	char *builtin_str[] = {"cd", "exit", "env"};

	int (*builtin_func[]) (char **, char *) = {&cd, &exit_shell, &printenv};


	num_builtins = sizeof(builtin_str) / sizeof(char *);

	if (_strcmp(cmd, "\n") ==  0)
		return (1);

	for (i = 0; i < num_builtins; i++)
	{
		if (_strcmp(cmd, builtin_str[i]) == 0)
			return ((*builtin_func[i])(args, program_name));
	}

	return (child(cmd, args, program_name));
}




/**
 * printenv - prints the environment
 * @args: an array of arguments to the command
 * @program_name: name of the file containing the main
 *
 * Return: 1
 */

int printenv(__attribute__((unused)) char **args,
__attribute__((unused)) char *program_name)
{
	int i;
	char *var;

	i = 0;
	var = environ[i];

	while (var != NULL)
	{
		write(STDOUT_FILENO, var, _strlen(var) + 1);
		var = environ[++i];
		if (var == NULL)
			write(STDOUT_FILENO, "\n", 1);
		else
			write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}



/**
 * exit_shell - exits the shell
 * @args: an array of arguments to the command
 * @program_name: name of the file containing the main
 *
 * Return: 0
 */

int exit_shell(char **args, __attribute__((unused)) char *program_name)
{
	if (args[1] == NULL)
		exit(EXIT_SUCCESS);

	exit(atoi(args[1]));
	return (0);
}


/**
 * cd - changes the current working directory of the shell
 * @args: an array of arguments to the command
 * @program_name: name of the file containing the main
 *
 * Return: 1
 */

int cd(char **args, __attribute__((unused)) char *program_name)
{
	int status;
	char *dir;
	char *prevdir;

	dir = malloc(sizeof(char) * 256);
	dir = args[1];
	prevdir = getcwd(NULL, 1024);

	if (dir == NULL)
	{
		dir = getenv("HOME");
		status = chdir(dir);
	}
	else if (_strcmp(dir, "-") == 0)
	{
		_strcpy(dir, prevdir);
		status = chdir(dir);
	}
	else
	{
		status = chdir(dir);
	}

	if (status == -1)
	{
		print_error("cd", program_name);
		return (1);
	}

	setenv("PWD", dir, 1);

	return (1);
}
