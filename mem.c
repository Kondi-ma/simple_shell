#include "shell.h"

/**
 * free_p - This frees a pointer and it NULLs the address
 * @ad_point: This is the address of the pointer free
 * Return: 1 if free, 0 otherwise.
 */
int free_p(void **ad_point)
{
	if (ad_point && *ad_point)
	{
		free(*ad_point);
		*ad_point = NULL;
		return (1);
	}
	return (0);
}
