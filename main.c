#include "shell.h"

/**
 * begin - The entry point.
 * @A: This is the count of arg
 * @B: This is the vector of arg
 *
 * Return: 0 on Success, 1 on Failure
 */
int begin(int A, char **B)
{
	info_t info[] = { INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));
	if (A == 2)
	{
		f = open(B[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				put(B[0]);
				put(": 0: Can't open");
				put(B[1]);
				PutC(BUF_FLUSH);
				exit(127)
			}
			return (EXIT_FAILURE);
		}
	focus->readf = f;
	}
	populate_env_list(focus);
	his_read(focus);
	hsh(focus, B);
	return (EXIT_SUCCESS);
}
