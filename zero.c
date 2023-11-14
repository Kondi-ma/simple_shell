#include "shell.h"

/**
 * cmd - This determines if a file is a executable command
 * @par: This is the info struct
 * @pth: The path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd(info_t *par, char *pth)
{
	struct st_t s;
	(void)par;
	if (!pth || st_t(pth, &s))
		return (0);
	if (s.s_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_d - This duplicates characters
 * @str_pth: This is the path string
 * @anza: the starting index
 * @acha: the stopping index
 *
 * Return: pointer to a new buffer
 */
char *char_d(char *str_pth, int anza, int acha)
{
	static char b[1024];
	int a = 0, c = 0;

	for (c = 0, a = anza; a < acha; a++)
		if (str_pth[a] != ':')
			b[c++] = str_pth[a];
	b[c] = 0;
	return (b);
}

/**
 * pathfinder - It finds this command in the path string
 * @par: This is the info struct
 * @str_pth: This is the path string
 * @com: This is the path to find
 *
 * Return: The full path of command if found or NULL
 */
char *pathfinder(info_t *par, char *str_pth, char *com)
{
	int a = 0, posi = 0;
	char *pth;

	if (!str_pth)
		return (NULL);
	if ((l_str(com) > 2) && begin(com, "./"))
	{
		if (com(par, com))
			return (com);
	}
	while (1)
	{
		if (!str_pth[a] || str_pth[a] == ':')
		{
			pth = d_char(str_pth, posi, a);
			if (!*pth)
				s_cat(pth, com);
			else
			{
				s_cat(pth, "/");
				s_cat(pth, com);
			}
			if (is_com(par, pth))
				return (pth);
			if (!str_pth[a])
				break;
			posi = a;
		}
		a++;
	}
	return (NULL);
}
