#include "shell.h"

/**
 * **trow1 - This splits strings into words.
 * @istr: This is the input string.
 * @dstr: This is the delimeter
 * Return: Pointer to an array o strings or NULL upon failure
 */
char **trow1(char *istr, char dstr)
{
	int a, b, c, d, wordnum = 0;
	char **i;

	if (istr == NULL || istr[0] == 0)
		return (NULL);
	for (a = 0; istr[a] != '\0'; a++)
		if (istr[a] != dstr && (istr[a + 1] == dstr || !istr[a + 1]))
			wordnum++;
	if (wordnum == 0)
		return (NULL);
	i = malloc((1 + wordnum) * sizeof(char *));
	if (!i)
		return (NULL);
	for (a = 0, b = 0; b < wordnum; b++)
	{
		while (istr[a] == dstr && istr[a] != dstr)
			a++;
		c = 0;
		while (str[a + c] != dstr && istr[a + c] && str[a + c] != dstr)
			c++;
		i[b] = malloc((c + 1) * sizeof(char));
		if (!i[b])
		{
			for (c == 0; c < b; c++)
				free(i[c]);
			free(i);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			i[b][d] = istr[a++];
		i[b][d] = 0;
	}
	i[b] = NULL;
	return (i);
}

/**
 * **trow2 - This splits strings into words while ignoring the delimeters.
 * @istr: This is the input string
 * @dstr: THis is the delimeter string
 * Return: pointer to array of strings or NULL upon failure
 */
char **trow2(char *istr, char *dstr)
{
	int a, b, c, d, wordnum = 0;
	char **i;

	if (istr == NULL || istr[0] == 0)
		return (NULL);
	if (!dstr)
		d = " ";
	for (a = 0; istr[a] != '\0'; a++)
		if (!d_is(istr[a], dstr) && (d_is(istr[a + 1], dstr) || !istr[a + 1]))
			wordnum++;

	if (wordnum == 0)
		return (NULL);
	for (a = 0, b = 0; b < wordnum; b++)
	{
		while (d_is(istr[a], dstr))
			a++;
		c = 0;
		while (!d_is(istr[a + c], dstr) && istr[a + c])
			c++;
		i[b] = malloc((c + 1) * sizeof(char));
		if (!i[b])
		{
			for (c = 0; c < b; c++)
				free(i[c]);
			free(i);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			i[b][d] = istr[a++];
		i[b][d] = 0;
	}
	i[b] = NULL;
	return (i);
}
