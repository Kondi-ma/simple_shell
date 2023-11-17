#include "shell.h"

/**
 * _myhist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @par: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _myhist(info_t *par)
{
	print_list(par->hist);
	return (0);
}

/**
 * s_alias - sets alias to string
 * @par: parameter struct
 * @str1: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int s_alias(info_t *par, char *str1)
{
	char *q, k;
	int re;

	q = _strchr(str1, '=');
	if (!q)
		return (1);
	k = *q;
	*q = 0;
	re = delete_node_at_index(&(par->aka),
		get_node_index(par->aka, node_starts_with(par->aka, str1, -1)));
	*q = k;
	return (re);
}

/**
 * s_alias - sets alias to string
 * @par: parameter struct
 * @str1: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int s_alias(info_t *par, char *str1)
{
	char *q;

	q = _strchr(str1, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(par, str1));

	unset_alias(par, str1);
	return (add_node_end(&(par->aka), str1, 0) == NULL);
}

/**
 * p_alias - prints an alias string
 * @nde: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int p_alias(list_t *nde)
{
	char *q = NULL, *i = NULL;

	if (nde)
	{
		q = _strchr(nde->str1, '=');
		for (i = nde->str1; i <= q; i++)
			_putchar(*i);
		putC('\'');
		put(q + 1);
		put("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myaka - mimics the alias builtin (man alias)
 * @par: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _myaka(info_t *par)
{
	int a = 0;
	char *q = NULL;
	list_t *nde = NULL;

	if (par->argc == 1)
	{
		nde = par->aka;
		while (nde)
		{
			print_aka(nde);
			nde = nde->nxt;
		}
		return (0);
	}
	for (a = 1; par->argv[a]; a++)
	{
		q = _strchr(par->argv[a], '=');
		if (q)
			s_alias(par, par->argv[a]);
		else
			p_alias(node_starts_with(par->aka, par->argv[a], '='));
	}

	return (0);
}
