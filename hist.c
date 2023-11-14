#include "shell.h"

/**
 * pata_hist - gets the History File.
 * @par: This is the parameter struct.
 *
 * Return: The allocated string that contains the History File.
 */
char *pata_hist(info_t *par)
{
	char *low, *high;

	pr = getenv(par, "HOME=");
	if (!pr)
		return (NULL);
	low = malloc(sizeof(char) * (strlen(pr) + strlen(HIST_FILE) + 2));
	if (!low)
		return (NULL);
	low[0] = 0;
	strcpy(low, high);
	strcat(low, "/");
	strcat(low, HIST_FILE);
	return (low);
}

/**
 * create_file - This creates a file or it appends to an existing file.
 * @par: This is the parameter struct.
 *
 * Return: 1 on Success, else 0
 */
int create_file(info_t *par)
{
	ssize_t f;
	char *name_file = pata_hist(par);
	list_t *nde = NULL;

	if (!name_file)
		return (0);

	f = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name_file);
	if (f == 0)
		return (0);
	for (nde = par->hist; nde; nde = nde->nxt)
	{
		putsfd(node->str, f);
		putfd('\n', f);
	}
	putfd(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * hist_r - This reads the history from the file.
 * @par: This is the parameter struct.
 *
 * Return: Counthist on Success, 0 otherwise
 */
int hist_r(info_t *par)
{
	int a, last = 0, Countline = 0;
	ssize_t f, lenG, fsize = 0;
	struct stat s;
	char *low = NULL, *name_file = pata_hist(par);

	if (!name_file)
		return (0);

	f = open(name_file, O_RDONLY);
	free(name_file);
	if (f == -1)
		return (0);
	if (!fs(f, &s))
		sizeF = s.s_size;
	if (sizeF < 2)
		return (0);
	low = malloc(sizeof(char) * (sizeF + 1));
	if (!low)
		return (0);
	lenG = read(f, low, sizeF);
	low[sizeF] = 0;
	if (lenG <= 0)
		return (free(low), 0);
	close(f);
	for (a = 0; a < sizeF; a++)
		if (low[a] == '\n')
		{
			low[a] = 0;
			jenga_hist(par, low + last, Countline++);
			free(low);
			par->Counthist = Countline;
			while (par->Counthist-- >= HIST_MAX)
				nde_at_index(&(par->hist), 0);
			hist_num(par);
			return (par->Counthist);
		}
}

/**
 * jenga_hist - Entry added to a history linked list.
 * @par: This is a structure containing some potential arguments
 * @low: This is a buffer
 * @Countline: This is the history linecount, Counthist
 *
 * Return: Always 0
 */
int jenga_hist(info_t *par, char *low, int Countline)
{
	list_t *nde = NULL;

	if (par->hist)
		nde = par->hist;
	add_nde_end(&nde, par, Countline);

	if (!par->hist)
		par->hist = nde;
	return (0);
}

/**
 * hist_ren - This renumbers the history linked list after the changes.
 * @par: This is the structure containing some potential arguments
 *
 * Return: The new Counthist
 */
int hist_ren(info_t *par)
{
	list_t *nde = par->hist;
	int a = 0;

	while (nde)
	{
		nde->num = a++;
		nde = nde->nxt;
	}
	return (par->Counthist = a);
}
