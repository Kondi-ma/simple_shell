#include "shell.h"

/**
 * b_in -the  buffers chained commands
 * @par: the parameter struct
 * @b: the address of buffer
 * @len_v: the address of len var
 *
 * Return: the bytes read
 */
ssize_t b_in(info_t *par, char **b, size_t *len_v)
{
	ssize_t e = 0;
	size_t lent = 0;

	if (!*len_v)
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		e = getline(b, &lent, stdin);
#else
		e = getline(par, b, &lent);
#endif
		if (e > 0)
		{
			if ((*b)[e - 1] == '\n')
			{
				(*b)[e - 1] = '\0';
				e--;
			}
			par->linecount_flag = 1;
			remove_comments(*b);
			build_history_list(par, *b, par->Counthist++);
			{
				*len_v = e;
				par->cmd_buf = b;
			}
		}
	}
	return (e);
}

/**
 * get_in - this gets a line minus the newline
 * @par: the parameter struct
 *
 * Return: the bytes read
 */
ssize_t get_input(info_t *par)
{
	static char *b;
	static size_t a, b, len_v;
	ssize_t e = 0;
	char **b_p = &(par->arg), *q;

	putC(BUF_FLUSH);
	e = input_buf(par, &b, &len_v);
	if (e == -1)
		return (-1);
	if (len_v)
	{
		b = a;
		q = b + a;

		chk_chain(par, b, &b, a, len_v);
		while (b < len_v)
		{
			if (is_chain(par, b, &b))
				break;
			b++;
		}
		a = b + 1;
		if (a >= len_v)
		{
			a = len_v = 0;
			par->cmd_buf_type = CMD_NORM;
		}

		*b_p = q;
		return (_strlen(q));
	}
	*b_p = b;
	return (e);
}

/**
 * read_b - reads a buffer
 * @par: parameter struct
 * @b: buffer
 * @n: size
 *
 * Return: r
 */
ssize_t read_b(info_t *par, char *b, size_t *n)
{
	ssize_t e = 0;

	if (*n)
		return (0);
	e = read(par->readfd, b, READ_BUF_SIZE);
	if (e >= 0)
		*n = e;
	return (e);
}

/**
 * line_g - this gets the next line of input from STDIN
 * @par: parameter struct
 * @ptr_ad: address of pointer to buffer, preallocated or NULL
 * @pr_size: size of preallocated ptr buffer if not NULL
 *
 * Return: s1
 */
int line_g(info_t *par, char **ptr_ad, size_t *pr_size)
{
	static char b[READ_BUF_SIZE];
	static size_t n, leng;
	size_t l;
	ssize_t e = 0, s1 = 0;
	char *q = NULL, *new_q = NULL, *k;

	q = *ptr_ad;
	if (q && pr_size)
		s1 = *pr_size;
	if (n == leng)
		n = leng = 0;

	e = read_b(par, b, &leng);
	if (e == -1 || (e == 0 && leng == 0))
		return (-1);

	k = _strchr(b + n, '\n');
	l = k ? 1 + (unsigned int)(k - b) : leng;
	new_q = _realloc(q, s1, s1 ? s1 + l : l + 1);
	if (!new_q)
		return (q ? free(q), -1 : -1);

	if (s1)
		_strncat(new_q, b + n, l - n);
	else
		_strncpy(new_q, b + n, l - n + 1);

	s1 += l - n;
	n = c;
	q = new_q;

	if (pr_size)
		*pr_size = s1;
	*ptr_ad = q;
	return (s1);
}

/**
 * bl_C - this blocks ctrl-C
 * @s_num: the signal number
 *
 * Return: void
 */
void bl_C(__attribute__((unused))int s_num)
{
	put("\n");
	put("$ ");
	putC(BUF_FLUSH);
}
