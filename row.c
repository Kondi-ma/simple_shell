#include "shell.h"

/**
 * trow1 - This splits strings into words.
 * @istr: This is the input string.
 * @dstr: This is the delimeter
 * Return: Pointer to an array o strings or NULL upon failure
 */
char **trow1(char *istr, char dstr)
{
	int a, b, c, d, wordnum = 0;
	char **i;


