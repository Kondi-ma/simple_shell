#include "shell.h"

/**
 * sh - main shell loop
 * @par: the parameter & return info struct
 * @avm: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int sh(info_t *par, char **avm)
{
	ssize_t e = 0;
	int builtin_ret = 0;

	while (e != -1 && builtin_ret != -2)
	{
		clear_info(par);
		if (interactive(par))
			put("$ ");
		putC(BUF_FLUSH);
		e = get_input(par);
		if (e != -1)
		{
			set_info(par, avm);
			builtin_ret = find_builtin(par);
			if (builtin_ret == -1)
				find_cmd(par);
		}
		else if (interactive(par))
			putC('\n');
		free_info(par, 0);
	}
	write_history(par);
	free_info(psr, 1);
	if (!interactive(par) && par->stat)
		exit(par->stat);
	if (builtin_ret == -2)
	{
		if (par->err_num == -1)
			exit(par->stat);
		exit(par->err_num);
	}
	return (builtin_ret);
}

/**
 * f_builtin - finds a builtin command
 * @par: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *par)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhist},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myaka},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(par->argv[0], builtintbl[a].type) == 0)
		{
			par->Countline++;
			built_in_ret = builtintbl[a].func(par);
			break;
		}
	return (built_in_ret);
}

/**
 * f_cmd - finds a command in PATH
 * @par: the parameter & return info struct
 *
 * Return: void
 */
void f_cmd(info_t *par)
{
	char *ph = NULL;
	int a, c;

	par->ph = par->argv[0];
	if (par->Countline_flag == 1)
	{
		par->Countline++;
		par->Countline_flag = 0;
	}
	for (a = 0, c = 0; par->arg[a]; a++)
		if (!is_delim(par->arg[a], " \t\n"))
			c++;
	if (!c)
		return;

	ph = find_ph(par, _getenv(par, "PATH="), par->argv[0]);
	if (ph)
	{
		par->ph = ph;
		fork_cmd(par);
	}
	else
	{
		if ((interactive(par) || _getenv(par, "PATH=")
			|| par->argv[0][0] == '/') && is_cmd(par, par->argv[0]))
			fork_cmd(par);
		else if (*(par->argu) != '\n')
		{
			par->stat = 127;
			print_error(par, "not found\n");
		}
	}
}

/**
 * fk_cmd - forks a an exec thread to run cmd
 * @par: the parameter & return info struct
 *
 * Return: void
 */
void fk_cmd(info_t *par)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(par->ph, par->argv, get_environ(par)) == -1)
		{
			free_info(par, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(par->stat));
		if (WIFEXITED(par->stat))
		{
			par->stat = WEXITSTATUS(info->status);
			if (par->stat == 126)
				print_error(par, "Permission denied\n");
		}
	}
}
