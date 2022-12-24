#include "main.h"


/**
 * read_command - reads command line from the terminal
 * @cmd: an array of characters that holds the command
 * @params: an array of char pointers that holds the arguments
 *
 * Return: 0 on success, exits on failure
 */

int read_command(char cmd[], char *params[])
{
	char *line;
	char *array[1024];
	char *word;
	int i;
	int j;
	size_t size;
	int bytes_read;

	i = 0;
	size = 10;
	line = malloc(size * sizeof(char));

	if (line == NULL || cmd == NULL || params == NULL)
		exit(EXIT_FAILURE);

	bytes_read = getline(&line, &size, stdin);
	if (bytes_read == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	word = strtok(line, " \n");
	while (word != NULL)
	{
		array[i++] = strdup(word);
		word = strtok(NULL, " \n");
	}

	_strcpy(cmd, array[0]);
	for (j = 0; j < i; j++)
		params[j] = array[j];

	params[j] = NULL;
	free(line);
	return (0);
}



/**
 * parsecmd -  processes the command by handling path
 * @cmd: the command
 * @path: path directory where previous commands were found
 * @list: head of the PATH linked list
 * @first_time: specifies if this is the first time the shell is running
 *
 * Return: returns parsed command,  NULL if command could
 * not be found or error
 */


char *parsecmd(char *cmd, char *path, plist *list, int *first_time)
{
	char *command;

	if (is_builtin(cmd))
	{
		command = malloc(sizeof(char) * _strlen(cmd) + 1);
		if (command == NULL)
			exit(EXIT_FAILURE);
		_strcpy(command, cmd);
	}
	else if (ispath(cmd))
	{
		if (isexe(cmd))
		{
			command = malloc(sizeof(char) * _strlen(cmd) + 1);
			if (command == NULL)
				exit(EXIT_FAILURE);
			_strcpy(command, cmd);
		}
		else
		{
			command = NULL;
		}
	}
	else if (!*first_time)
	{
		command = checkcmd(path, cmd);
	}
	else
	{
		*first_time = 0;
		if (path != NULL)
			free(path);
		path = _which(list, cmd);
		if (path == NULL)
			return (path);
		_strcat(path, "/");
		command = checkcmd(path, cmd);
	}
	return (command);
}
