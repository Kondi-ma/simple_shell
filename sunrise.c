#include "shell.h"

/**
 * put - this prints an input string
 * @st: this is the string to be printed
 *
 * Return: Nothing
 */
void put(char *st)
{
	int a = 0;

	if (!st)
		return;
	while (st[a] != '\0')
	{
		putC(st[a]);
		a++;
	}
}

/**
 * putC - writes the character e to stderr
 * @e: This is the character to print
 *
 * Return: 1 on success
 * Upon error, -1 is returned, and errno is set appropriately
 */
int putC(char e)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (e == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] = e;
	return (1);
}

/**
 * putd - writes the character e to given f
 * @e: This is the character to print
 * @f: this is the filedescriptor to write to
 *
 * Return: On success 1
 * Upon error, -1 returned, errno set appropriately
 */
int putd(char e, int f)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (e == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(f, b, a);
		a = 0;
	}
	if (e != BUF_FLUSH)
		b[a++] = e;
	return (1);
}

/**
 * putdd - this prints an input string
 * @st: this is the string to be printed
 * @f: this is the filedescriptor to write
 *
 * Return: num of characters put
 */
int putdd(char *st, int f)
{
	int a = 0;

	if (!st)
		return (0);
	while (*st)
	{
		a = putdd(*st++, f);
	}
	return (a);
}
