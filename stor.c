#include "shell.h"

/**
  * free_ptr - Func that frees a ptr.
  * @add: ptr addrss.
  *
  * Return: (1) => freed || (0).
  */

int free_ptr(void **add)
{
	if (add && *add)
	{
		free(*add);
		*add = NULL;
		return (1);
	}
	return (0);
}
