#include "shell.h"

/**
 * genv - This returns the string array copy of environ
 * @par: This structure contains potential arguments
 *
 * Return: Always 0
 */
char **genv(info_t *par)
{
	if (!par->env || par->change_env)
	{
		par->env = str_lst(par->en);
		par->change_env = 0;
	}
	return (par->env);
}

/**
 * remenv - This removes an environment variable
 * @par: This is a structure that contains potential arguments
 * @v: This is the string environment variable property
 *
 * Return: 1 on delete and 0 otherwise
 */
int remenv(info_t *par, char *v)
{
	list_t *nde = par->en;
	size_t a = 0;
	char *i;

	if (!nde || !v)
		return (0);
	while (nde)
	{
		i = begin(nde->str, v);
		if (i && *i == '=')
		{
			par->change_env = nde_delete(&(par->en), a);
			a = 0;
			nde = par->en;
			continue;
		}
		nde = nde->nxt;
		a++;
	}
	return (par->change_env);
}

/**
 * I_env - This initializes a new environment var or can modify an existing one
 * @par: This is  a  structure containing potential arguments
 * @v: This is the string environment variable property
 * @va: This is the string environment variable value
 *
 * Return: Always 0
 */
int I_env(info_t *par, char *v, char *va)
{
	char *b = NULL;
	list_t *nde;
	char *i;

	if (!v || !va)
		return (0);

	b = malloc(slen(v) + slen(va) + 2);
	if (!b)
		return (1);
	scpy(b, v);
	scat(b, "=");
	scat(b, va);
	nde = par->env;
	while (nde)
	{
		i = s_with(nde->str, v);
		if (i && *i == '=')
		{
			free(nde->str);
			nde->str = b;
			par->change_env = 1;
			return (0);
		}
		nde = nde->nxt;
	}
	add_nde_e(&(par->env), b, 0);
	free(b);
	par->change_env = 1;
	return (0);
}
