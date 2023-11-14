#include "shell.h"

/**
 * s_copy - it copies a string
 * @dt: destination
 * @sc: source
 *
 * Return: the pointer to the destination
 */
char *s_copy(char *dt, char *sc)
{
	int a = 0;

	if (dt == sc || sc == 0)
		return (dt);
	while (sc[a])
	{
		dt[a] = sc[a];
		a++;
	}
	dt[a] = 0;
	return (dt);
}

