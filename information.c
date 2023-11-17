#include "shell.h"

/**
 * i_info - initializes info_t struct
 * @par: struct address
 */
void i_info(info_t *par)
{
	par->argu = NULL;
	par->argv = NULL;
	par->path = NULL;
	par->argc = 0;
}

/**
 * s_info - initializes info_t struct
 * @par: struct address
 * @arv: argument vector
 */
void s_info(info_t *par, char **arv)
{
	int a = 0;

	par->f_name = arv[0];
	if (par->argu)
	{
		par->argv = strtow(par->argu, " \t");
		if (!par->argv)
		{

			par->argv = malloc(sizeof(char *) * 2);
			if (par->argv)
			{
				par->argv[0] = _strdup(par->argu);
				par->argv[1] = NULL;
			}
		}
		for (a = 0; par->argv && par->argv[a]; a++);
		par->argc = a;

		replace_aka(par);
		replace_Vars(par);
	}
}

/**
 * f_info - frees info_t struct fields
 * @par: struct address
 * @f_all: true if freeing all fields
 */
void f_info(info_t *par, int f_all)
{
	ffree(par->argv);
	par->argv = NULL;
	par->path = NULL;
	if (f_all)
	{
		if (!par->cmd_buf)
			free(par->argu);
		if (par->env)
			f_list(&(par->env));
		if (par->hist)
			f_list(&(par->hist));
		if (par->aka)
			f_list(&(par->aka));
		ffree(par->environ);
			par->environ = NULL;
		b_free((void **)par->cmd_buf);
		if (par->readfd > 2)
			close(par->readfd);
		putC(BUF_FLUSH);
	}
}
