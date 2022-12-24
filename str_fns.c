#include "main.h"

/**
* _strlen - finds the length of a string
* @s: the string in question
* Return: the length of string s
*/

int _strlen(char *s)
{
	int count = 0;

	while (*(s + count) != '\0')
	{
		count++;
	}

	return (count);
}


/**
* _strcmp - compares two strings
* @s1: the first string
* @s2: the second string
* Return: 0 if the two strings are equal
* 1 if s1 is greater than s2 and -1 otherwise
*/

int _strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
		i++;

	if (s1[i] > s2[i])
		return (1);
	else if (s1[i] < s2[i])
		return (-1);
	else
		return (0);
}

/**
* _strcpy - copies string from one buffer to  another
* @dest: destination buffer
* @src: source buffer
* Return: a pointer to the destination pointer
*/

char *_strcpy(char *dest, char *src)
{
	int count;

	count = 0;

	while (count >= 0)
	{
		*(dest + count) = *(src + count);
		if (*(src + count) == '\0')
			break;

		count++;
	}
	return (dest);
}




/**
* _strcat - concatenates two strings
* @dest: the first string
* @src:L the second string
* Return: a pointer to dest
*/

char *_strcat(char *dest, char *src)
{
	int i;
	int j;
	int  d_len;
	int s_len;

	d_len = _strlen(dest);
	s_len = _strlen(src);

	for (i = 0, j = d_len ; (i <= s_len + 1) && (j <= d_len + s_len); i++, j++)
		dest[j] = src[i];

	return (*&dest);
}


