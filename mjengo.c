#include "shell.h"

/**
 * sh_exit - exits the shell
 * @par: Structure containing potential arguments.
 *
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int sh_exit(info_t *par)
{
	int exit_chk;

	if (par->argv[1])
	{
		exit_chk = _erratoi(par->argv[1]);
		if (exit_chk == -1)
		{
			par->stat = 2;
			print_error(par, "Illegal number: ");
			put(par->argv[1]);
			putC('\n');
			return (1);
		}
		par->err_num = _erratoi(par->argv[1]);
		return (-2);
	}
	par->err_num = -1;
	return (-2);
}

/**
 * change_cd - changes the current directory of the process
 * @par: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int chane_cd(info_t *par)
{
	char *t, *dir, buffer[1024];
	int chdir_ret;

	t = getcwd(buffer, 1024);
	if (!t)
		put("TODO: >>getcwd failure emsg here<<\n");
	if (!par->argv[1])
	{
		dir = _getenv(par, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = _getenv(par, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(par->argv[1], "-") == 0)
	{
		if (!_getenv(par, "OLDPWD="))
		{
			put(t);
			putC('\n');
			return (1);
		}
		put(_getenv(par, "OLDPWD=")), putC('\n');
		chdir_ret =
			chdir((dir = _getenv(par, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(par->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(par, "can't cd to ");
	        put(par->argv[1]), putC('\n');
	}
	else
	{
		s_env(par, "OLDPWD", genv(par, "PWD="));
		s_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * change_cd - changes the current directory of the process
 * @par: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int change_cd(info_t *par)
{
	char **arg_array;

	arg_array = par->argv;
	put("help call works. Function not yet implemented \n");
	if (0)
		put(*arg_array);
	return (0);
}
