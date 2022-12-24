#include "main.h"

/**
 * build_plist - builds a linked list of
 * the PATH directories
 * @path: the PATH environment variable
 * obtained from _getenv
 *
 * Return: a pointer to the head node of the list
 * or a NULL pointer if path is NULL or on error
 */

plist *build_plist(char *path)
{
	char *token;
	plist *head;
	char *temp_path;

	if (path == NULL)
		return (NULL);

	temp_path = malloc(sizeof(char) * _strlen(path) + 1);
	if (temp_path == NULL)
		exit(EXIT_FAILURE);

	_strcpy(temp_path, path);
	head = NULL;
	token = strtok(temp_path, "=");
	temp_path = strtok(NULL, "=");

	token = strtok(temp_path, ":");
	while (token != NULL)
	{
		append(&head, token);
		token = strtok(NULL, ":");
	}
	return (head);
}



/**
 * _getenv - returns an environment variable
 * @var_name: name of environment variable
 *
 * Return: the environment variable specified by filename
 * or NULL if the environment variable could not be found
 */

char *_getenv(const char *var_name)
{
	char *var;
	char *buffer;
	char *token;
	int n;

	n = 0;
	var = malloc(sizeof(char) * _strlen(environ[n] + 1));
	_strcpy(var, environ[n]);

	while (var != NULL)
	{
		buffer = malloc(sizeof(char) * _strlen(var) + 1);
		_strcpy(buffer, var);
		token = strtok(buffer, " = ");

		if (_strcmp(token, var_name) == 0)
		{
			free(buffer);
			return (var);
		}
		n++;
		free(var);
		free(buffer);
		var = malloc(sizeof(char) * _strlen(environ[n] + 1));
		_strcpy(var, environ[n]);
	}


	return (NULL);
}


/**
 * _which - searches for a file in the current PATH
 * @head: a pointer to the head node of a likned list
 * of the PATH variable
 * @filename: name of file to be searched for
 *
 * Return: the name of the directory where file was found
 * or a NULL pointer if file was not found
 */

char *_which(plist *head, const char *filename)
{
	plist *temp;
	DIR *folder;
	struct dirent *entry;
	char *dirname;

	dirname = malloc(256);
	if (head == NULL)
	{
		dirname = NULL;
		return (dirname);
	}

	temp = head;
	while (temp != NULL)
	{
		folder = opendir(temp->d_name);
		if (folder == NULL)
		{
			dirname = NULL;
			return (dirname);
		}

		while ((entry = readdir(folder)))
		{
			if (_strcmp(entry->d_name, filename) == 0)
			{
				_strcpy(dirname, temp->d_name);
				closedir(folder);
				return (dirname);
			}
		}
		closedir(folder);
		temp = temp->next;
	}
	dirname = NULL;
	return (dirname);
}


/**
 * append -  adds a node at the end of the PATH linked list
 * @head_ref: a pointer to the head node of the list
 * @d_name: name of the path directory to be added to the list
 *
 * Returns: nothing
 */

void append(plist **head_ref, char *d_name)
{
	plist *new_node;
	plist *last;

	new_node = malloc(sizeof(plist));
	if (new_node == NULL)
		return;

	last = *head_ref;

	new_node->d_name = d_name;
	new_node->next = NULL;

	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
}



