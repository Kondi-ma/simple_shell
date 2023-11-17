#include "shell.h"

/**
 *s_mem - fills memory with a constant byte
 *@am: the pointer to the memory area
 *@fb: the byte to fill *am with
 *@an: the amount of bytes to be filled
 *Return: (am) a pointer to the memory area am
 */
char *s_mem(char *am, char fb, unsigned int an)
{
	unsigned int a;

	for (a = 0; a < an; a++)
		am[a] = fb;
	return (am);
}

/**
 * f_free - frees a string of strings
 * @ss: string of strings
 */
void f_free(char **ss)
{
	char **s = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(s);
}

/**
 * realloc - reallocates a block of memory
 * @pprev: pointer to previous malloc'ated block
 * @p_size: byte size of previous block
 * @n_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc(void *pprev, unsigned int p_size, unsigned int n_size)
{
	char *q;

	if (!pprev)
		return (malloc(n_size));
	if (!n_size)
		return (free(pprev), NULL);
	if (n_size == p_size)
		return (pprev);

	q = malloc(n_size);
	if (!q)
		return (NULL);

	p_size = p_size < n_size ? p_size : n_size;
	while (p_size--)
		q[p_size] = ((char *)pprev)[p_size];
	free(pprev);
	return (q);
}
