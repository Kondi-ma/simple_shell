#include "shell.h"

/**
 * s_int - This converts a string into an integer
 * @c: This is the string to be converted
 * Return: 0 if no nums in the string, converted num otherwise -1 on error
 */
int s_int(char *c)
{
	int a = 0;
	unsigned long int res = 0;

	if (*c == '+')
		c++;
	for (a = 0; c[a] != '\0'; a++)
	{
		if (c[a] >= '0' && c[a] <= '9')
		{
			res *= 10;
			res += (c[a] - '0');
			if (res > INT_MAX)
				return (0);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * p_err - This prints an error message
 * @par: this is the parameter and return information struct
 * @err_str: the string containing specified error type
 * Return: 0 if there are no numbers in the string, otherwise -1 on error
 */
void p_err(info_t *par, char *err_str)
{
	put(par->name_f);
	put(": ");
	print_d(par->Countline, STDERR_FILENO);
	put(": ");
	put(par->argu[0]);
	put(": ");
	put(err_str);
}

/**
 * dprint - the function prints an integer to base 10
 * @in: input
 * @f: the filedescriptor
 *
 * Return: number of chars printed
 */
int dprint(int in, int f)
{
	int (putC)(char) = putC;
	int a, ct = 0;
	unsigned int abs, curr;

	if (f == STDERR_FILENO)
		putC = eputC;
	if (in < 0)
	{
		abs = -in;
		putC('-');
		ct++;
	}
	else
		abs = in;
	curr = abs;
	for (a = 200000000; a > 1; a /= 10)
	{
		if (abs / a)
		{
			putC('0' + curr / a);
			ct++;
		}
		curr %= a;
	}
	putC('0' + curr);
	ct++;

	return (ct);
}

/**
 * con_num - this is the converter function
 * @numb: the number
 * @ba: the base
 * @fl: the argument flags
 *
 * Return: string
 */
char *con_num(long int numb, int ba, int fl)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *point;
	unsigned long m = numb;

	if (!(fl & CONVERT_UNSIGNED) && numb < 0)
	{
		m = -numb;
		sign = '-';
	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	point = &buff[49];
	*point = '\0';

	if (sign)
		*--point = sign;
	return (point);
}

/**
 * com_rem - this function replaces first instance of '#' with '\0'
 * @b: an address of the string to modify
 *
 * Return: Always 0;
 */
void com_rem(char *b)
{
	int a;

	for (a = 0; b[a] != '\0'; a++)
		if (b[a] == '#' && (!a || b[a - 1] == ' '))
		{
			b[a] = '\0';
			break;
		}
}
