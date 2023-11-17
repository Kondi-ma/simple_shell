#include "shell.h"

/**
 * cur_env - prints the current environment
 * @par: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int cur_env(info_t *par)
{
	print_list_str(par->env);
	return (0);
}

/**
 * genv - gets the value of an environ variable
 * @par: Structure containing potential arguments.
 * @v_name: env var name
 *
 * Return: the value
 */
char *genv(info_t *par, const char *v_name)
{
	list_t *nde = par->env;
	char *q;

	while (nde)
	{
		q = begin_with(nde->str, v_name);
		if (q && *q)
			return (q);
		nde = nde->nxt;
	}
	return (NULL);
}

/**
 * s_env - Initialize a new environment variable
 * @par: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int s_env(info_t *par)
{
	if (par->argc != 3)
	{
		put("Incorrect number of arguements\n");
		return (1);
	}
	if (s_env(par, par->argv[1], par->argv[2]))
		return (0);
	return (1);
}
