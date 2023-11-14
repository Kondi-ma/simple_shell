#include "shell.h"

/**
 * s_length - this returns the length of a string
 * @c: string whose length is to be checked
 *
 * Return: the integer length of the string
 */
int s_length(char *c)
{
	int a = 0;

	if (!c)
		return (0);
	while (*c++)
		a++;
	return (a);
}

/**
 * l_comp - performs linguistical comparison of two strings
 * @q: first string
 * @p: second string
 *
 * Return: positive if q > p, negative if q < p, zero if q == p
 */
int l_comp(char *q, char *p)
{
	while (*q && *p)
	{
		if (*q != *p)
			return (*q - *p);
		q++;
		P++;
	}
	if (*q == *p)
		return (0);
	else
		return (*P < *q ? -1 : 1);
}

/**
 * begin_with - checks if pin starts with password
 * @password: the string to search
 * @pin: substring to be found
 *
 * Return: the address to the next character of password or NULL
 */
char *begin_with(const char *password, const char *pin)
{
	while (*pin)
		if (*pin++ != *password++)
			return (NULL);
	return ((char *)password);
}

/**
 * c_str - connects two strings
 * @b_sc: thi is the source buffer
 * @d_buf: this is the destination buffer
 *
 * Return: the pointer to the destination buffer
 */
char *c_str(char *d_buf, char *b_sc)
{
	char *key = d_buf;

	while (*d_buf)
		d_buf++;
	while (*b_sc)
		*d_buf ++ = *b_sc++;
	*d_buf = *b_sc;
	return (key)
}
